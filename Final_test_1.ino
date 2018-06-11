//#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#define PIN_RADAR1 17
#define PIN_RADAR2 35
#define PIN_RADAR3 39

#define PIN_PIR1 34//#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#define PIN_RADAR1 17
#define PIN_RADAR2 35
#define PIN_RADAR3 39

#define PIN_PIR1 34
#define PIN_PIR2 25
#define PIN_PIR3 2

#define trig50 13 //Ultra Sonic
#define echo50 36

#define trig100 21
#define echo100 37

#define trig150 22
#define echo150 38



SSD1306  display(0x3c, 4, 15);
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;
long duration50, distance50,duration100, distance100,duration150, distance150;


void setup() {
  
  pinMode(PIN_RADAR1, INPUT);
  pinMode(PIN_RADAR2, INPUT);
  pinMode(PIN_RADAR3, INPUT);
  
  pinMode(PIN_PIR1,INPUT);
  pinMode(PIN_PIR2,INPUT);
  pinMode(PIN_PIR3,INPUT);
  
  pinMode(trig50, OUTPUT);
  pinMode(echo50, INPUT);
  pinMode(trig100, OUTPUT);
  pinMode(echo100, INPUT);
  pinMode(trig150, OUTPUT);
  pinMode(echo150, INPUT);
  Serial.begin(9600);
  
  pinMode(16,OUTPUT);
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50); 
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high
  
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
}

void drawText(int x, int y, char input_text[] ) {
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(x, y, input_text);
    
}


void loop() {
  display.clear ();
  
  int Motion1 = digitalRead(PIN_RADAR1);
  int Motion2 = digitalRead(PIN_RADAR2);
  int Motion3 = digitalRead(PIN_RADAR3);
  
  int PIR1 = digitalRead(PIN_PIR1);
  int PIR2 = digitalRead(PIN_PIR2);
  int PIR3 = digitalRead(PIN_PIR3);

  digitalWrite(trig50, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trig50, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trig50, LOW);
  duration50 = pulseIn(echo50, HIGH);
  distance50 = (duration50/2) / 29.1;

  digitalWrite(trig100, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trig100, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trig100, LOW);
  duration100 = pulseIn(echo100, HIGH);
  distance100 = (duration100/2) / 29.1;

  digitalWrite(trig150, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trig150, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trig150, LOW);
  duration150 = pulseIn(echo150, HIGH);
  distance150 = (duration150/2) / 29.1;



  
//Ultrasonic 1
if (distance50 < 4) {  // This is where the LED On/Off happens
     drawText(0,30,"Too close");
     Serial.println("Too close");
}
  else {
  }
  if (distance50 >= 300 || distance50 <= 0){
    drawText(0,30,"Out of range");
    Serial.println("Out of range");
  }
  else {
    display.drawString(64, 30, String(distance50) + " cm");
    Serial.print(distance50);
    Serial.println(" cm");
  }
  delay(300);


  //Ultrasonic 2
  if (distance100 < 4) {  // This is where the LED On/Off happens
     drawText(0,40,"Too close");
     Serial.println("Too close");
}
  else {
  }
  if (distance100 >= 300 || distance100 <= 0){
    drawText(0,40,"Out of range");
    Serial.println("Out of range");
  }
  else {
    display.drawString(64, 40, String(distance100) + " cm");
    Serial.print(distance100);
    Serial.println(" cm");
  }
  delay(300);


  // Utrasonic 3
  if (distance150 < 4) {  // This is where the LED On/Off happens
     drawText(0,50,"Too close");
     Serial.println("Too close");
}
  else {
  }
  if (distance150 >= 300 || distance150 <= 0){
    drawText(0,50,"Out of range");
    Serial.println("Out of range");
  }
  else {
    display.drawString(64, 50, String(distance150) + " cm");
    Serial.print(distance150);
    Serial.println(" cm");
  }
  delay(300);

  // Radar 1
  if (Motion1 == HIGH) {
    drawText(0,0,"R1 detected");
  // write the buffer to the display
    display.display();
    Serial.println("motion 1 detected");
  }
  else {
  drawText(0,0,"R1 not detected");
  display.display();
  Serial.println("NO motion 1 detected");
  }

  // Radar 2
  if (Motion2 == HIGH) {
    drawText(0,10,"R2 detected");
  // write the buffer to the display
    display.display();
    Serial.println("motion 2 detected");
  }
  else {
  drawText(0,10,"R2 not detected");
  display.display();
  Serial.println("NO motion 2 detected");
  }
  
  //Radar 3
  if (Motion3 == HIGH) {
   drawText(0,20,"R3 detected");
  // write the buffer to the display
    display.display();
    Serial.println("motion 3 detected");
  }
  else {
  drawText(0,20,"R3 NOT detected");
  display.display();
  Serial.println("NO motion 3 detected");
  }  
  delay(100);
  
  if(PIR1==HIGH)
  {
    drawText(60, 0, "P1 detected");
    display.display();
    Serial.println("");
  }
  else
  {
    drawText(60, 0, "P1 Not detected");
    display.display();
  }
  delay(100);
  

  if(PIR2==HIGH)
  {
    drawText(60, 10, "P2 detected");
    display.display();
    Serial.println("");
  }
  else
  {
    drawText(60, 10, "P2 Not detected");
    display.display();
  }
  delay(100);
  

  if(PIR3==HIGH)
  {
    drawText(60, 20, "P3 detected");
    display.display();
    Serial.println("");
  }
  else
  {
    drawText(60, 20, "P3 Not detected");
    display.display();
  }


  
}

