#include <Servo.h>
#include <AccelStepper.h>
Servo servoRIGHT;
Servo servoLEFT;
Servo S1;
Servo S2;
#define SENSOR_LINE_PIN_LEFT 4
#define SENSOR_LINE_PIN_MID 5
#define SENSOR_LINE_PIN_RIGHT 6

String incomingByte;
int counter = 0;
int order = 0;
String ans;

const int buttonPin1 = A0; // Пин для кнопки
const int stepPin1 = 16;// // Пин для сигнала шага 1-16 2-18 3-20
const int dirPin1 = 15; // Пин для направления 1-15 2-17 3-19

const int buttonPin2 = A3; // Пин для кнопки
const int stepPin2 = 18;// // Пин для сигнала шага 1-16 2-18 3-20
const int dirPin2 = 17; // Пин для направления 1-15 2-17 3-19

const int buttonPin3 = A2; // Пин для кнопки
const int stepPin3 = 20;// // Пин для сигнала шага 1-16 2-17 3-19
const int dirPin3 = 19; // Пин для направления 1-15 2-18 3-20

AccelStepper stepper1(AccelStepper::DRIVER, stepPin1, dirPin1);
AccelStepper stepper2(AccelStepper::DRIVER, stepPin2, dirPin2);
AccelStepper stepper3(AccelStepper::DRIVER, stepPin3, dirPin3);


void to_detect_high(){
  String data;
  stepper3.moveTo(1350+start_pos_stepper3);
  stepper3.runToPosition();
  S2.write(20);
  delay(800);
  S2.write(91);
  stepper2.moveTo(-2700+start_pos_stepper2);
  stepper2.runToPosition();
  S2.write(180);
  while (data != 'a1a2a3'){
    delay(150);
    Serial.println("CikKL");
    to_detect_high();
  }
  String s = data[18];
  n = toInt(s);
  String sa1 = data[9::12];
  String sa2 = data[12::15];
  String sa3 = data[15::18];
  int a1, a2, a3;
  a1 = toInt(sa1);
  a2 = toInt(sa2);
  a3 = toInt(sa3);
  for (i = 0, i < n, i++){
    to_detect_high();
    hand_take_high(a1, a2, a3);
  }
}

void to_detect_low(){
  String data;
  stepper3.moveTo(1350+start_pos_stepper3);
  stepper3.runToPosition();
  S2.write(20);
  delay(800);
  S2.write(91);
  stepper2.moveTo(-2700+start_pos_stepper2);
  stepper2.runToPosition();
  S2.write(180);
  while (data != 'a1a2a3'){
    delay(150);
    Serial.println("CikKL");
    to_detect_low();
  }
  String s = data[18];
  n = toInt(s);
  String sa1 = data[9::12];
  String sa2 = data[12::15];
  String sa3 = data[15::18];
  int a1, a2, a3;
  a1 = toInt(sa1);
  a2 = toInt(sa2);
  a3 = toInt(sa3);
  for (i = 0, i < n, i++){
    to_detect_low();
    hand_take_low(a1, a2, a3);
  }
}

void moving(){
    bool signal_left = digitalRead(SENSOR_LINE_PIN_LEFT);
    bool signal_mid = digitalRead(SENSOR_LINE_PIN_MID);
    bool signal_right = digitalRead(SENSOR_LINE_PIN_RIGHT);
    while ((!signal_mid && signal_left && signal_right)||((!signal_mid && !signal_left && signal_right)||(signal_mid && !signal_left && signal_right))||((!signal_mid && signal_left && !signal_right)||(signal_mid && signal_left && !signal_right))){
      bool signal_left = digitalRead(SENSOR_LINE_PIN_LEFT);
      bool signal_mid = digitalRead(SENSOR_LINE_PIN_MID);
      bool signal_right = digitalRead(SENSOR_LINE_PIN_RIGHT);
      if (!signal_mid && signal_left && signal_right){
        servoLEFT.write(0);
        servoRIGHT.write(180);

      }
      if ((!signal_mid && !signal_left && signal_right)||(signal_mid && !signal_left && signal_right)){
          servoLEFT.write(180); //0
          servoRIGHT.write(180); //180
      }
      if ((!signal_mid && signal_left && !signal_right)||(signal_mid && signal_left && !signal_right)){
          servoLEFT.write(0); //0
          servoRIGHT.write(0); //180
      }
      if (!signal_mid && !signal_left && !signal_right) {
        break;
      }
      delay(300);
      servoLEFT.write(90); //0
      servoRIGHT.write(90);
    }
}

