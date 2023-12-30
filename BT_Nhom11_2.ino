//Quạt
#include <Stepper.h>
int stepsPerRevolution = 2048;
Stepper myStepper = Stepper(stepsPerRevolution, 10, 12, 11, 13);
int poteniometer = A1;
int value, motorSpeed;

//Cảm biến ánh sáng
int cambien = A0;
int led = 4;
int ANALOG_THRESHOLD = 200;
int analogValue;


//Cửa cuốn
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int nutnhanlen = 5;
int nutnhanxuong = 5;

void setup() {
  pinMode(led, OUTPUT);

  //Quạt
  int value = 0;
  int motorSpeed = 0;

  //Cửa cuốn
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(nutnhanlen, INPUT_PULLUP);
  pinMode(nutnhanxuong, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  //Cảm biến ánh sáng
  analogValue = analogRead(A0);
  Serial.println(analogValue);
  if (analogValue > ANALOG_THRESHOLD)
    digitalWrite(led, LOW);
  else
    digitalWrite(led, HIGH);


  //Quạt
  value = analogRead(poteniometer);
  motorSpeed = map(value, 0, 1023, 0, 19);
  if (motorSpeed > 0) {
    myStepper.setSpeed(motorSpeed);
    myStepper.step(1);
  }

  //Cửa cuốn
  // int trangthainutlen = digitalRead(nutnhanlen);
  // int trangthainutxuong = digitalRead(nutnhanxuong);

  // if (trangthainutlen == 0 && trangthainutxuong != 0) {
  //   tien();
  // } else if (trangthainutlen != 0 && trangthainutxuong == 0) {
  //   lui();
  // } else {
  //   dung();
  // }
}


//Cửa cuốn
void tien() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void lui() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void dung() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
