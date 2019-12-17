void loop() {
  if (queue_x.isEmpty() && queue_y.isEmpty()) {
    brake();
    delay(10000);
  }
  else {
    if (pos == 100) {
      x_follow();
    }
    else if (pos == 101) {
      y_follow();
    }
  }

}

