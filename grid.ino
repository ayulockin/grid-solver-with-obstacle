#include<QueueArray.h>
QueueArray <char> queue_x;
QueueArray <char> queue_y;

#define lc 0 //black
#define sc 1 //white

///////////////////////////grid parameters//////////////////
int flag = 0;
int start_x = 0; int start_y = 0;
int end_x = 2;
int end_y = 2;
int i,j;
char prev_dir = 'N';
int state = 0;
int pos = 100;

char handle[3];
int k=0;

//////////////////////pid parameters///////////////////

float error = 0;
float prev_error = 0;
float Kp = 37.5;
float Kd = 100;  //100/150
float P = 0;
float D = 0;
float pd = 0;

int lms, rms;
int bs = 130;

int leftthres = 400; int rightthres = 400;
int left_max = 200;
int right_max = 200; //based on motor speed diff
int left_min = 0;
int right_min = 0;

int left = 1000; int right = 1000;

////////////////////sensor variables///////////////////

int s1, s2, s3, s4, s5, s6, s7, s8;
int b_detect;

////////////////////motor pin out//////////////

#define lm1 3
#define lm2 5
#define rm1 6
#define rm2 9
