#include <Servo.h>
#include <AccelStepper.h>

int angle1 = A1;
int angle2 = A2;

const int stepPin1 = 16;// // Пин для сигнала шага 1-16 2-18 3-20
const int dirPin1 = 15; // Пин для направления 1-15 2-17 3-19

const int stepPin2 = 18;// // Пин для сигнала шага 1-16 2-18 3-20
const int dirPin2 = 17; // Пин для направления 1-15 2-17 3-19

const int stepPin3 = 20;// // Пин для сигнала шага 1-16 2-17 3-19
const int dirPin3 = 19; // Пин для направления 1-15 2-18 3-20

AccelStepper stepper1(AccelStepper::DRIVER, stepPin1, dirPin1);
AccelStepper stepper2(AccelStepper::DRIVER, stepPin2, dirPin2);
AccelStepper stepper3(AccelStepper::DRIVER, stepPin3, dirPin3);



void first(){
  digitalWrite(stepPin2, HIGH);
  digitalWrite(dirPin2, HIGH); // Устанавливаем направление вращения //low-1 high-2
  while (analogRead(A0) != ??) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(1000); // Задержка между шагами
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(1000);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP); // Включаем подтягивающий резистор

  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(buttonPin2, INPUT_PULLUP);

  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(buttonPin3, INPUT_PULLUP);
  
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(600);
  stepper2.setMaxSpeed(600);
  stepper2.setAcceleration(300);
  stepper3.setMaxSpeed(700);
  stepper3.setAcceleration(500);
);
  first();
}

void loop() {
  // put your main code here, to run repeatedly:

}
