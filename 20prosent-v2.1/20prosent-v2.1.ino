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

//Bluetooth
char incomingValue = 0;

bool movingForward = false;
bool movingBackward = false;
bool movingForwardRight = false;
bool movingForwardLeft = false;
bool movingBackwardLeft = false;
bool movingBackwardRight = false;

//ákveða hvort eigi að keyra sjálfkrafa eða nota Bluetooth
bool remoteControlled = true;


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

void moveForwardLeft() {
  if (movingForwardLeft == false) {
    movingForwardLeft = true;
    digitalWrite(motorPinLeftForward, LOW);
    digitalWrite(motorPinLeftBackward, LOW);
    digitalWrite(motorPinRightForward, HIGH);
    digitalWrite(motorPinRightBackward, LOW);
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

void resetMovement () {
  movingForward = false;
  movingBackward = false;
  movingForwardLeft = false;
  movingForwardRight = false;
  movingBackwardLeft = false;
  movingBackwardRight = false;

  digitalWrite(motorPinLeftForward, LOW);
  digitalWrite(motorPinLeftBackward, LOW);
  digitalWrite(motorPinRightForward, LOW);
  digitalWrite(motorPinRightBackward, LOW);
}

void senseDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
}

void remoteControl (char value) {
  switch (value) {
      case '0':
        resetMovement();
        break;
      case '1':
        moveForward();
        break;
      case '2':
        moveForwardRight();
        break;
      case '3':
        moveBackward();
        break;
      case '4':
        moveForwardLeft();
        break;
      case '5':
        moveBackwardLeft();
        break;
      case '6':
        moveBackwardRight();
        break;
      default:
        break;
    }
}

void selfDriving (int dist) {
  if (dist < 25) {
    resetMovement();
    moveBackwardLeft();
    delay(400);
    resetMovement();
    moveForwardRight();
    delay(400);
    resetMovement();
  }
  else {
    moveForward();
  }
}

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
  
  //Bíður eftir skilaboðum
  if (Serial.available() > 0) {

    //les skilaboðin
    incomingValue = Serial.read();
    Serial.print("Value: ");
    Serial.println(incomingValue);

    //Skoðar hvort eigi að breyta hvernig hann keyrir
    if (incomingValue == 's') {
      //breytir hvernig hann keyrir
      remoteControlled = !remoteControlled;
      //núllstillir Ævar
      resetMovement();
    }

    if (remoteControlled == true) {
    //ber skilaboðin saman við skipanir
    remoteControl(incomingValue);
    } 
  }

  if (remoteControlled == false) {
    //skynjar fjarlægð fyrir framan sig og uppfærir distance breytuna
    senseDistance();
    //ákveður hvert á að keyra
    selfDriving(distance);
  }

}

