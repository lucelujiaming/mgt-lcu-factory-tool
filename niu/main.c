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

  // 测试分为两个部分， 
  // 第一部分测试输入和输出接口，
  iRet = SWITCH_FAILED;
  // 首先需要 发送串口指令, 偶校验， 9600 波特率,开启工厂生产模式： 
  iRet = switch_factory_mode("/dev/tty0");
  if(iRet == SWITCH_SUCCESS)
  {
        niu_enable_all_gpio();
        // GPIO   0 : IN - 左转向按键	-------->  GPIO  22 : OUT - 左转向灯
        pData.channel[0] = test_input_and_out(KEY_LEFT_TURN, LIGHT_LEFT_TURN);
        // * GPIO   1 : IN - 右转向按键	-------->  GPIO  23 : OUT - 右转向灯
        pData.channel[0] = test_input_and_out(KEY_RIGHT_TURN, LIGHT_RIGHT_TURN);
        // * GPIO   2 : IN - 远光开关		-------->  GPIO  24 : OUT - 远光灯
        pData.channel[0] = test_input_and_out(KEY_REMOTE_LIGHT, LIGHT_REMOTE_LIGHT);
        // * GPIO   3 : IN - 自动大灯		-------->  GPIO  25 : OUT - 近光灯
        pData.channel[0] = test_input_and_out(KEY_AUTO_LIGHT, LIGHT_LOW_LIGHT);
        // * GPIO   4 : IN - 双闪开关		-------->  GPIO  26 : OUT - 天使眼
        pData.channel[0] = test_input_and_out(KEY_DOUBLE_FLASH, LIGHT_DOUBLE_FLASH);
        // * GPIO   5 : IN - 转向关闭开关	-------->  GPIO  27 : OUT - 车尾灯
        pData.channel[0] = test_input_and_out(KEY_TURN_OFF, LIGHT_OVERTAKE);
        // * GPIO   6 : IN - 超车按键		-------->  GPIO  28 : OUT - 备用灯控 VCC 输出口 2 （坐桶灯）
        pData.channel[0] = test_input_and_out(KEY_OVERTAKE, LIGHT_OVERTAKE);
        // * GPIO   7 : IN - 手动大灯		-------->  GPIO  29 : OUT - 备用喇叭 VCC 输出口 1 + 锁孔灯
        pData.channel[0] = test_input_and_out(KEY_MANUAL_LIGHT, LIGHT_MANUAL_LIGHT);
        
        // 通过发送串口指令关闭工厂生产模式
        exit_factory_mode("/dev/tty0");
        // 第二步， 双闪开关 电平从 3.3V 降低到 0V， 检查 双闪是否正常， 另外检查转向提示音是否输出并正常。
        // 第三步， 查询软件版本， 
        // 第四步， 查询光感
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



