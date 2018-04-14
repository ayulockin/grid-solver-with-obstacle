bool block(){
  readsensors_block();
  if (b_detect < 400) {
    return true;
  }
  return false;
}

