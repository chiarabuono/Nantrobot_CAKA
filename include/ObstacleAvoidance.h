#include <Arduino.h>
int state = 1;
/*
  state 0: obstacles - turning
  state 1: turned enough, go straight ahead for a second
*/


void obstacle_avoidance();