void hand_take_low(int a1, int a2, int a3){
  //delay(5000);
  steps1 = degreestosteps(a1);
  steps2 = degreestosteps(a2);
  steps3 = degreestosteps(a3);
    long start_pos_stepper1 = stepper1.currentPosition();
    long start_pos_stepper2 = stepper2.currentPosition();
    long start_pos_stepper3 = stepper3.currentPosition();
    stepper1.moveTo(steps1+start_pos_stepper1);
    stepper1.runToPosition();    
    S1.write(120);
    stepper3.moveTo(steps2+start_pos_stepper3);
    stepper3.runToPosition();
    S2.write(20);
    delay(800);
    S2.write(91);
    stepper2.moveTo(steps3+start_pos_stepper2);
    stepper2.runToPosition();
    S2.write(100);
    delay(2000);

    delay(1000);
    /*
    stepper3.moveTo(1900+start_pos_stepper3);
    stepper3.runToPosition();*/
    stepper2.moveTo(-1700+start_pos_stepper2);
    stepper2.runToPosition();
    stepper3.moveTo(700+start_pos_stepper3);
    stepper3.runToPosition();
    stepper2.moveTo(start_pos_stepper2);
    stepper2.runToPosition();
    stepper3.moveTo(start_pos_stepper3);
    stepper3.runToPosition();
    stepper1.moveTo(6600+4700+start_pos_stepper1);
    stepper1.runToPosition();
    delay(3000);
    S1.write(70);
    S2.write(20);
    delay(700);
    S2.write(92);
    S1.write(90);
    delay(2000);
    servoLEFT.write(0);
    servoRIGHT.write(180);
    delay(1700);
    servoLEFT.write(90);
    servoRIGHT.write(90);
}

int degreestosteps(int a){
  return (a/180*28000)
}

void hand_take_high(int a1, int a2, int a3){
  steps1 = degreestosteps(a1);
  steps2 = degreestosteps(a2);
  steps3 = degreestosteps(a3);
    long start_pos_stepper1 = stepper1.currentPosition();
    long start_pos_stepper2 = stepper2.currentPosition();
    long start_pos_stepper3 = stepper3.currentPosition();
    stepper1.moveTo(a1+start_pos_stepper1);
    stepper1.runToPosition();    
    S1.write(85);
    stepper3.moveTo(a3+start_pos_stepper3);
    stepper3.runToPosition();
    S2.write(20);
    delay(800);
    S2.write(91);
    stepper2.moveTo(a2+start_pos_stepper2);
    stepper2.runToPosition();
    S2.write(180);
    delay(2000);
    //Корзина
    stepper3.moveTo(1900+start_pos_stepper3);
    stepper3.runToPosition();
    stepper2.moveTo(-1700+start_pos_stepper2);
    stepper2.runToPosition();
    stepper3.moveTo(1300+start_pos_stepper3);
    stepper3.runToPosition();
    stepper2.moveTo(start_pos_stepper2);
    stepper2.runToPosition();
    stepper3.moveTo(start_pos_stepper3);
    stepper3.runToPosition();
    stepper1.moveTo(6600+4700+start_pos_stepper1);
    stepper1.runToPosition();
    delay(3000);
    S1.write(70);
    S2.write(20);
    delay(700);
    S2.write(92);
    S1.write(90);
    //servoLEFT.write(90);
    //servoRIGHT.write(90);
  
  delay(2000);/*
  S1.write(80);
  S2.write(200);
  stepper2.moveTo(-1700+start_pos_stepper2);
  stepper2.runToPosition();
  stepper2.moveTo(start_pos_stepper2);
  stepper2.runToPosition();
  stepper3.moveTo(700+start_pos_stepper3);
  stepper3.runToPosition();
  S1.write(80);
  //положить в корзину

  stepper3.moveTo(start_pos_stepper3);
  stepper3.runToPosition();
  stepper1.moveTo(6000+4700+start_pos_stepper1);
  stepper1.runToPosition();
  delay(3000);
  
  S2.write(80);
  delay(1000);
  S1.write(55);
  delay(1000);
  S2.write(100);
  delay(1000);
  stepper3.moveTo(1300+start_pos_stepper3);
  stepper3.runToPosition();*/
  servoLEFT.write(0);
  servoRIGHT.write(180);
  delay(1700);
  servoLEFT.write(90);
  servoRIGHT.write(90);
  }
}
void check_QR_high(){
  //moving to qr 
  String data_qr = Serial.readString();
  Serial.print("You sent me to qr: ");
  Serial.println(data_qr);
  while ((data_qr != 'TAKE')||(data_qr != 'NOTAKE')){
    delay(150);
    Serial.println("CKL");
    check_QR_high();
  }
  if (data_qr == ""){
    check_QR_high();
  }
  if (data_qr == 'TAKE'){
    String s = String(data_qr);
    String s_last = String(s[4]);
    int n = s_last.toInt();
    Serial.println(n);
    to_detect_high();
  }
}

