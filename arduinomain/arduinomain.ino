#include <AccelStepper.h>
#include <Servo.h>
Servo servoRIGHT;
Servo servoLEFT;
Servo servoKOLENO;
#define SENSOR_LINE_PIN_LEFT 4
#define SENSOR_LINE_PIN_MID 5
#define SENSOR_LINE_PIN_RIGHT 6

//расстояние в мм
//Написать значение переменных:
int s = 12;
int x = 12;
int y = 12;
int w = 12;
int h = 12;
int n = 12;

String incomingByte;
int counter = 0;
int order = 0;
String ans;
int count_lines = 0;
int count_nechet = 0;

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

  servoRIGHT.attach(3);
  servoLEFT.attach(9);
  servoKOLENO.attach(11);

  // ПОМЕНЯТЬ ПОД ПАРАМЕТРЫ /настройка скорости и ускорения шаговых двигателей
  stepper1.setMaxSpeed(200);
  stepper1.setAcceleration(100);
  stepper2.setMaxSpeed(200);
  stepper2.setAcceleration(100);
  stepper3.setMaxSpeed(200);
  stepper3.setAcceleration(100);

  Serial.begin(115200);
  
}

/*Додумать!!!!*/
void move_back() {
  /*Движение прямо*/
  bool signal_left = digitalRead(SENSOR_LINE_PIN_LEFT);
  bool signal_mid = digitalRead(SENSOR_LINE_PIN_MID);
  bool signal_right = digitalRead(SENSOR_LINE_PIN_RIGHT);
  if (!signal_mid && !signal_left && !signal_right){
    servoLEFT.write(0);
    servoRIGHT.write(180);
    c++;
    return 1;
  }
  else {
    return 0;
  }
}

void move_forward() {
  /*Движение прямо*/
  bool signal_left = digitalRead(SENSOR_LINE_PIN_LEFT);
  bool signal_mid = digitalRead(SENSOR_LINE_PIN_MID);
  bool signal_right = digitalRead(SENSOR_LINE_PIN_RIGHT);
  if (!signal_mid && !signal_left && !signal_right){
    servoLEFT.write(0);
    servoRIGHT.write(180);
    return 1;
  }
  else {
    return 0;
  }
}

void turn_right(){
  /*Поворот направо*/
  servoRIGHT.write(180);//ВПИСАТЬ УГЛЫ
  servoLEFT.write(0);
  delay(7800);
  servoRIGHT.write(90);//ВПИСАТЬ УГЛЫ
  servoLEFT.write(90);
}

void turn_right(){
  /*Поворот направо*/
  servoRIGHT.write(0);//ВПИСАТЬ УГЛЫ
  servoLEFT.write(180);
  delay(7800);
  servoRIGHT.write(90);//ВПИСАТЬ УГЛЫ
  servoLEFT.write(90);
}
void reverse(){
  /*Функция поворота*/
  servoRIGHT.write(36);//ВПИСАТЬ УГЛЫ
  servoLEFT.write(-36);
}

void QR_low_moving_to_pos() {
  /*Для задачи положения манипулятора для нижней полки*/
  // ОТРЕДАКТИРОВАТЬ  движение колен 
  servoKOLENO.write();

  stepper2.moveTo(); 
  stepper2.runToPosition();

  stepper3.moveTo(); 
  stepper3.runToPosition();
}

void QR_answer() {
  Serial.println("QR");
  delay(50);
  ans = Serial.readString();
  return (ans);
}

void QR_low_moving_back() {
  // Пауза 1 секунда
  delay(1000);

  // движение обратно
  servoKOLENO.write(0);

  stepper2.moveTo(0);
  stepper2.runToPosition();

  stepper3.moveTo(0);
  stepper3.runToPosition();
}

void QR_high_moving_to_pos() {
  /*Для задачи положения манипулятора для верхней полки*/
  // ОТРЕДАКТИРОВАТЬ  движение колен 
  servoKOLENO.write();

  stepper2.moveTo(); 
  stepper2.runToPosition();

  stepper3.moveTo();
  stepper3.runToPosition();
}
  
