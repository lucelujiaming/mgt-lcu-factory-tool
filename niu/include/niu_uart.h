#ifndef NIU_UART_H
#define NIU_UART_H

#define SWITCH_SUCCESS 1
#define SWITCH_FAILED   0

int  switch_factory_mode(char * dev_name);
int exit_factory_mode(char * dev_name);

int  query_light_sensor(char * dev_name);
int  query_software_version(char * dev_name);

#endif
