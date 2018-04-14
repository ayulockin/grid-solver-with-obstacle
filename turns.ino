
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