/*Написать движение манипулятора*/
void QR_high_moving_back() {
  delay(1000);

  // движение обратно
  servoKOLENO.write(0);

  stepper2.moveTo(0);
  stepper2.runToPosition();

  stepper3.moveTo(0);
  stepper3.runToPosition();
}


/*
Объяснение ( ):
  Робот должен встать в ту точку, где должна происходить выгрузка в зависимости от номера заказа (Переменная order)
  Далее происходит выгрузка в эту точку в завимости от количества деталек в его багажнике(Переменная counter)
*/
//Написать движение робота + коленей для каждого из номера заказов
void load_out(int order, int counter) {
  if (order == 1) {
    /*Написать маршрут до точки выгрузки*/
    move_forward();
    turn_left();
  }
  if (order == 2) {
    /*Написать маршрут до точки выгрузки*/
    move_forward();
    turn_left();
  }
  if (order == 3) {
    /*Написать маршрут до точки выгрузки*/
    move_forward();
    turn_left();
  }
  if (order == 4) {
    /*Написать маршрут до точки выгрузки*/
    move_forward();
    turn_left();
  }

  while (counter > 0) {
    //Для кажого из ветвления надо будет написать свое положение манипулятора
    if (counter == 1) {
      stepper2.moveTo(); 
      stepper2.runToPosition();
  
      stepper3.moveTo();
      stepper3.runToPosition();
      delay(1000);
      servoKOLENO.write(180);//отпустил, вписать угл
      delay(1000);
    }
    if (counter == 2) {
      stepper2.moveTo(); 
      stepper2.runToPosition();
  
      stepper3.moveTo();
      stepper3.runToPosition();
      delay(1000);
      servoKOLENO.write(180);//отпустил, вписать угл
      delay(1000);
    }
    if (counter == 3){
      stepper2.moveTo(); 
      stepper2.runToPosition();
  
      stepper3.moveTo();
      stepper3.runToPosition();
      delay(1000);
      servoKOLENO.write(180);//отпустил, вписать угл
      delay(1000);
    }
    if (counter == 4){
      stepper2.moveTo(); 
      stepper2.runToPosition();
  
      stepper3.moveTo();
      stepper3.runToPosition();
      delay(1000);
      servoKOLENO.write(180);//отпустил, вписать угл
      delay(1000);
    }
    counter = counter - 1;
  }
  reverse();
  if (order == 1) {
    /* написать маршрут обратно в точку S*/
    move_forward();
    turn_right();
  }
  if (order == 2) {
    /* написать маршрут обратно в точку S*/
    move_forward();
    turn_right();
  }
  if (order == 3) {
    /* написать маршрут обратно в точку S*/
    move_forward();
    turn_right();
  }
  if (order == 4) {
    /* написать маршрут обратно в точку S*/
    move_forward();
    turn_right();
  }
}
// Написать движение коленей для каждого из каунтеров Каунтеры - кол-во коробок
void load_in(int counter){
  //ВАЖНО! Дополнительно изначально мы задаем положение манипулятора, тк коробки будут идти и сверху, и снизу 
  servoKOLENO.write(36);//ВПИСАТЬ
  stepper2.moveTo(); 
  stepper2.runToPosition();

  stepper3.moveTo();
  stepper3.runToPosition();
  stepper1.moveTo(180); //поворот на 180
  stepper1.runToPosition();
  
  if (counter == 1){
//загрузка В багажник
    stepper2.moveTo(); 
    stepper2.runToPosition();

    stepper3.moveTo();
    stepper3.runToPosition();
    delay(1000);
    servoKOLENO.write(180);//отпустил, вписать угл
    delay(1000);

  }
  if (counter == 2){
   //загрузка В багажник
    stepper1.moveTo(); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(); 
    stepper2.runToPosition();

    stepper3.moveTo();
    stepper3.runToPosition();
    delay(1000);
    servoKOLENO.write(180);//отпустил, вписать угл
    delay(1000);
  }
  if (counter == 3){
    //загрузка В багажник
    stepper1.moveTo(); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(); 
    stepper2.runToPosition();

    stepper3.moveTo();
    stepper3.runToPosition();
    delay(1000);
    servoKOLENO.write(180);//отпустил, вписать угл
    delay(1000);
  }
  if (counter == 4){
    //загрузка В багажник
    stepper1.moveTo(); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(); 
    stepper2.runToPosition();

    stepper3.moveTo();
    stepper3.runToPosition();
    delay(1000);
    servoKOLENO.write(180);//отпустил, вписать угл
    delay(1000);
  }
  stepper1.moveTo(0); //в аргументы функции дописать положение
  stepper1.runToPosition();

  stepper2.moveTo(0);     
  stepper2.runToPosition();

  stepper3.moveTo(0);
  stepper3.runToPosition();
  delay(1000);

  servoKOLENO.write(0);
}

