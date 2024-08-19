/* Написать функции:
  load_in() -> int counter
  load_out() -> int order
  take_high()
  take_low()
*/

#include <AccelStepper.h>
int w = 20;
int counter = 0;
int s, x, y, w, h, n;
/*
  Написать значение переменных:
s = 12;
x = 12;
y = 12;
w = 12;
h = 12;
n = 12;
*/
String incomingByte;
int counter = 0;
int order = 0;
String ans;

#define IN1 5 //ПРАВАЯ(или левая) СЕРВА
#define IN2 4
#define ENA 3

#define IN3 9//ЛЕВАЯ(или правая) СЕРВА
#define IN4 7
#define ENB 6
//ДОПИСАТЬ КОЛЕНО!!!

//пины для шаговых
const int stepPin1 = 2;  // пин шага для двигателя 1
const int dirPin1 = 3;  // пин направления для двигателя 1
const int stepPin2 = 4;  // пин шага для двигателя 2
const int dirPin2 = 5;  // пин направления для двигателя 2
const int stepPin3 = 6;  // пин шага для двигателя 3
const int dirPin3 = 7;  // пин направления для двигателя 3

// ОТРЕДАКТИРОВАТЬ шаг в один оборот для немы17
const int stepsPerRevolution = 200;

//  объект accelstepper для каждого двигателя
AccelStepper stepper1(AccelStepper::DRIVER, stepPin1, dirPin1);
AccelStepper stepper2(AccelStepper::DRIVER, stepPin2, dirPin2);
AccelStepper stepper3(AccelStepper::DRIVER, stepPin3, dirPin3);

void setup() {

  pinMode(ENA, OUTPUT); // шаг 1 сервы ПРАВАЯ(или левая, поменяем)
  pinMode(IN1, OUTPUT); // пин 1 сервы ПРАВАЯ(или левая, поменяем)
  pinMode(IN2, OUTPUT); // пин 1 сервы ПРАВАЯ(или левая, поменяем)
  pinMode(ENB, OUTPUT);// шаг 2 сервы ЛЕВАЯ(или правая, поменяем)
  pinMode(IN3, OUTPUT);// пин 2 сервы ЛЕВАЯ(или правая, поменяем)
  pinMode(IN4, OUTPUT);// пин 2 сервы ЛЕВАЯ(или правая, поменяем)
  //дописать колено

  // ПОМЕНЯТЬ ПОД ПАРАМЕТРЫ /настройка скорости и ускорения шаговых двигателей
  stepper1.setMaxSpeed(200);
  stepper1.setAcceleration(100);
  stepper2.setMaxSpeed(200);
  stepper2.setAcceleration(100);
  stepper3.setMaxSpeed(200);
  stepper3.setAcceleration(100);

  Serial.begin(9600);
  
}

int way_to_degrees(int way) {
  /*Перевод из миллиметров в градусы*/

  double diff = way/127.;
  int degree = diff*360/5;
  return (degree);
}

void move_forward(int arg) {
  /*Движение прямо*/

  digitalWrite(IN1, HIGH); //1 серва(правая или левая допишем)
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH); //2 серва(правая или левая допишем)
  digitalWrite(IN4, LOW);
  //дописать колено

  int full_way = way_to_degrees(arg);

  analogWrite(ENA, full_way);
  analogWrite(ENB, full_way);
  
}

void turn_right(){
  /*Поворот направо*/

  digitalWrite(IN1, HIGH); //1 серва(правая или левая допишем)
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH); //2 серва (правая или левая допишем)
  digitalWrite(IN4, LOW);
//дописать колено
  
  /*Изменить параметры*/
  analogWrite(ENB, 18); //поменять на ENA, если ENB-правый
  analogWrite(ENA, -18); //поменять на ENB, если ENA-правый
}

void turn_left(){
  /*Поворот налево*/

  digitalWrite(IN1, HIGH); //1 серва(правая или левая допишем)
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH); //2 серва (правая или левая допишем)
  digitalWrite(IN4, LOW);
  //дописать колено

  /*Изменить параметры*/
  analogWrite(ENB, -18); //поменять на ENA, если ENA-правый
  analogWrite(ENA, 18); //поменять на ENB, если ENB-правый
}

