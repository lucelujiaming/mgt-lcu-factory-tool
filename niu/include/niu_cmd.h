#ifndef NIU_CMD_H
#define NIU_CMD_H

#define WRITE_SUCCESS 1
#define WRITE_FAILED   0

int read_gpio_as_one();
int read_gpio_as_zero();

int write_gpio_to_one();
int write_gpio_to_zero();
    
void niu_enable_all_gpio();
void niu_exec_cmd(char * cmd_string);
void niu_exec_cmd_with_result(char * cmd_string, char * result_string);

#endif
