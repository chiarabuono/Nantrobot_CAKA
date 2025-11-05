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

float duration, distance;

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

}

void loop() {
  /*
  turn_left();
  delay(500);
  turn_right();
  delay(1000);
  */

  //read_sonar();

}