void reverse(){
  /*Функция поворота*/
  
  digitalWrite(IN1, HIGH); //1 серва(правая или левая допишем)
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH); //2 серва (правая или левая допишем
  digitalWrite(IN4, LOW);
  //дописать колено

  /*Изменить параметры*/
  analogWrite(ENB, -36);
  analogWrite(ENA, 36);
}

void QR_low_moving_to_pos() {
  /*Для задачи положения манипулятора для нижней полки, передачи и чтению данных с малины*/
  // ОТРЕДАКТИРОВАТЬ  движение колен 
  stepper1.moveTo(); //в аргументы функции дописать положение
  stepper1.runToPosition();

  stepper2.moveTo(); //в аргументы функции дописать положение
  stepper2.runToPosition();

  stepper3.moveTo(); //в аргументы функции дописать положение
  stepper3.runToPosition();
}

void QR_answer() {
  Serial.println("QR");
  delay(50);
  ans = Serial.readString();
  return ans;
}

void QR_low_moving_back() {
  // Пауза 1 секунда
  delay(1000);

  // движение обратно
  stepper1.moveTo(0);
  stepper1.runToPosition();

  stepper2.moveTo(0);
  stepper2.runToPosition();

  stepper3.moveTo(0);
  stepper3.runToPosition();
}

void QR_high_moving_to_pos() {
  /*Для задачи положения манипулятора для верхней полки, передачи и чтению данных с малины*/

  /*Написать движение манипулятора*/
  // ОТРЕДАКТИРОВАТЬ  движение колен 
  stepper1.moveTo(); //в аргументы функции дописать положение
  stepper1.runToPosition();

  stepper2.moveTo(); //в аргументы функции дописать положение
  stepper2.runToPosition();

  stepper3.moveTo(); //в аргументы функции дописать положение
  stepper3.runToPosition();

  
/*Написать движение манипулятора*/
void QR_high_moving_back() {
  delay(1000);

  // движение обратно
  stepper1.moveTo(0);
  stepper1.runToPosition();

  stepper2.moveTo(0);
  stepper2.runToPosition();

  stepper3.moveTo(0);
  stepper3.runToPosition();
}

/* Написать движение робота + коленей для каждого из номера заказов
load_out(int order) {
  if (order == 1){

  }
  if (order == 2){
    
  }
  if (order == 3){
    
  } 
}
*/

/* Написать движение коленей для каждого из каунтеров
load_in(int counter){
  if (counter == 1){

  }
  if (counter == 2){

  }
  if (counter == 3){

  }
  if (counter == 4){

  }
}*/

void loop() {
  delay(100);
  if (Serial.available() > 0) {
    incomingByte = Serial.readString();
    if (incomingByte == "START") {
      order = order + 1;
      move_forward(y);
      QR_low_moving_back();
      delay(100);
      ans = QR_answer();
      delay(100);
      QR_low_moving_to_pos();
      if (ans == "TAKE"){
        take_low();
        counter = counter + 1;
        load_in(counter)
      QR_high_moving_back();
      delay(100);
      ans = QR_answer();
      delay(100);
      QR_high_moving_to_pos();
      if (ans == "TAKE"){
        take_high();
        counter = counter + 1;
        load_in(counter)
      turn_right();
      move_forward(w/2+n);
      turn_left();
      move_forward(h);
      turn_left();
      move_forward(w/2+n);
      turn_right();
      QR_low_moving_back();
      delay(100);
      ans = QR_answer();
      delay(100);
      QR_low_moving_to_pos();
      if (ans == "TAKE"){
        take_low();
        counter = counter + 1;
        load_in(counter)
      }
      QR_low_moving_back();
      delay(100);
      ans = QR_answer();
      delay(100);
      QR_low_moving_to_pos();
      if (ans == "TAKE"){
        take_high();
        counter = counter + 1;
        load_in(counter)
      }
      turn_left();
      move_forward(w/2+x);
      turn_right();
      move_forward();
      load_out(order);
      reverse();
      Serial.println("END");
  }
}