//Здесь нужно больше кода. Манипулятор должен не только закинуть на верхнее звено коробку, но и поднять ее, не уронив полку
void take_high() {
  //Для захвата коробки на верхней полке
  stepper2.moveTo(); 
  stepper2.runToPosition();

  stepper3.moveTo(); 
  stepper3.runToPosition();

  servoKOLENO.write(180)//взял 
  delay(1000);

  stepper2.moveTo(0);
  stepper2.runToPosition();

  stepper3.moveTo(0);
  stepper3.runToPosition();
}


//Здесь нужно больше кода. Манипулятор должен не только закинуть на верхнее звено коробку, но и поднять ее, не уронив полку, а потом положить в багажник
void take_low() {
   //Для захвата коробки на нижней полке
  stepper2.moveTo(); 
  stepper2.runToPosition();

  stepper3.moveTo(); 
  stepper3.runToPosition();

  servoKOLENO.write(180)//взял 
  delay(1000)


  stepper1.moveTo(0);
  stepper1.runToPosition();

  stepper2.moveTo(0);
  stepper2.runToPosition();

  stepper3.moveTo(0);
  stepper3.runToPosition();
}

void loop() {
  delay(100);
  if (Serial.available() > 0) {
    incomingByte = Serial.readString();
    if (incomingByte == "START") {
      order = order + 1;
      bool signal_left = digitalRead(SENSOR_LINE_PIN_LEFT);
      bool signal_mid = digitalRead(SENSOR_LINE_PIN_MID);
      bool signal_right = digitalRead(SENSOR_LINE_PIN_RIGHT);
      if (signal_left && signal_right && !signal_mid) {
        servoLEFT.write(0);
        servoRIGHT.write(180);
        delay(500);
      }
      count_lines++;
      count_nechet++;
      int x = 1;
      while (x) {
        move_forward();
        x = move_forward();
      }
      count_lines++;
      count_nechet++;
      servoLEFT.write(90);
      servoRIGHT.write(90);
      stepper1.moveTo(0);
      stepper1.runToPosition();
      QR_low_moving_to_pos();
      delay(100);
      ans = QR_answer();
      delay(100);
      QR_low_moving_back();
      if (ans == "TAKE"){
        take_low();
        counter = counter + 1;
        load_in(counter);
      }
      QR_high_moving_to_pos();
      delay(100);
      ans = QR_answer();
      delay(100);
      QR_high_moving_back();
      if (ans == "TAKE"){
        take_high();
        counter = counter + 1;
        load_in(counter);
      }
      stepper1.moveTo(0);
      stepper1.runToPosition();
      QR_low_moving_to_pos();
      delay(100);
      ans = QR_answer();
      delay(100);
      QR_low_moving_back();
      if (ans == "TAKE"){
        take_low();
        counter = counter + 1;
        load_in(counter);
      }
      QR_high_moving_to_pos();
      delay(100);
      ans = QR_answer();
      delay(100);
      QR_high_moving_back();
      if (ans == "TAKE"){
        take_high();
        counter = counter + 1;
        load_in(counter);
      }
      int x = 1;
      while (x) {
        move_forward();
        x = move_forward();
      }
      count_lines++;
      count_nechet++;
      load_out(order, counter);
      //move_back
      Serial.println("END");
      count_lines = 0;
      count_nechet = 0;
  }
}
