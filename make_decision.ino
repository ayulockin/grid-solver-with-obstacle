void make_decision(char dir, char prev_dir) {
  brake();
  delay(100);
  if (prev_dir == dir) {//just cross the present node
    straight();
    delay(30);
  }

  else if (prev_dir != dir) {
    if (flag == 0) {
      if (dir == 'E' && prev_dir == 'N') {//just right turn on that node
        sharp_right_turn();
        delay(400);
        readsensors();
        while (s4 != lc && s5 != lc) { 
          sharp_right_turn();
          readsensors();
        }
        brake();
      }
      else if (dir == 'N' && prev_dir == 'E') {//just left turn on that node
        sharp_left_turn();
        delay(400);              //to be tuned
        readsensors();
        while (s4 != lc && s5 != lc) { //right on cross
          sharp_left_turn();
          readsensors();
        }
        brake();
      }
      
    }
    else if (flag == 1) {
      if (dir == 'E' && prev_dir == 'N') {//just left turn on that node
        sharp_left_turn();
        delay(400);             
        readsensors();
        while (s4 != lc && s5 != lc) { 
          sharp_left_turn();
          readsensors();
        }
        brake();
      }
      else if (dir == 'N' && prev_dir == 'E') {//just right turn on that node
        sharp_right_turn();
        delay(400);             
        readsensors();
        while (s4 != lc && s5 != lc) { 
          sharp_right_turn();
          readsensors();
        }
        brake();
      }
    }
    else if (flag == 2) {
      if (dir == 'E' && prev_dir == 'N') {//just right turn on that node
        sharp_right_turn();
        delay(400);              
        readsensors();
        while (s4 != lc && s5 != lc) { 
          sharp_right_turn();
          readsensors();
        }
        brake();
      }
      else if (dir == 'N' && prev_dir == 'E') {//just left turn on that node
        sharp_left_turn();
        delay(400);              
        readsensors();
        while (s4 != lc && s5 != lc) { 
          sharp_left_turn();
          readsensors();
        }
        brake();
      }
    }
  }
}

