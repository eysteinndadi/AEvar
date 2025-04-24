#include <Servo.h>    

//mótorar
const int motorPinLeftForward = 12;
const int motorPinLeftBackward = 13;
const int motorPinRightForward = 10;
const int motorPinRightBackward = 11;

//skynjari
const int trigPin = 6;
const int echoPin = 5;

long duration;
int distance;

bool movingForward = false;
bool movingBackward = false;
bool movingForwardRight = false;
bool movingForwardLeft = false;
bool movingBackwardLeft = false;
bool movingBackwardRight = false;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  //Gerir mótorana tilbúna
  pinMode(motorPinLeftForward, OUTPUT);
  pinMode(motorPinLeftBackward, OUTPUT);
  pinMode(motorPinRightForward, OUTPUT);
  pinMode(motorPinRightBackward, OUTPUT);
  
  //Gerir skynjaran tilbúinn
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  
  //skynjar fjarlægð fyrir framan sig og uppfærir distance breytuna
  senseDistance();
  if (distance < 20) {
    resetMovement();
    moveBackwardLeft();
    delay(600);
    resetMovement();
    moveForwardRight();
    delay(600);
    resetMovement();
  }
  else {
    moveForward();
  }

}

void senseDistance() {
  // Hreynsar trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Kveikir á trigPin í 10 míkrósekúndur
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Les af echoPin, skilar ferðatíma hljóðbylgjunnar í míkrósekúndum.
  duration = pulseIn(echoPin, HIGH);
  // Reiknar lengdina út í cm
  distance = duration * 0.034 / 2;

  // Skrifar lengdina á skjáinn
  Serial.print("Distance: ");
  Serial.println(distance);
}

void moveForward() {
  if (movingForward == false) {
    movingForward = true;
    digitalWrite(motorPinLeftForward, HIGH);
    digitalWrite(motorPinLeftBackward, LOW);
    digitalWrite(motorPinRightForward, HIGH);
    digitalWrite(motorPinRightBackward, LOW);
  }  
}

void moveBackward() {
  if (movingBackward == false) {
    movingBackward = true;
    digitalWrite(motorPinLeftForward, LOW);
    digitalWrite(motorPinLeftBackward, HIGH);
    digitalWrite(motorPinRightForward, LOW);
    digitalWrite(motorPinRightBackward, HIGH);
  }  
}

void moveForwardRight() {
  if (movingForwardRight == false) {
    movingForwardRight = true;
    digitalWrite(motorPinLeftForward, HIGH);
    digitalWrite(motorPinLeftBackward, LOW);
    digitalWrite(motorPinRightForward, LOW);
    digitalWrite(motorPinRightBackward, LOW);
  }
}

void moveForwardLeft() {
  if (movingForwardLeft == false) {
    movingForwardLeft = true;
    digitalWrite(motorPinLeftForward, LOW);
    digitalWrite(motorPinLeftBackward, LOW);
    digitalWrite(motorPinRightForward, HIGH);
    digitalWrite(motorPinRightBackward, LOW);
  }
}

void moveBackwardLeft() {
  if (movingBackwardLeft == false) {
    movingBackwardLeft = true;
    digitalWrite(motorPinLeftForward, LOW);
    digitalWrite(motorPinLeftBackward, LOW);
    digitalWrite(motorPinRightForward, LOW);
    digitalWrite(motorPinRightBackward, HIGH);
  }
}

void moveBackwardRight() {
  if (movingBackwardRight == false) {
    movingBackwardRight = true;
    digitalWrite(motorPinLeftForward, LOW);
    digitalWrite(motorPinLeftBackward, HIGH);
    digitalWrite(motorPinRightForward, LOW);
    digitalWrite(motorPinRightBackward, LOW);
  }
}

void resetMovement() {
  movingForward = false;
  movingBackward = false;
  movingForwardRight = false;
  movingForwardLeft = false;
  movingBackwardLeft = false;
  movingBackwardRight = false;

  digitalWrite(motorPinLeftForward, LOW);
  digitalWrite(motorPinLeftBackward, LOW);
  digitalWrite(motorPinRightForward, LOW);
  digitalWrite(motorPinRightBackward, LOW);
}
