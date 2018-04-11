#include<EEPROM.h>
#include<QueueArray.h>
QueueArray <char> queue;

#define SIZE 3
#define lc 0 //black
#define sc 1 //white

#define lm1 3
#define lm2 5
#define rm1 6
#define rm2 9

int s1, s2, s3, s4, s5, s6, s7, s8;
int b_detect;

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
int eeAddress = 0;

int grid[SIZE][SIZE];
int counter=1;
int uc=0;
int i,j;
char stax_x[]=" ";
char stax_y[]=" ";
int state=0;
int start_x=0;int start_y=0;
int end_x=2;int end_y=2;
bool flag=true;
char prev_dir='N';

void setup() {
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);

  Serial.begin(9600);
  queue.setPrinter(Serial);
  
  grid_solver();

  /*
  while (!queue.isEmpty ()){
    direct(queue.peek(),prev_dir);
    prev_dir=queue.pop();
    
    //char a = queue.dequeue();
    //Serial.print(a);
  }
  if(queue.isEmpty()){
    Serial.println("end bro");
  }
    */
  
}

void loop() {
  readsensors();
  error_map();
  pid();

  if(!queue.isEmpty()){
    if ((s1==lc)&&(s2==lc)&&(s3==lc)&&(s4==lc)&&(s5==lc)&&(s6==lc)&&(s7==lc)&&(s8==lc)){
      delay(10); 
      brake();
      //delay(100);
      direct(queue.peek(),prev_dir);
      prev_dir=queue.pop();
    } 
  }
  else if(queue.isEmpty()){
    brake();
    delay(10000);
  }
}

void grid_solver(){
   for(i=0;i<abs(end_x-start_x);i++){
    if((end_x-start_x)<0){
      queue.enqueue('W');
    }
    else{
      queue.enqueue('E');
    }
   }

   for(i=0;i<abs(end_y-start_y);i++){
    if((end_y-start_y)<0){
      queue.enqueue('S');
    }
    else{
      queue.enqueue('N');
    }
   }

   queue.enqueue('X');
}

void direct(char dir, char prev_dir) {
  Serial.println("direct");
  brake();
  delay(100);
  if (prev_dir == dir) {
    Serial.println(2);
    state = 2;
    cross();
  }
  else if (prev_dir != dir) {
    if (dir == 'E' && prev_dir == 'N') {
      Serial.println(0);
      state = 0;
      cross();
    }
    else if (prev_dir == 'E' && dir == 'S') {
      state = 0;
      cross();
    }
    else if (prev_dir == 'S' && dir == 'W') {
      state = 0;
      cross();
    }
    else if (prev_dir == 'S' && dir == 'E') {
      state = 1;
      cross();
    }
    else if (prev_dir == 'E' && dir == 'N') {
      Serial.println(1);
      state = 1;
      cross();
    }
    else if (prev_dir == 'N' && dir == 'W') {
      state = 1;
      cross();
    }
    else if (prev_dir == 'W' && dir == 'S') {
      state = 1;
      cross();
    }
    else if (prev_dir == 'S' && dir == 'N') {
      state = 1;
      cross();
    }
  }
}

void cross() {
  //Serial.println("cross");
  brake();
  delay(10);

  if (state == 0) {
    sharp_right_turn();
    delay(400);              //to be tuned
    readsensors();
    while (s4 != lc && s5 != lc) { //left on cross
      sharp_right_turn();
      readsensors();
    }
    brake();
    //delay(100);
  }
  else if (state == 1) {
    sharp_left_turn();
    delay(400);              //to be tuned
    readsensors();
    while (s4 != lc && s5 != lc) { //right on cross
      sharp_left_turn();
      readsensors();
    }
    brake();
    //delay(100);
  }

  else if (state == 2) {
    straight();
    delay(30);
    //linefollow();
  }

  left = 1000;
  right = 1000;
}

void savetoEEPROM() {
  EEPROM.put(eeAddress, grid);
}

