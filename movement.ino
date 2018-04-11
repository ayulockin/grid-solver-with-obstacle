void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

/////////////////error map/////////////////////

void error_map() {

  if ((s3 == sc) && ((s4 == lc) || (s5 == lc)) && (s6 == sc)) {
    error = 0;
  }

  else if ((s3 == sc) && (s4 == lc) && (s5 == lc) && (s6 == sc)) {
    error = 0;
  }

  else if ((s3 == lc) && (s4 == lc) && (s5 == sc) && (s6 == sc)) {
    error = -0.5;
  }

  else if ((s3 == lc) && (s4 == lc) && (s5 == lc) && (s6 == sc)) {
    error = -1.0;
  }

  else if ((s2 == lc) && (s3 == lc) && (s4 == sc) && (s5 == sc)) {
    error = -1.5;
  }

  else if ((s2 == lc) && (s3 == lc) && (s4 == lc) && (s5 == sc)) {
    error = -2.0;
  }

  else if ((s2 == lc) && (s3 == lc) && (s4 == lc) && (s5 == lc) && (s6 == sc)) {
    error = -2.5;
  }

  else if ((s1 == lc) && (s2 == lc) && (s3 == sc) && (s4 == sc) && (s5 == sc)) {
    error = -3.0;
  }

  else if ((s1 == lc) && (s2 == lc) && (s3 == lc) && (s4 == sc) && (s5 == sc)) {
    error = -3.5;
  }

  else if ((s1 == lc) && (s2 == lc) && (s3 == lc) && (s4 == lc) && (s5 == sc)) {
    error = -4.0;
  }

  else if ((s1 == lc) && (s2 == lc) && (s3 == lc) && (s4 == lc) && (s5 == lc) && (s6 == sc)) {
    error = -4.5;
  }
//////////////////end of negative errors////////////////////////////////////////////////

else if ((s3 == sc) && (s4 == sc) && (s5 == lc) && (s6 == lc)) {
    error = 0.5;
  }

  else if ((s3 == sc) && (s4 == lc) && (s5 == lc) && (s6 == lc)) {
    error = 1.0;
  }

  else if ((s7 == lc) && (s6 == lc) && (s5 == sc) && (s4 == sc)) {
    error = 1.5;
  }

  else if ((s7 == lc) && (s6 == lc) && (s5 == lc) && (s4 == sc)) {
    error = 2.0;
  }

  else if ((s7 == lc) && (s6 == lc) && (s5 == lc) && (s4 == lc) && (s3 == sc)) {
    error = 2.5;
  }

  else if ((s8 == lc) && (s7 == lc) && (s6 == sc) && (s5 == sc) && (s4 == sc)) {
    error = 3.0;
  }

  else if ((s8 == lc) && (s7 == lc) && (s6 == lc) && (s5 == sc) && (s4 == sc)) {
    error = 3.5;
  }

  else if ((s8 == lc) && (s7 == lc) && (s6 == lc) && (s5 == lc) && (s4 == sc)) {
    error = 4.0;
  }

  else if ((s8 == lc) && (s7 == lc) && (s6 == lc) && (s5 == lc) && (s4 == lc) && (s3 == sc)) {
    error = 4.5;
  }

/////////////////////////end of positive errors

}
