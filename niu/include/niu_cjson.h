/*
niu innovation lab
hang.feng@niu.com
*/


typedef struct{
    int channel[9];
    char sn[9];
    char swver[9];
    char hwver[9];
    int modeSwitch;
}PostData;

int genPostData(PostData *Data, char **replyString);

