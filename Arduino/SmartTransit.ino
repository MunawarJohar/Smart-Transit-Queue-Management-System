#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo gate;

// ================= KEYPAD =================
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ================= SYSTEM =================
bool booked[10];
int queueSeat[10];
String tokenList[10];

int front = 0;
int rear = 0;
int token = 1;
int passengers = 0;

// ================= BUS =================
bool busFull = false;
unsigned long busFullStart = 0;
int waitTime = 15;

// ================= ULTRASONIC =================
#define TRIG 11
#define ECHO 12

// ================= ALERT =================
#define BUZZER A0
#define REDLED A1

void setup() {

Serial.begin(9600);

lcd.init();
lcd.backlight();

gate.attach(10);
gate.write(0);

pinMode(TRIG, OUTPUT);
pinMode(ECHO, INPUT);

pinMode(BUZZER, OUTPUT);
pinMode(REDLED, OUTPUT);

showSeats();
}

// ================= LOOP =================
void loop() {

if(busFull){
handleBusFull();
return;
}

booking();
gateSystem();
}

// ================= LCD FREE SEATS =================
void showSeats() {

lcd.clear();
lcd.print("Free Seats:");

lcd.setCursor(0,1);

for(int i=1;i<=9;i++){
if(!booked[i]){
lcd.print(i);
lcd.print(" ");
}
}
}

// ================= LOUD BEEP =================
void loudBeep(){

for(int i=0;i<3;i++){
tone(BUZZER, 3000);
delay(150);
noTone(BUZZER);
delay(80);
}
}

// ================= BOOKING =================
void booking() {

char key = keypad.getKey();

if(key>='1' && key<='9'){

int seat = key-'0';

// already booked
if(booked[seat]){

digitalWrite(REDLED, HIGH);

loudBeep();

lcd.clear();
lcd.print("Seat ");
lcd.print(seat);
lcd.print(" Booked");

lcd.setCursor(0,1);
lcd.print("Choose Other");

delay(1200);

digitalWrite(REDLED, LOW);

showSeats();
return;
}

// new booking
booked[seat]=true;

String tk=makeToken();

queueSeat[rear]=seat;
tokenList[rear]=tk;
rear++;

lcd.clear();
lcd.print("Seat ");
lcd.print(seat);

lcd.setCursor(0,1);
lcd.print(tk);

Serial.print("BOOKED,");
Serial.print(seat);
Serial.print(",");
Serial.println(tk);

delay(1200);

showSeats();
}
}

// ================= TOKEN =================
String makeToken(){

String t="A00";
t += String(token++);
return t;
}

// ================= GATE =================
void gateSystem(){

if(front>=rear)return;

long duration;
int dist;

digitalWrite(TRIG,LOW);
delayMicroseconds(2);

digitalWrite(TRIG,HIGH);
delayMicroseconds(10);
digitalWrite(TRIG,LOW);

duration=pulseIn(ECHO,HIGH);
dist=duration*0.034/2;

if(dist>0 && dist<10){

gate.write(90);
delay(1000);
gate.write(0);

Serial.println("GATE_OPEN");

passengers++;
front++;

if(passengers>=4){
startBusFull();
}

delay(500);
}
}

// ================= BUS FULL =================
void startBusFull(){

busFull=true;
busFullStart=millis();

Serial.println("BUS_FULL");

lcd.clear();
lcd.print("BUS FULL");
delay(1000);
}

// ================= TIMER =================
void handleBusFull(){

int elapsed=(millis()-busFullStart)/1000;
int remaining=waitTime-elapsed;

static int last=-1;

if(remaining!=last){

lcd.clear();
lcd.print("BUS FULL");

lcd.setCursor(0,1);
lcd.print("Next:");
lcd.print(remaining);
lcd.print("s");

last=remaining;
}

if(remaining<=0){
resetBus();
busFull=false;
last=-1;
}
}

// ================= RESET =================
void resetBus(){

for(int i=0;i<10;i++){
booked[i]=false;
queueSeat[i]=0;
tokenList[i]="";
}

front=0;
rear=0;
passengers=0;

lcd.clear();
lcd.print("NEW BUS ARRIVED");

Serial.println("NEW_BUS");

delay(2000);

showSeats();
}