/*
niu innovation lab
hang.feng@niu.com
*/
#include <string.h>
#include <curl/curl.h>
//#include "debug.h"

size_t write_data(void* buffer, size_t size, size_t nmemb, void *stream)
{
    printf("write_data:%s\n", stream);
    return size*nmemb;
}


int doPostAction(char * serverip, char *postData)
{
	CURLcode res;
	CURL* curl = curl_easy_init();
	if(NULL == curl)
	{
		DbgError("curl easy init failed\n");
		return -1;
	}


	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
	//curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug)

	curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.0.101:8505/me/testpost" );
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_data);
	curl_easy_setopt(curl, CURLOPT_HEADER, 1);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

	res = curl_easy_perform(curl);

	if(res != CURLE_OK)
	{
		switch(res)
		{
			case CURLE_UNSUPPORTED_PROTOCOL:
				fprintf(stderr, "not support protocol.\n");
				break;
			case CURLE_COULDNT_CONNECT:
				fprintf(stderr, "can not connect to remote pc.\n");
				break;
			case CURLE_HTTP_RETURNED_ERROR:
				fprintf(stderr, "http return error\n");
				break;
			case CURLE_READ_ERROR:
				fprintf(stderr, "get local file error\n");
				break;
			default:
				fprintf(stderr, "return value:%d\n", res);
		}
		return -1;
	}
	curl_easy_cleanup(curl);
}




#if 0
typedef struct data_t  	//chrade add 191205 debug purpose..
{  
    unsigned char *value;  
    unsigned int length;  
}data_t;  

//chrade add 191205
 static size_t recv_head_callback(char *ptr, size_t size, size_t nmemb, void *userdata)  
{  
    data_t *recv_head = (data_t*)userdata;  
    unsigned int append = size*nmemb;  
  
    recv_head->value = (unsigned char*)realloc(recv_head->value, recv_head->length+append+1);  
    if(!recv_head->value)  
        return -1;  
  
    memcpy(recv_head->value+recv_head->length, ptr, append);  
    recv_head->length += append;  
    recv_head->value[recv_head->length] = 0;  
  
    //log_debug("recv http response head: %s", recv_head->value);  
    DbgError("recv http response head: %s", recv_head->value);	
    return size*nmemb;  
}  

//chrade add 191205
 static size_t recv_body_callback(char *ptr, size_t size, size_t nmemb, void *userdata)  
{  
    data_t *recv_body = (data_t*)userdata;  
    unsigned int append = size*nmemb;  
  
    recv_body->value = (unsigned char*)realloc(recv_body->value, recv_body->length+append+1);  
    if(!recv_body->value)  
        return -1;  
  
    memcpy(recv_body->value+recv_body->length, ptr, append);  
    recv_body->length += append;  
    recv_body->value[recv_body->length] = 0;  
  
    //log_debug("recv http response body: %s", recv_body->value);  
    DbgError("recv http response body: %s", recv_body->value);
    return size*nmemb;  
}  


int doPostAction(char * serverip, char *postData)
{
  int ErrCode;
  CURL *curlHandle = NULL;
  CURLcode retCode;
  struct curl_slist *headers = NULL; 
  data_t send_body, recv_head, recv_body;
  memset(&send_body, 0, sizeof(data_t));
  memset(&recv_head, 0, sizeof(data_t));
  memset(&recv_body, 0, sizeof(data_t));
  
  char servUrl[1024] = {0};

  strcpy(serverip, "192.168.0.101");  //local debug purpose..

  retCode = curl_global_init(CURL_GLOBAL_ALL);
  if(retCode != CURLE_OK){
  	DbgError("curl global init failed");
	return -1;	//need errcode to realize this part..
  }


  curlHandle = curl_easy_init();

  if(NULL == curlHandle){
    DbgError("curl_easy_init failed\n");
    return -1;// need errcode realize this part..
  }

  memset(servUrl, 0x0, sizeof(servUrl));
 
//  sprintf(servUrl, "http://%s/testcgi", serverip);
  sprintf(servUrl, "http://192.168.0.101:8505/me/testpost");

  send_body.value = postData;
  send_body.length = strlen((const char*)send_body.value);

  curl_easy_setopt(curlHandle, CURLOPT_URL, servUrl);
  curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
  curl_easy_setopt(curlHandle, CURLOPT_TIMEOUT, 3L);
  curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1L);
  
  headers = curl_slist_append(headers, "Accept: text/json");  
  headers = curl_slist_append(headers, "Content-Type: text/json; charset=UTF-8");  
  headers = curl_slist_append(headers, "Connection: keep-alive");  
  curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headers);  
  
  curl_easy_setopt(curlHandle, CURLOPT_HEADERFUNCTION, recv_head_callback);  
  curl_easy_setopt(curlHandle, CURLOPT_HEADERDATA, &recv_head);  
  
  curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, recv_body_callback);  
  curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &recv_body);  

  retCode = curl_easy_perform(curlHandle);
  if(retCode != CURLE_OK){
    DbgError("curl easy perform faild:%s",curl_easy_strerror(retCode));
    goto ErrP;
  }
  
  unsigned int code = 200;
  retCode = curl_easy_getinfo(curlHandle, CURLINFO_RESPONSE_CODE, &code);

  if(retCode != CURLE_OK || code != 200){
    DbgError("Response-Code:%d", code);
    goto ErrP;
  }
  //follow get and parse recv_body...

  if(send_body.value) free(send_body.value);


  if(send_body.value) free(send_body.value);  
  //if(json_req) json_decref(json_req);  

  if(recv_head.value) free(recv_head.value);  
  if(recv_body.value) free(recv_body.value);  
  //if(json_res) json_decref(json_res);  

  if(headers) curl_slist_free_all(headers);  
  if(curlHandle) curl_easy_cleanup(curlHandle);  
  curl_global_cleanup();  
  return 0;  

 ErrP:  
  if(send_body.value) free(send_body.value);  
  //if(json_req) json_decref(json_req);  
  
  if(recv_head.value) free(recv_head.value);  
  if(recv_body.value) free(recv_body.value);  
  //if(json_res) json_decref(json_res);  
  
  if(headers) curl_slist_free_all(headers);  
  if(curlHandle) curl_easy_cleanup(curlHandle);  
  curl_global_cleanup();  
    return -1; 



  
  return 0;
}

#endif


