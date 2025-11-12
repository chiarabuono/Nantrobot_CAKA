#include <Arduino.h>
#include <math.h>

#define EncoderPin1A 22
#define EncoderPin1B 23
#define motorRforward 19
#define motorRbackward 18

#define EncoderPin2A 4
#define EncoderPin2B 21
#define motorLforward 16
#define motorLbackward 17

float const pi = 3.141592653589793;
int avoidance_state = 0;

int state = 1;
/*
  state 0: no obstacles - go straight ahead
  state 1: obstacles - turning
  state 2: turned enough, go straight ahead for a second
  state 3: align again with the target
*/

// sonar pins
#define trigPin 0
#define echoPin 0

float duration, distance;
float distance_to_move = 0.0;
float radians_to_turn = 0.0;
float safe_dist = 15;     // [cm]
float prev_dist = 0;      // [cm] obstacle from the robot

struct point {
  float x;
  float y;
  float theta;            // theta = 0 then robot moving along positive x
};

point robot_pos = {0, 0, 0};
point destination_point = {2, 3, 0};

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


float compute_distance(point start_pos, point end_pos) {
  return std::sqrt(pow((start_pos.x - end_pos.x), 2) + pow((start_pos.y - end_pos.y), 2));
}

float compute_radians(point start_pos, point end_pos) {
  float delta_x = start_pos.x - end_pos.x;
  float delta_y = start_pos.y - end_pos.y;
  float rel_angle = atan2(delta_y, delta_x);

  return rel_angle - start_pos.theta;
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

void obstacle_avoidance() {

}


void setup() {
  // set up motor pins
  pinMode(motorRforward, OUTPUT);
  pinMode(motorRbackward, OUTPUT);
  pinMode(motorLforward, OUTPUT);
  pinMode(motorLbackward, OUTPUT);

  // set up sonar pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);

  distance_to_move = compute_distance(robot_pos, destination_point);
  radians_to_turn = compute_radians(robot_pos, destination_point);

}

void go_to_target() {

}

void loop() {
  float dist = read_sonar();

  switch (avoidance_state){
    case 0:
      if (dist < safe_dist) {
        avoidance_state = 1;
      break;
      }
      go_to_target();
      break;
  
    case 1:
      obstacle_avoidance();
      break;
  }
  

}

/*
  state 0: no obstacles - go straight ahead
  state 1: obstacles - turning
  state 2: turned enough, go straight ahead for a second
  state 3: align with the target
*/
