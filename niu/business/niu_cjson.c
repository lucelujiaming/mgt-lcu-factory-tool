/*
niu innovation lab
hang.feng@niu.com
*/


#include "cJSON.h"
#include "niu_cjson.h"

int genPostData(PostData *Data, char **replyString)
{
    
    cJSON* rootJson = NULL;
    cJSON* itemJson = NULL;

    rootJson = cJSON_CreateObject();
    cJSON_AddNumberToObject(rootJson, "left-left", Data->channel[0]);
    cJSON_AddNumberToObject(rootJson, "right-right", Data->channel[1]);
    cJSON_AddNumberToObject(rootJson, "far-far", Data->channel[2]);
    cJSON_AddNumberToObject(rootJson, "auto-near", Data->channel[3]);
    cJSON_AddNumberToObject(rootJson, "double-angle", Data->channel[4]);
    cJSON_AddNumberToObject(rootJson, "off-tail", Data->channel[5]);
    cJSON_AddNumberToObject(rootJson, "pass-back2", Data->channel[6]);
    cJSON_AddNumberToObject(rootJson, "manual-back1", Data->channel[7]);

    cJSON_AddStringToObject(rootJson, "swver", Data->swver);
    cJSON_AddStringToObject(rootJson, "hwver", Data->hwver);

    if(Data->modeSwitch){
        cJSON_AddStringToObject(rootJson, "modeSwitch", "Succeed");
    }else{
        cJSON_AddStringToObject(rootJson, "modeSwitch", "failed");
    }

    *replyString = cJSON_Print(rootJson);

    printf("in %s\n", *replyString );

    return 0; 
} 



