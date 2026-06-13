import processing.serial.*;

Serial myPort;

String event="SYSTEM READY";
String token="-";
String seat="-";

int revenue=0;
int passengers=0;
int busCount=0;

int[] seats=new int[10];

PFont f;

void setup(){
size(1300,750);

println(Serial.list());
myPort=new Serial(this,Serial.list()[0],9600);
myPort.bufferUntil('\n');

f=createFont("Arial Bold",20);
textFont(f);
}

void draw(){

background(15,20,35);

drawHeader();
drawSeats();
drawStats();
drawFooter();
drawAlerts();
}

// ================= HEADER =================
void drawHeader(){

fill(0,255,220);
textSize(34);
text("SMART METRO BUS CONTROL SYSTEM",280,40);

fill(255);
textSize(16);
text("Prepared by Student - IMSG Dhoke Jerrani",470,70);

stroke(0,255,255);
line(50,85,1250,85);
}

// ================= SEATS =================
void drawSeats(){

fill(255);
textSize(24);
text("LIVE SEAT STATUS",520,130);

for(int i=1;i<=9;i++){

int x=90*i+40;
int y=180;

if(seats[i]==1)
fill(255,60,60);      // occupied
else
fill(60,255,80);      // free

stroke(255);
strokeWeight(2);
rect(x,y,80,80,15);

fill(0);
textSize(26);
text(i,x+30,y+48);

fill(255);
textSize(14);

if(seats[i]==1)
text("BOOKED",x+12,y+105);
else
text("FREE",x+25,y+105);
}
}

// ================= DASHBOARD =================
void drawStats(){

fill(255);
textSize(24);
text("SYSTEM DASHBOARD",80,380);

fill(0,200,255);
rect(60,420,300,70,15);

fill(255);
textSize(22);
text("EVENT : "+event,75,463);


// Token
fill(255,170,0);
rect(60,510,300,70,15);

fill(0);
text("TOKEN : "+token,75,553);


// Seat
fill(120,255,120);
rect(60,600,300,70,15);

fill(0);
text("SEAT : "+seat,75,643);


// Right Side Stats
fill(255);
textSize(22);

text("Passengers Entered : "+passengers,700,430);
text("Revenue Collected : Rs "+revenue,700,490);
text("Bus Completed : "+busCount,700,550);

int available=9-countBooked();
text("Available Seats : "+available,700,610);
}

// ================= ALERT =================
void drawAlerts(){

if(event.equals("BUS FULL")){

fill(255,0,0);
textSize(38);
text("BUS FULL - WAIT FOR NEXT BUS",350,720);
}
}

// ================= FOOTER =================
void drawFooter(){

fill(180);
textSize(14);
text("Arduino + Keypad + LCD + Servo + Ultrasonic + Processing Interface",350,740);
}

// ================= COUNT BOOKED =================
int countBooked(){

int c=0;

for(int i=1;i<=9;i++){
if(seats[i]==1)c++;
}

return c;
}

// ================= SERIAL =================
void serialEvent(Serial p){

String data=p.readStringUntil('\n');

if(data==null)return;

data=trim(data);

// BOOKED
if(data.startsWith("BOOKED")){

String[] parts=split(data,',');

seat=parts[1];
token=parts[2];

seats[int(seat)]=1;

event="SEAT RESERVED";
}

// GATE
if(data.equals("GATE_OPEN")){

event="PASSENGER ENTERED";
passengers++;
revenue+=100;
}

// FULL
if(data.equals("BUS_FULL")){

event="BUS FULL";
busCount++;
}

// RESET
if(data.equals("NEW_BUS")){

event="NEW BUS ARRIVED";

for(int i=0;i<10;i++)
seats[i]=0;

token="-";
seat="-";
}
}