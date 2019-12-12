/*
niu innovation lab
hang.feng@niu.com
*/
#include <string.h>


#include "cJSON.h"
#include "niu_cjson.h"
#include "niu_uart.h"
#include "niu_cmd.h"
#include "niu_gpio_config.h"

int test_input_and_out(int input_pin, int output_pin)
{
    int i, iRet = 0;
    write_gpio_to_one(input_pin);
    iRet = read_gpio_as_one(output_pin);
    if(iRet == WRITE_FAILED)
    {
        return 0;
    }
    else
    {
        write_gpio_to_zero(input_pin);
        iRet = read_gpio_as_zero(output_pin);

        if(iRet == WRITE_FAILED)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

int main()
{
  int i, iRet = 0;
  char serverip[32];
  PostData pData;
  char *pJsonString;

  char **ppJsonString = &pJsonString;

  strcpy(serverip, "192.168.0.101:8505");

  for (i=0;i<9;i++){
    pData.channel[i] = 1;
  }
  
  strcpy(pData.sn, "abcdefgh\0");

  strcpy(pData.swver, "SWVER123\0" );

  strcpy(pData.hwver, "HWVER456\0");

  // ���Է�Ϊ�������֣� 
  // ��һ���ֲ������������ӿڣ�
  iRet = SWITCH_FAILED;
  // ������Ҫ ���ʹ���ָ��, żУ�飬 9600 ������,������������ģʽ�� 
  iRet = switch_factory_mode("/dev/tty0");
  if(iRet == SWITCH_SUCCESS)
  {
        niu_enable_all_gpio();
        // GPIO   0 : IN - ��ת�򰴼�	-------->  GPIO  22 : OUT - ��ת���
        pData.channel[0] = test_input_and_out(KEY_LEFT_TURN, LIGHT_LEFT_TURN);
        // * GPIO   1 : IN - ��ת�򰴼�	-------->  GPIO  23 : OUT - ��ת���
        pData.channel[0] = test_input_and_out(KEY_RIGHT_TURN, LIGHT_RIGHT_TURN);
        // * GPIO   2 : IN - Զ�⿪��		-------->  GPIO  24 : OUT - Զ���
        pData.channel[0] = test_input_and_out(KEY_REMOTE_LIGHT, LIGHT_REMOTE_LIGHT);
        // * GPIO   3 : IN - �Զ����		-------->  GPIO  25 : OUT - �����
        pData.channel[0] = test_input_and_out(KEY_AUTO_LIGHT, LIGHT_LOW_LIGHT);
        // * GPIO   4 : IN - ˫������		-------->  GPIO  26 : OUT - ��ʹ��
        pData.channel[0] = test_input_and_out(KEY_DOUBLE_FLASH, LIGHT_DOUBLE_FLASH);
        // * GPIO   5 : IN - ת��رտ���	-------->  GPIO  27 : OUT - ��β��
        pData.channel[0] = test_input_and_out(KEY_TURN_OFF, LIGHT_OVERTAKE);
        // * GPIO   6 : IN - ��������		-------->  GPIO  28 : OUT - ���õƿ� VCC ����� 2 ����Ͱ�ƣ�
        pData.channel[0] = test_input_and_out(KEY_OVERTAKE, LIGHT_OVERTAKE);
        // * GPIO   7 : IN - �ֶ����		-------->  GPIO  29 : OUT - �������� VCC ����� 1 + ���׵�
        pData.channel[0] = test_input_and_out(KEY_MANUAL_LIGHT, LIGHT_MANUAL_LIGHT);
        
        // ͨ�����ʹ���ָ��رչ�������ģʽ
        exit_factory_mode("/dev/tty0");
        // �ڶ����� ˫������ ��ƽ�� 3.3V ���͵� 0V�� ��� ˫���Ƿ������� ������ת����ʾ���Ƿ������������
        // �������� ��ѯ����汾�� 
        // ���Ĳ��� ��ѯ���
        niu_disable_all_gpio();
  }
  else
  {
        exit_factory_mode("/dev/tty0");
  }

  genPostData(&pData,  ppJsonString);

  printf("%s\n", pJsonString);

  doPostAction(serverip, pJsonString);

  return 0;

}



