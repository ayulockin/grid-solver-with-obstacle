#include<EEPROM.h>

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

int grid[SIZE][SIZE] = {{0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

int x = 0; int y = 0;
int dx = 2;   int dy = 2;
int state = 0;
char dir;
char prev_dir = 'N';
int eeAddress = 0;

void setup() {
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);

  //Serial.begin(9600);
}

void loop() {
  readsensors();
  //b_detect = analogRead(A5);
  error_map();
  pid();
  if ((s1==lc)&&(s2==lc)&&(s3==lc)&&(s4==lc)&&(s5==lc)&&(s6==lc)&&(s7==lc)&&(s8==lc)){
    //Serial.println('a');
    delay(10); 
    brake();
    //delay(100);
    /*
    digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(13,LOW);
    delay(50);*/
    
    if(dy>y){
      //Serial.println('b');
      //Serial.print(x);
      //Serial.print('\t');
      //Serial.println(y);
      direct('N','N');
      coord_handle('N');
    }
    else if(dy==y){
      //Serial.println('c');
      //Serial.print(x);
      //Serial.print('\t');
      //Serial.println(y);
      if(dx!=0){
      direct('E','N');
      coord_handle('E');
      follow_x();
      }
      else if(dx==0){
        brake();
        delay(10000);
      }
    }
  }
}

void follow_x() {
  //Serial.println('d');
  while (1) {
    readsensors();
    //b_detect = analogRead(A5);
    error_map();

    if(b_detect>700 && b_detect<750){
      brake();
      delay(100);
      digitalWrite(13,HIGH);
      delay(50);
      digitalWrite(13,LOW);
      delay(50);
      block_detect(); 
    }
    else{
      if ((s1==lc)&&(s2==lc)&&(s3==lc)&&(s4==lc)&&(s5==lc)&&(s6==lc)&&(s7==lc)&&(s8==lc)){
        delay(10);
        brake();
        delay(100);
        if (dx > x){
          //Serial.println('e');
          //Serial.print(x);
          //Serial.print('\t');
          //Serial.println(y);
          direct('E', 'E');
          coord_handle('E');
        }
        else if (dx == x) {
          //Serial.println('f');
          //Serial.print(x);
          //Serial.print('\t');
          //Serial.println(y);
          brake();
          savetoEEPROM();
          digitalWrite(13,HIGH);
          delay(10000);
        }
      }
    }
    pid(); 
  }
}

int coord_handle(char dir) {
  //Serial.println("coord");
  if (dir == 'N') {
    y++;
    //Serial.print(x);
    //Serial.print('\t');
    //Serial.println(y);
  }
  else if (dir == 'E') {
    x++;
    //Serial.print(x);
    //Serial.print('\t');
    //Serial.println(y);
  }
  else if (dir == 'W') {
    x--;
    //Serial.print(x);
    //Serial.print('\t');
    //Serial.println(y);
  }
  else if (dir == 'S') {
    y--;
    //Serial.print(x);
    //Serial.print('\t');
    //Serial.println(y);
  }
}

void direct(char dir, char prev_dir) {
  //Serial.println("direct");
  brake();
  delay(100);
  if (prev_dir == dir) {
    state = 2;
    cross();
  }
  else if (prev_dir != dir) {
    if (dir == 'E' && prev_dir == 'N') {
      state = 0;
      cross();
      grid[x][y] = 1;
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
    delay(10);
    //linefollow();
  }

  left = 1000;
  right = 1000;
}

void block_detect(){
  sharp_right_turn();
  delay(500);
  readsensors();
  while(s4!=lc && s5!=lc){
    sharp_right_turn();
    readsensors();
  }
  if(dir=='N'){
    dir='S';
  }
  else if(dir=='S'){
    dir='N';
  }
  else if(dir=='E'){
    dir='W';
  }
  else if(dir=='W'){
    dir='E';
  }
  coord_handle(dir);
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
