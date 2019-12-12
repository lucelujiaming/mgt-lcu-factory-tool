#ifndef NIU_GPIO_CONFIG_H
#define NIU_GPIO_CONFIG_H

/******************************************************************************
 * GPIO   0 : IN - ��ת�򰴼�	-------->  GPIO  22 : OUT - ��ת���
 * GPIO   1 : IN - ��ת�򰴼�	-------->  GPIO  23 : OUT - ��ת���
 * GPIO   2 : IN - Զ�⿪��		-------->  GPIO  24 : OUT - Զ���
 * GPIO   3 : IN - �Զ����		-------->  GPIO  25 : OUT - �����
 * GPIO   4 : IN - ˫������		-------->  GPIO  26 : OUT - ��ʹ��
 * GPIO   5 : IN - ת��رտ���	-------->  GPIO  27 : OUT - ��β��
 * GPIO   6 : IN - ��������		-------->  GPIO  28 : OUT - ���õƿ� VCC ����� 2 ����Ͱ�ƣ�
 * GPIO   7 : IN - �ֶ����		-------->  GPIO  29 : OUT - �������� VCC ����� 1 + ���׵�
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
