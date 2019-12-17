void x_follow() {
  while (!queue_x.isEmpty()) {
    line_follow();

    if (node()) {
      make_decision(queue_x.peek(), prev_dir);
      delay(100);
      while(!node){
        line_follow();  
      }
      if(node){
        queue_x.pop();
      }
    }
    else if (block()) {
       
    }
  }
  if(queue_x.isEmpty()){
    pos=101;
    return;
  }
}