void check_QR_low(){
  //moving to qr 
  String data_qr = Serial.readString();
  Serial.print("You sent me to qr: ");
  Serial.println(data_qr);
  while ((data_qr != 'TAKE')||(data_qr != 'NOTAKE')){
    delay(150);
    Serial.println("CKL");
    check_QR_low();
  }
  if (data_qr == ""){
    check_QR_low();
  }
  if (data_qr == 'TAKE'){
    String s = String(data_qr);
    String s_last = String(s[4]);
    int n = s_last.toInt();
    Serial.println(n);
    to_detect_low();
  }
  else if (data_qr == 'NOTAKE'){
    servoLEFT.write(0);
    servoRIGHT.write(180);
    delay(1700);
    servoLEFT.write(90);
    servoRIGHT.write(90);
  }
}

void to_upload(){
  long start_pos_stepper1 = stepper1.currentPosition();
  long start_pos_stepper2 = stepper2.currentPosition();
  long start_pos_stepper3 = stepper3.currentPosition();
  stepper1.moveTo(6600+4000+start_pos_stepper1);
  stepper1.runToPosition();
  stepper3.moveTo(1500+start_pos_stepper3);
  stepper3.runToPosition();
  stepper2.moveTo(-1700+start_pos_stepper2);
  stepper2.runToPosition();
  stepper3.moveTo(700+start_pos_stepper3);
  stepper3.runToPosition();
  stepper2.moveTo(start_pos_stepper2);
  stepper2.runToPosition();
  stepper3.moveTo(-100+start_pos_stepper3);
  stepper3.runToPosition();
  delay(3000);
  S2.write(33);    
  delay(2000);
  S2.write(91);
  S1.write(60);
  delay(5000);
  S2.write(120);
  delay(1000);
  S2.write(95);
  stepper3.moveTo(1300+start_pos_stepper3);
  stepper3.runToPosition();    
  stepper2.moveTo(-1600+start_pos_stepper2);
  stepper2.runToPosition();
  stepper1.moveTo(1200+start_pos_stepper1);
  stepper1.runToPosition();
  stepper2.moveTo(-2200+start_pos_stepper2);
  stepper2.runToPosition();
  S2.write(30);
  delay(300);
  S2.write(90);
}

int count = 0;
void first() {
  if (Serial.available() > 0) {
    String data = Serial.readString();
    Serial.print("You sent me: ");
    Serial.println(data);
    while (data != 'START'){
      Serial.println("CIKL");
      delay(300);
      first();
    }
    
    moving();
    //servoLEFT.write(90); //0
    //servoRIGHT.write(90); 
    check_QR_high();
    check_QR_low();
    moving();
    //servoLEFT.write(90); //0
    //servoRIGHT.write(90); 
    check_QR_high();
    check_QR_low();
    moving();
    servoLEFT.write(0);
    servoRIGHT.write(180);
    delay(1700);
    servoLEFT.write(90);
    servoRIGHT.write(90);
    moving();
    to_upload();
    moving();
  }
  
  //count = count+1;
  /*
  stepper1.disableOutputs();
  stepper2.disableOutputs();
  stepper3.disableOutputs();*/
  /*
  bool signal_left = digitalRead(SENSOR_LINE_PIN_LEFT);
  bool signal_mid = digitalRead(SENSOR_LINE_PIN_MID);
  bool signal_right = digitalRead(SENSOR_LINE_PIN_RIGHT);
  if (!signal_mid && signal_left && signal_right){
      servoLEFT.write(0);
      servoRIGHT.write(180);
 
  }
  if ((!signal_mid && !signal_left && signal_right)||(signal_mid && !signal_left && signal_right)){
      servoLEFT.write(180); //0
      servoRIGHT.write(180); //180
  }
  if ((!signal_mid && signal_left && !signal_right)||(signal_mid && signal_left && !signal_right)){
      servoLEFT.write(0); //0
      servoRIGHT.write(0); //180
  }1
  if (!signal_mid && !signal_left && !signal_right) {
    hand_take();
  }
  delay(300);
  servoLEFT.write(90); //0
  servoRIGHT.write(90);*/
}

void setup() {
  Serial.begin(9600);
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

  digitalWrite(stepPin1, HIGH);
  digitalWrite(dirPin1, LOW); // Устанавливаем направление вращения //low-1 high-2

  servoRIGHT.attach(9);
  servoLEFT.attach(11);
  S1.attach(12);
  S2.attach(37);
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(600);
  stepper2.setMaxSpeed(600);
  stepper2.setAcceleration(300);
  stepper3.setMaxSpeed(700);
  stepper3.setAcceleration(500);
}

void loop(){
  first();
}
      count_lines = 0;
      count_nechet = 0;
  }
}
