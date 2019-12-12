#include "niu_uart.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

// 0x68 + 0x70 + 0x8F + 0x68 + 0x04 + 0x03 + 0x89 + 0x34 + 0x33 = 0x2C6
char * switch_factory_mode_data = "\x68\x70\x8f\x68\x04\x03\x89\x34\x33\xC6\x16";
// 0x68 + 0x70 + 0x8F + 0x68 + 0x04 + 0x03 + 0x89 + 0x33 + 0x33 = 0x2C5
char * exit_factory_mode_data          = "\x68\x70\x8f\x68\x04\x03\x89\x33\x33\xC5\x16";

int set_opt(int,int,int,char,int);

int switch_factory_mode(char * dev_name)
{
    int fd,nByte,flag=1;
    char *uart3 = dev_name;    //   "/dev/ttySAC3"\u662fcon2
    char buffer[512];
    memset(buffer, 0, sizeof(buffer));
    if((fd = open(uart3, O_RDWR|O_NONBLOCK))<0)  //  \u975e\u963b\u585e\u8bfb\u65b9\u5f0f 
        printf("open %s is failed",uart3);
    else{
        set_opt(fd, 9600, 8, 'N', 1);
        write(fd, switch_factory_mode_data, strlen(switch_factory_mode_data));
        usleep(1000);
        nByte = read(fd, buffer, 512);
        close(fd);
        if(buffer[4] == 0x84)
            return SWITCH_SUCCESS;
        else
            return SWITCH_FAILED;
    }
}


int exit_factory_mode(char * dev_name)
{
    int fd,nByte,flag=1;
    char *uart3 = dev_name;    //   "/dev/ttySAC3"\u662fcon2
    char buffer[512];
    memset(buffer, 0, sizeof(buffer));
    if((fd = open(uart3, O_RDWR|O_NONBLOCK))<0)  //  \u975e\u963b\u585e\u8bfb\u65b9\u5f0f 
        printf("open %s is failed",uart3);
    else{
        set_opt(fd, 9600, 8, 'N', 1);
        write(fd, exit_factory_mode_data, strlen(exit_factory_mode_data));
        usleep(1000);
        nByte = read(fd, buffer, 512);
        close(fd);
        if(buffer[4] == 0x84)
            return SWITCH_SUCCESS;
        else
            return SWITCH_FAILED;
    }
}


int  query_light_sensor(char * dev_name)
{
    int fd,nByte,flag=1;
    char *uart3 = dev_name;    //   "/dev/ttySAC3"\u662fcon2
    char buffer[512];
    memset(buffer, 0, sizeof(buffer));
    if((fd = open(uart3, O_RDWR|O_NONBLOCK))<0)  //  \u975e\u963b\u585e\u8bfb\u65b9\u5f0f 
        printf("open %s is failed",uart3);
    else{
        set_opt(fd, 9600, 8, 'N', 1);
        write(fd, exit_factory_mode_data, strlen(exit_factory_mode_data));
        usleep(1000);
        nByte = read(fd, buffer, 512);
        close(fd);
        if(buffer[4] == 0x84)
            return SWITCH_SUCCESS;
        else
            return SWITCH_FAILED;
    }
}

int  query_software_version(char * dev_name)
{
    int fd,nByte,flag=1;
    char *uart3 = dev_name;    //   "/dev/ttySAC3"\u662fcon2
    char buffer[512];
    memset(buffer, 0, sizeof(buffer));
    if((fd = open(uart3, O_RDWR|O_NONBLOCK))<0)  //  \u975e\u963b\u585e\u8bfb\u65b9\u5f0f 
        printf("open %s is failed",uart3);
    else{
        set_opt(fd, 9600, 8, 'N', 1);
        write(fd, exit_factory_mode_data, strlen(exit_factory_mode_data));
        usleep(1000);
        nByte = read(fd, buffer, 512);
        close(fd);
        if(buffer[4] == 0x84)
            return SWITCH_SUCCESS;
        else
            return SWITCH_FAILED;
    }
}

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio,oldtio;
    if  ( tcgetattr( fd,&oldtio)  !=  0) { 
        perror("SetupSerial 1");
        return -1;
    }
    bzero( &newtio, sizeof( newtio ) );
    newtio.c_cflag  |=  CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;
 
    switch( nBits )
    {
        case 7:
            newtio.c_cflag |= CS7;
            break;
        case 8:
            newtio.c_cflag |= CS8;
            break;
    }
 
    switch( nEvent )
    {
    case 'O':
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E': 
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':  
        newtio.c_cflag &= ~PARENB;
        break;
    }
 
    switch( nSpeed )
    {
        case 2400:
            cfsetispeed(&newtio, B2400);
            cfsetospeed(&newtio, B2400);
            break;
        case 4800:
            cfsetispeed(&newtio, B4800);
            cfsetospeed(&newtio, B4800);
            break;
        case 9600:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
        case 115200:
            cfsetispeed(&newtio, B115200);
            cfsetospeed(&newtio, B115200);
            break;
        case 460800:
            cfsetispeed(&newtio, B460800);
            cfsetospeed(&newtio, B460800);
            break;
        default:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
    }
    if( nStop == 1 )
        newtio.c_cflag &=  ~CSTOPB;
    else if ( nStop == 2 )
        newtio.c_cflag |=  CSTOPB;
        newtio.c_cc[VTIME]  = 100;///* \u8bbe\u7f6e\u8d85\u65f610 seconds*/
        newtio.c_cc[VMIN] = 0;
        tcflush(fd,TCIFLUSH);
    if((tcsetattr(fd,TCSANOW,&newtio))!=0)
    {
        perror("com set error");
        return -1;
    }
    
    //    printf("set done!\n\r");
    return 0;
}
 

