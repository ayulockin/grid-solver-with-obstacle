#include<QueueArray.h>
QueueArray <char> queue_x;
QueueArray <char> queue_y;

#define SIZE 3
#define lc 0 //black
#define sc 1 //white

////////////////////motor pin out//////////////

#define lm1 3
#define lm2 5
#define rm1 6
#define rm2 9

////////////////////sensor variables///////////////////

int s1, s2, s3, s4, s5, s6, s7, s8;
int b_detect;

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
int eeAddress = 0;

///////////////////////////grid parameters//////////////////

int c_left=0;int c_right=0;
int c_up=0;int c_down=0;

int c_x=0;int c_y=0;

int i,j;
int flag=0;

int x; int y;
int start_x=0;int start_y=0;
int end_x=2;
int end_y=2;

char prev_dir='N';
int state=0;
int pos=100;

///////////grid solved without obstacles to get the optimum path////////////

void grid_solved(){
  for(i=0;i<abs(end_x-start_x);i++){
    if((end_x-start_x)<0){
      //c_left++;
      queue_x.push('W');
    }
    else{
      //c_right++;
      queue_y.push('E');
    }
  }
   
  for(i=0;i<abs(end_y-start_y);i++){
    if((end_y-start_y)<0){
      //c_down++;
      queue_y.push('S');
    }
    else{
      //c_up++;
      queue_y.push('N');
    }
  }

  queue_x.push('X');
  queue_y.push('X');
  //c_x=c_left+c_right;
  //c_y=c_up+c_down;
}

///////////////////block check///////////



void loop(){
  readsensors();
  readsensors_block();
  error_map();
  pid();

  if(queue_x.isEmpty() && queue_y.isEmpty()){
    brake();
    delay(10000);
  }
  else{
    if(pos==100){
      x_follow();
    }
    else if(pos==101){
      y_follow();
    }
  }
  
}

void x_follow(){
  while(!queue_x.isEmpty()){
    readsensors();
    error_map();
    readsensors_block();
    pid();

    if(flag==0){
      if(queue_x.peek()=='W'){
        if(check_proximity){
          block_detect();
          flag=1;
          pos=101;
          return;
        }
        else if((s1==lc)&&(s2==lc)&&(s3==lc)&&(s4==lc)&&(s5==lc)&&(s6==lc)&&(s7==lc)&&(s8==lc)){
          delay(10);
          brake();

          flag=0;
          direct(queue_x.peek(),prev_dir);

          prev_dir=queue_x.pop();
          c_left--;
          c_x--;
          x=x-1;
        }
      }
      else if(queue_x.peek()=='E'){
        if(check_proximity){
          block_detect();
          queue_x.push('W');
          flag=1;
          pos=101;
          return;
        }
        else if((s1==lc)&&(s2==lc)&&(s3==lc)&&(s4==lc)&&(s5==lc)&&(s6==lc)&&(s7==lc)&&(s8==lc)){
          delay(10);
          brake();
          flag=0;
          state=0;
          cross();
          prev_dir=queue_x.pop();
          c_right--;
          c_x--;
          x=x+1;
         }
        }
    }
    else if(flag==1){ //sent by queue_y
      if(queue_x.peek()=='W'){
        queue_y.push(prev_dir);
        if(check_proximity){
          block_detect();
          flag=2;
          pos=101;
          return;
        }
        else if((s1==lc)&&(s2==lc)&&(s3==lc)&&(s4==lc)&&(s5==lc)&&(s6==lc)&&(s7==lc)&&(s8==lc)){
          delay(10);
          brake();

          flag=0;
          state=1;
          cross();

          prev_dir=queue_x.pop();
          c_left--;
          c_x--;
          x=x-1;
        }
      }
      else if(queue_x.peek()=='E'){
        if(check_proximity){
          block_detect();
          queue_y.push(prev_dir);
          flag=1;
          pos=101;
          return;
        }
        else if((s1==lc)&&(s2==lc)&&(s3==lc)&&(s4==lc)&&(s5==lc)&&(s6==lc)&&(s7==lc)&&(s8==lc)){
          delay(10);
          brake();
          flag=0;
          state=0;
          cross();
          prev_dir=queue_x.pop();
          c_right--;
          c_x--;
          x=x+1;
         }
        }
    }
    else if(flag==2){ //both way jamed

      ////////////
      queue_y.push(prev_dir);
      ////////////
      if(queue_x.peek()=='W'){
        flag=0;
        state=0;
        cross();
        prev_dir=queue_x.pop();
        c_x++;
        c_left++;
        x=x+1;
        pos=101;
        return;
      }
      else if(queue_x.peek()=='E'){
        flag=0;
        state=1;
        cross();
        prev_dir=queue_x.pop();
        c_x++;
        c_right++;
        x=x-1;
        pos=101;
        return;
      }
    } 
  }
}

