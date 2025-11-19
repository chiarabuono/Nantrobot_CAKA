#include <Arduino.h>

#define EncoderPin1A 22
#define EncoderPin1B 23
#define motorRforward 19
#define motorRbackward 18

#define EncoderPin2A 4
#define EncoderPin2B 21
#define motorLforward 16
#define motorLbackward 17

// sonar pins
#define trigPin 0
#define echoPin 0

//encoder counters
volatile long encoder1Count = 0;
volatile long encoder2Count = 0;

float duration, distance;

void stopmotors() {
  digitalWrite(motorRforward, LOW);
  digitalWrite(motorRbackward, LOW);
  digitalWrite(motorLforward, LOW);
  digitalWrite(motorLbackward, LOW);  
}

void move_forward() {
  digitalWrite(motorRforward, HIGH);
  digitalWrite(motorRbackward, LOW);
  digitalWrite(motorLforward, HIGH);
  digitalWrite(motorLbackward, LOW);  
}

void move_backward() {
  digitalWrite(motorRforward, LOW);
  digitalWrite(motorRbackward, HIGH);
  digitalWrite(motorLforward, LOW);
  digitalWrite(motorLbackward, HIGH);
}

void turn_left() {
  digitalWrite(motorRforward, HIGH);
  digitalWrite(motorRbackward, LOW);
  digitalWrite(motorLforward, LOW);
  digitalWrite(motorLbackward, HIGH);
}

void turn_right() {
  digitalWrite(motorRforward, LOW);
  digitalWrite(motorRbackward, HIGH);
  digitalWrite(motorLforward, HIGH);
  digitalWrite(motorLbackward, LOW);
}

float read_sonar() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.0343/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  // delay(100);

  return distance;
}

void encoder1ISR() {
  int stateM1C1 = digitalRead(EncoderPin1A);
  int stateM1C2 = digitalRead(EncoderPin1B);

  if (stateM1C1 == stateM1C2) {
    encoder1Count--;
  }
  else {
    encoder1Count++;
  }
}
void encoder2ISR() {
  int stateM2C1 = digitalRead(EncoderPin2A);
  int stateM2C2 = digitalRead(EncoderPin2B);

  if (stateM2C1==stateM2C2) {
    encoder2Count--;
  }
  else {
    encoder2Count++;
  }
}

float go_distance(float dist) {
  float steps = dist * 200;
  long startstep1 = encoder1Count;
  //long startstep2 = encoder2Count;
  long goalstep1 = startstep1 + (long)steps;
  //long goalstep2 = startstep2 + steps;
  if(steps > 0){
    if(goalstep1 < encoder1Count) {
      move_forward;
    }
    else{
      stopmotors;
    }
  }
  else if(steps<0){
    if(goalstep1>encoder1Count) {
      move_backward;
    }
    else{
      stopmotors;
    }
  }
  else{
    stopmotors;
  }
  delay(50);
  float dist_moved = (encoder1Count - startstep1) / 200;
  return dist_moved;
}

float turn_radians(float radians) {
  //SET TURN RADIUS HERE BASED OFF OF DISTANCE BETWEEN WHEELS
  float turn_radius = 8;

  float turn_dist = turn_radius * radians;
  float steps = turn_dist * 200;

  long startstep1 = encoder1Count;

  long goalstep1 = startstep1 + (long)steps;
  if (steps>0) {
    while(goalstep1 > encoder1Count) {
      turn_left;
      delay(50);
    }
  }
  else{
    while(goalstep1 < encoder1Count) {
      turn_right;
      delay(50);
    }
  }
  float rad_turned = (encoder1Count- startstep1) / (200 * turn_radius); 
  return rad_turned;
}

void setup() {
  Serial.begin(115200);

  // set up motor pins
  pinMode(motorRforward, OUTPUT);
  pinMode(motorRbackward, OUTPUT);
  pinMode(motorLforward, OUTPUT);
  pinMode(motorLbackward, OUTPUT);

  // set up sonar pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //encoder
  pinMode(EncoderPin1A, INPUT_PULLUP);
  pinMode(EncoderPin1B, INPUT_PULLUP);
  pinMode(EncoderPin2A, INPUT_PULLUP);
  pinMode(EncoderPin2B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(EncoderPin1A), encoder1ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(EncoderPin2A), encoder2ISR, CHANGE);
  
  

}

float distance_to_move = 5;
float radians_to_turn = 0;

void loop() {
  distance_to_move = distance_to_move - go_distance(distance_to_move);
  //radians_to_turn = radians_to_turn - turn_radians(radians_to_turn);
}
