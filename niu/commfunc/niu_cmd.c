#include "niu_cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include "niu_gpio_config.h"

int read_gpio_as_one(int gpio_idx)
{
    char cCmdString[128];
    char cResultString[128];
    
    memset(cCmdString, 0x00, 128);
    memset(cResultString, 0x00, 128);
    sprintf(cCmdString, "echo %d > /sys/class/gpio/export\n", 
        g_niu_raspberrypi_gpio_config[gpio_idx].bcm_code);
    niu_exec_cmd_with_result(cCmdString, cResultString);
    if(strcmp(cResultString, "1\n") == 0)
        return WRITE_SUCCESS;
    else
        return WRITE_FAILED;
}

int read_gpio_as_zero(int gpio_idx)
{
    char cCmdString[128];
    char cResultString[128];
    
    memset(cCmdString, 0x00, 128);
    memset(cResultString, 0x00, 128);
    sprintf(cCmdString, "echo %d > /sys/class/gpio/export\n", 
        g_niu_raspberrypi_gpio_config[gpio_idx].bcm_code);
    niu_exec_cmd_with_result(cCmdString, cResultString);
    if(strcmp(cResultString, "0\n") == 0)
        return WRITE_SUCCESS;
    else
        return WRITE_FAILED;
}

int write_gpio_to_one(int gpio_idx)
{
    char cCmdString[128];
    char cResultString[128];
    
    memset(cCmdString, 0x00, 128);
    sprintf(cCmdString, "echo %d > /sys/class/gpio/export\n", 
        g_niu_raspberrypi_gpio_config[gpio_idx].bcm_code);
    system(cCmdString);
    usleep(50);

    memset(cCmdString, 0x00, 128);
    memset(cResultString, 0x00, 128);
    sprintf(cCmdString, "echo %d > /sys/class/gpio/export\n", 
        g_niu_raspberrypi_gpio_config[gpio_idx].bcm_code);
    niu_exec_cmd_with_result(cCmdString, cResultString);
    if(strcmp(cResultString, "1\n") == 0)
        return WRITE_SUCCESS;
    else
        return WRITE_FAILED;
}

int write_gpio_to_zero(int gpio_idx)
{
    char cCmdString[128];
    char cResultString[128];
    
    memset(cCmdString, 0x00, 128);
    sprintf(cCmdString, "echo %d > /sys/class/gpio/export\n", 
        g_niu_raspberrypi_gpio_config[gpio_idx].bcm_code);
    system(cCmdString);
    usleep(50);

    memset(cCmdString, 0x00, 128);
    memset(cResultString, 0x00, 128);
    sprintf(cCmdString, "echo %d > /sys/class/gpio/export\n", 
        g_niu_raspberrypi_gpio_config[gpio_idx].bcm_code);
    niu_exec_cmd_with_result(cCmdString, cResultString);
    if(strcmp(cResultString, "0\n") == 0)
        return WRITE_SUCCESS;
    else
        return WRITE_FAILED;
}

void niu_enable_all_gpio()
{
    int i = 0 ;
    char cCmdString[128];
    for(i = 0 ; i < GPIO_BCM_SIZE; i++)
    {
	if(g_niu_raspberrypi_gpio_config[i].bcm_code >0)
       {
            memset(cCmdString, 0x00, 128);
            sprintf(cCmdString, "echo %d > /sys/class/gpio/export\n", 
                g_niu_raspberrypi_gpio_config[i].bcm_code);
            system(cCmdString);
            usleep(50);
            
            memset(cCmdString, 0x00, 128);
            if(g_niu_raspberrypi_gpio_config[i].direction == KEY)
            {
            	sprintf(cCmdString, "echo 'in' > /sys/class/gpio/gpio%d/direction\n", 
                	g_niu_raspberrypi_gpio_config[i].bcm_code);
            }
            else if(g_niu_raspberrypi_gpio_config[i].direction == IN)
            {
            	sprintf(cCmdString, "echo 'in' > /sys/class/gpio/gpio%d/direction\n", 
                	g_niu_raspberrypi_gpio_config[i].bcm_code);
            }
            else if(g_niu_raspberrypi_gpio_config[i].direction == OUT)
            {
            	sprintf(cCmdString, "echo 'out' > /sys/class/gpio/gpio%d/direction\n", 
                	g_niu_raspberrypi_gpio_config[i].bcm_code);
            }
            system(cCmdString);
            usleep(50);
	}
    }
}


void niu_disable_all_gpio()
{
    int i = 0 ;
    char cCmdString[128];
    for(i = 0 ; i < GPIO_BCM_SIZE; i++)
    {
	if(g_niu_raspberrypi_gpio_config[i].bcm_code >0)
       {
            memset(cCmdString, 0x00, 128);
            sprintf(cCmdString, "echo %d > /sys/class/gpio/unexport\n", 
                g_niu_raspberrypi_gpio_config[i].bcm_code);
            system(cCmdString);
            usleep(50);
	}
    }
}

void niu_exec_cmd(char * cmd_string)
{
    system(cmd_string);
}

void niu_exec_cmd_with_result(char * cmd_string, char * result_string)
{
    FILE *fp = NULL;
    char data[100] = {'0'};
    fp = popen("ls", "r");
    if (fp == NULL)
    {
        printf("popen error!\n");
        return 1;
    }
    while (fgets(data, sizeof(data), fp) != NULL)
    {
        sprintf(result_string, "%s", data);
    }
    pclose(fp);
    
}