void readsensors() {
  s1 = digitalRead(A0);
  s2 = digitalRead(A1);
  s3 = digitalRead(A2);
  s4 = digitalRead(A3);
  s5 = digitalRead(A4);
  s6 = digitalRead(8);
  s7 = digitalRead(2);
  s8 = digitalRead(4);
}

void error_map() {
  if ((s3 == sc) && (s4 == lc) && (s5 == lc) && (s6 == sc))
    error = 0;
  else if ((s3 == lc) && (s4 == lc) && (s5 == lc) && (s6 == sc))
    error = -0.5;
  else if ((s3 == sc) && (s4 == lc) && (s5 == sc) && (s6 == sc))
    error = -0.5;
  else if ((s3 == sc) && (s4 == lc) && (s5 == lc) && (s6 == lc))
    error = 0.5;
  else if ((s3 == sc) && (s4 == sc) && (s5 == lc) && (s6 == sc))
    error = 0.5;

  else if ((s2 == sc) && (s3 == lc) && (s4 == lc) && (s5 == sc))
    error = -1;
  else if ((s4 == sc) && (s5 == lc) && (s6 == lc) && (s7 == sc))
    error = 1;

  else if ((s2 == lc) && (s3 == lc) && (s4 == lc) && (s5 == sc))
    error = -1.5;
  else if ((s2 == sc) && (s3 == lc) && (s4 == sc) && (s5 == sc))
    error = -1.5;
  else if ((s4 == sc) && (s5 == lc) && (s6 == lc) && (s7 == lc))
    error = 1.5;
  else if ((s4 == sc) && (s5 == sc) && (s6 == lc) && (s7 == sc))
    error = 1.5;

  else if ((s1 == sc) && (s2 == lc) && (s3 == lc) && (s4 == sc))
    error = -2;
  else if ((s5 == sc) && (s6 == lc) && (s7 == lc) && (s8 == sc))
    error = 2;

  else if ((s1 == lc) && (s2 == lc) && (s3 == lc) && (s4 == sc))
    error = -2.5;
  else if ((s1 == sc) && (s2 == lc) && (s3 == sc) && (s4 == sc))
    error = -2.5;
  else if ((s5 == sc) && (s6 == lc) && (s7 == lc) && (s8 == lc))
    error = 2.5;
  else if ((s5 == sc) && (s6 == sc) && (s7 == lc) && (s8 == sc))
    error = 2.5;

  else if ((s1 == lc) && (s2 == lc) && (s3 == sc))
    error = -3;
  else if ((s6 == sc) && (s7 == lc) && (s8 == lc))
    error = 3;

  if ((s1 == lc) && (s2 == sc) && (s8 == sc))
    error = -3.5;
  if ((s1 == sc) && (s7 == sc) && (s8 == lc))
    error = 3.5;
}

void pid() {
  readsensors();
  error_map();

  pd = Kp * error + Kd * (error - prev_error);

  lms = bs + pd;
  rms = bs - pd;

  if (lms >= left_max)
  {
    lms = left_max;
  }

  else if (lms <= left_min)
  {
    lms = left_min;
  }

  if (rms >= right_max)
  {
    rms = right_max;
  }

  else if (rms <= right_min)
  {
    rms = right_min;
  }

  analogWrite(lm1, lms);
  analogWrite(lm2, 0);
  analogWrite(rm1, rms);
  analogWrite(rm2, 0);

  prev_error = error;

}

void straight() {
  analogWrite(lm1, 90);
  analogWrite(lm2, 0);
  analogWrite(rm1, 90);
  analogWrite(rm2, 0);
}

void sharp_left_turn() {
  analogWrite(lm1, 0);
  analogWrite(lm2, 90);
  analogWrite(rm1, 90);
  analogWrite(rm2, 0);
}

void sharp_right_turn() {
  analogWrite(lm1, 90); //90->90->140 
  analogWrite(lm2, 0);
  analogWrite(rm1, 0);
  analogWrite(rm2, 90);
}

void brake() {
  analogWrite(lm1, 0);
  analogWrite(lm2, 0);
  analogWrite(rm1, 0);
  analogWrite(rm2, 0);
}

