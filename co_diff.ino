void co_diff() {
  queue_x.push('N');
  for (i = 0; i < abs(end_x - start_x); i++) {
    queue_x.push('E');
  }

  for (i = 0; i < abs(end_y - start_y); i++) {
    queue_y.push('N');
  }
  //queue_x.push('N');
  //queue_y.push('N');
}

