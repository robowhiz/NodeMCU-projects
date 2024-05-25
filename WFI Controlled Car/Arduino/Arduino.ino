#include <Arduino.h>

#define RIGHT_FORWARD 3
#define RIGHT_BACKWARD 4
#define LEFT_FORWARD 5
#define LEFT_BACKWARD 6

void setup() {
  Serial.begin(9600);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACKWARD, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_BACKWARD, OUTPUT);
}

void loop() {
  while (Serial.available() > 0) {
    char data = Serial.read();
    if (data == 'f') {
      digitalWrite(RIGHT_FORWARD, HIGH);
      digitalWrite(RIGHT_BACKWARD, LOW);
      digitalWrite(LEFT_FORWARD, HIGH);
      digitalWrite(LEFT_BACKWARD, LOW);
    }

    else if (data == 'b') {
      digitalWrite(RIGHT_FORWARD, LOW);
      digitalWrite(RIGHT_BACKWARD, HIGH);
      digitalWrite(LEFT_FORWARD, LOW);
      digitalWrite(LEFT_BACKWARD, HIGH);
    }
    else if (data == 'r') {
      digitalWrite(RIGHT_FORWARD, LOW);
      digitalWrite(RIGHT_BACKWARD, HIGH);
      digitalWrite(LEFT_FORWARD, HIGH);
      digitalWrite(LEFT_BACKWARD, LOW);
    }

    else if (data == 'l') {
      digitalWrite(RIGHT_FORWARD, HIGH);
      digitalWrite(RIGHT_BACKWARD, LOW);
      digitalWrite(LEFT_FORWARD, LOW);
      digitalWrite(LEFT_BACKWARD, HIGH);
    }

    else if (data == 's') {
      digitalWrite(RIGHT_FORWARD, LOW);
      digitalWrite(RIGHT_BACKWARD, LOW);
      digitalWrite(LEFT_FORWARD, LOW);
      digitalWrite(LEFT_BACKWARD, LOW);
    }
  }
}