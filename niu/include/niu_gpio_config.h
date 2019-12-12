#ifndef NIU_GPIO_CONFIG_H
#define NIU_GPIO_CONFIG_H

/******************************************************************************
 * GPIO   0 : IN - 左转向按键	-------->  GPIO  22 : OUT - 左转向灯
 * GPIO   1 : IN - 右转向按键	-------->  GPIO  23 : OUT - 右转向灯
 * GPIO   2 : IN - 远光开关		-------->  GPIO  24 : OUT - 远光灯
 * GPIO   3 : IN - 自动大灯		-------->  GPIO  25 : OUT - 近光灯
 * GPIO   4 : IN - 双闪开关		-------->  GPIO  26 : OUT - 天使眼
 * GPIO   5 : IN - 转向关闭开关	-------->  GPIO  27 : OUT - 车尾灯
 * GPIO   6 : IN - 超车按键		-------->  GPIO  28 : OUT - 备用灯控 VCC 输出口 2 （坐桶灯）
 * GPIO   7 : IN - 手动大灯		-------->  GPIO  29 : OUT - 备用喇叭 VCC 输出口 1 + 锁孔灯
 * GPIO  21 : KEY
 *******************************************************************************/
#define  KEY_LEFT_TURN          0
#define  KEY_RIGHT_TURN         1
#define  KEY_REMOTE_LIGHT       2
#define  KEY_AUTO_LIGHT         3
#define  KEY_DOUBLE_FLASH       4
#define  KEY_TURN_OFF           5
#define  KEY_OVERTAKE           6
#define  KEY_MANUAL_LIGHT       7

#define  KEY_TEST              21

#define  LIGHT_LEFT_TURN       22
#define  LIGHT_RIGHT_TURN      23
#define  LIGHT_REMOTE_LIGHT    24
#define  LIGHT_LOW_LIGHT       25
#define  LIGHT_DOUBLE_FLASH    26
#define  LIGHT_TURN_OFF        27
#define  LIGHT_OVERTAKE        28
#define  LIGHT_MANUAL_LIGHT    29

#define GPIO_BCM_SIZE   30 

enum NIU_GPIO_DIRECTION {
    NO,
    KEY,
    IN,
    OUT
};

typedef struct _niu_gpio_config {
    int bcm_code ;
    enum NIU_GPIO_DIRECTION  direction;    
} gpio_bcm_config;

extern gpio_bcm_config g_niu_raspberrypi_gpio_config[GPIO_BCM_SIZE];

#endif