#define PIN_PIR2 25
#define PIN_PIR3 2

#define trig50 13 //Ultra Sonic
#define echo50 36

#define trig100 14
#define echo100 37

#define trig150 27
#define echo150 38



SSD1306  display(0x3c, 4, 15);
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;
long duration50, distance50,duration100, distance100,duration150, distance150;


void setup() {
  
  pinMode(PIN_RADAR1, INPUT);
  pinMode(PIN_RADAR2, INPUT);
  pinMode(PIN_RADAR3, INPUT);
  
  pinMode(PIN_PIR1,INPUT);
  pinMode(PIN_PIR2,INPUT);
  pinMode(PIN_PIR3,INPUT);
  
  pinMode(trig50, OUTPUT);
  pinMode(echo50, INPUT);
  pinMode(trig100, OUTPUT);
  pinMode(echo100, INPUT);
  pinMode(trig150, OUTPUT);
  pinMode(echo150, INPUT);
  Serial.begin(9600);
  
  pinMode(16,OUTPUT);
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50); 
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high
  
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
}

void drawText(int x, int y, char input_text[] ) {
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(x, y, input_text);
    
}


void loop() {
  display.clear ();
  
  int Motion1 = digitalRead(PIN_RADAR1);
  int Motion2 = digitalRead(PIN_RADAR2);
  int Motion3 = digitalRead(PIN_RADAR3);
  
  int PIR1 = digitalRead(PIN_PIR1);
  int PIR2 = digitalRead(PIN_PIR2);
  int PIR3 = digitalRead(PIN_PIR3);

  digitalWrite(trig50, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trig50, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trig50, LOW);
  duration50 = pulseIn(echo50, HIGH);
  distance50 = (duration50/2) / 29.1;

  digitalWrite(trig100, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trig100, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trig100, LOW);
  duration100 = pulseIn(echo100, HIGH);
  distance100 = (duration100/2) / 29.1;

  digitalWrite(trig150, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trig150, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trig150, LOW);
  duration150 = pulseIn(echo150, HIGH);
  distance150 = (duration150/2) / 29.1;



  
//Ultrasonic 1
if (distance50 < 4) {  // This is where the LED On/Off happens
     drawText(0,30,"Too close");
     Serial.println("Too close");
}
  else {
  }
  if (distance50 >= 300 || distance50 <= 0){
    drawText(0,30,"Out of range");
    Serial.println("Out of range");
  }
  else {
    display.drawString(64, 30, String(distance50) + " cm");
    Serial.print(distance50);
    Serial.println(" cm");
  }
  delay(300);


  //Ultrasonic 2
  if (distance100 < 4) {  // This is where the LED On/Off happens
     drawText(0,40,"Too close");
     Serial.println("Too close");
}
  else {
  }
  if (distance100 >= 300 || distance100 <= 0){
    drawText(0,40,"Out of range");
    Serial.println("Out of range");
  }
  else {
    display.drawString(64, 40, String(distance100) + " cm");
    Serial.print(distance100);
    Serial.println(" cm");
  }
  delay(300);


  // Utrasonic 3
  if (distance150 < 4) {  // This is where the LED On/Off happens
     drawText(0,50,"Too close");
     Serial.println("Too close");
}
  else {
  }
  if (distance150 >= 300 || distance150 <= 0){
    drawText(0,50,"Out of range");
    Serial.println("Out of range");
  }
  else {
    display.drawString(64, 50, String(distance150) + " cm");
    Serial.print(distance150);
    Serial.println(" cm");
  }
  delay(300);

  // Radar 1
  if (Motion1 == HIGH) {
    drawText(0,0,"R1 detected");
  // write the buffer to the display
    display.display();
    Serial.println("motion 1 detected");
  }
  else {
  drawText(0,0,"R1 not detected");
  display.display();
  Serial.println("NO motion 1 detected");
  }

  // Radar 2
  if (Motion2 == HIGH) {
    drawText(0,10,"R2 detected");
  // write the buffer to the display
    display.display();
    Serial.println("motion 2 detected");
  }
  else {
  drawText(0,10,"R2 not detected");
  display.display();
  Serial.println("NO motion 2 detected");
  }
  
  //Radar 3
  if (Motion3 == HIGH) {
   drawText(0,20,"R3 detected");
  // write the buffer to the display
    display.display();
    Serial.println("motion 3 detected");
  }
  else {
  drawText(0,20,"R3 NOT detected");
  display.display();
  Serial.println("NO motion 3 detected");
  }  
  delay(100);
  
  if(PIR1==HIGH)
  {
    drawText(60, 0, "P1 detected");
    display.display();
    Serial.println("");
  }
  else
  {
    drawText(60, 0, "P1 Not detected");
    display.display();
  }
  delay(100);
  

  if(PIR2==HIGH)
  {
    drawText(60, 10, "P2 detected");
    display.display();
    Serial.println("");
  }
  else
  {
    drawText(60, 10, "P2 Not detected");
    display.display();
  }
  delay(100);
  

  if(PIR3==HIGH)
  {
    drawText(60, 20, "P3 detected");
    display.display();
    Serial.println("");
  }
  else
  {
    drawText(60, 20, "P3 Not detected");
    display.display();
  }


  
}