void y_follow(){
  while(!queue_y.isEmpty()){
    readsensors();
    error_map();
    readsensors_block();
    pid();

    if(flag==0){
      if(queue_y.peek()=='N'){
        if(check_proximity){
          block_detect();
          flag=1;
          pos=100;
          return;
        }
        else if((s1==lc)&&(s2==lc)&&(s3==lc)&&(s4==lc)&&(s5==lc)&&(s6==lc)&&(s7==lc)&&(s8==lc)){
          delay(10);
          brake();

          flag=0;
          state=2;
          cross();

          prev_dir=queue_y.pop();
          c_up--;
          c_y--;
          y=x+1;
        }
      }
      else if(queue_y.peek()=='S'){
        if(check_proximity){
          block_detect();
          flag=1;
          pos=100;
          return;
        }
        else if((s1==lc)&&(s2==lc)&&(s3==lc)&&(s4==lc)&&(s5==lc)&&(s6==lc)&&(s7==lc)&&(s8==lc)){
          delay(10);
          brake();
          flag=0;
          state=2;
          cross();
          prev_dir=queue_y.pop();
          c_down--;
          c_y--;
          y=y-1;
         }
        }
    }
    else if(flag==1){ //sent by queue_x
      queue_x.push(prev_dir);
      if(queue_y.peek()=='N'){
        /////////////////
        queue_x.push(prev_dir);
        //////////////////
        if(check_proximity){
          block_detect();
          queue_x.push(prev_dir);
          flag=2;
          pos=100;
          return;
        }
        else if((s1==lc)&&(s2==lc)&&(s3==lc)&&(s4==lc)&&(s5==lc)&&(s6==lc)&&(s7==lc)&&(s8==lc)){
          delay(10);
          brake();

          flag=0;
          state=2;
          cross();

          prev_dir=queue_y.pop();
          c_up--;
          c_y--;
          y=y+1;
        }
      }
      else if(queue_y.peek()=='S'){
        queue_x.push(prev_dir);
        if(check_proximity){
          block_detect();
          flag=1; 
          pos=100;
          return;
        }
        else if((s1==lc)&&(s2==lc)&&(s3==lc)&&(s4==lc)&&(s5==lc)&&(s6==lc)&&(s7==lc)&&(s8==lc)){
          delay(10);
          brake();
          flag=0;
          state=2;
          cross();
          prev_dir=queue_y.pop();
          c_down--;
          c_y--;
          y=y-1;
         }
        }
    }
    else if(flag==2){ //both way jamed
      //////////////////
      queue_x.push(prev_dir);
      //////////////////
      if(queue_y.peek()=='N'){
        flag=0;
        state=2;
        cross();
        prev_dir=queue_y.pop();
        c_y++;
        c_up++;
        y=y-1;
        pos=100;
        return;
      }
      else if(queue_y.peek()=='S'){
        flag=0;
        state=2;
        cross();
        prev_dir=queue_y.pop();
        c_y++;
        c_down++;
        y=y+1;
        pos=100;
        return;
      }
    } 
  }
}

void direct(char dir, char prev_dir) {
  //Serial.println("direct");
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

void block_detect(){
  //Serial.println('b');
  if(b_detect<400){
    readsensors_block();
    while(b_detect>100){
      readsensors_block();
      slow_pid();
    }
    brake();
    delay(1000);

    /////
  sharp_right_turn();
  delay(600);
  readsensors();
  while(s4!=lc && s5!=lc){
    sharp_right_turn();
    readsensors();
  }
}
}


void setup() {
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);

  Serial.begin(9600);
  queue_x.setPrinter(Serial);
  queue_y.setPrinter(Serial);
  
  grid_solved();

  /*
  while (!queue_x.isEmpty ())
    Serial.print(queue_x.dequeue());
  Serial.print('\t');
  while (!queue_y.isEmpty ())
    Serial.print(queue_y.dequeue ());  */
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

//////////////////////////sensors reading//////////////////

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
void readsensors_block(){
  b_detect=analogRead(A5);
}

/////////////////////////error map////////////////////////////

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

//////////////////////////////pid///////////////////////

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

bool check_proximity(){
  //Serial.println('c');
  readsensors_block();
  if(b_detect<400){
    Serial .println("b_detect");
    return true; 
  }
  return false;
}

/////////////////////////turn function//////////////////////

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

void slow_pid(){
  Serial.println("slow_pid");
  readsensors();
  error_map();

  pd = 20*error + 80*(error - prev_error);
 
  lms = 90 + pd;
  rms = 90 - pd;

  if(lms>=120)
  {
   lms=120;
  }
 
  else if(lms<=0)
  {
   lms=0;
  }
   
  if(rms>=120)
  {
   rms=120;
  }
  
  else if(rms<=0)
  {
   rms=0;
  }

  analogWrite(lm1,lms);
  analogWrite(lm2,0);
  analogWrite(rm1,rms);
  analogWrite(rm2,0);

  prev_error = error;

}
