//#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#define PIN_RADAR 17

#define PIN_PIR 34

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
  
  pinMode(PIN_PIR,INPUT);
  pinMode(trig50, OUTPUT);
  pinMode(echo50, INPUT);
  pinMode(trig100, OUTPUT);
  pinMode(echo100, INPUT);
  pinMode(trig150, OUTPUT);
  pinMode(echo150, INPUT);
  Serial.begin(9600);
  pinMode(PIN_RADAR, INPUT);
  
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

void drawTextDetect() {
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Motion detected");
}
void drawTextNoDetect() {
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "No Motion detected");
}

void loop() {
  display.clear ();
  
  int Motion = digitalRead(PIN_RADAR);
  int PIR = digitalRead(PIN_PIR);

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



  

if (distance50 < 4) {  // This is where the LED On/Off happens
     drawText(0,20,"Too close");
     Serial.println("Too close");
}
  else {
  }
  if (distance50 >= 300 || distance50 <= 0){
    drawText(0,20,"Out of range");
    Serial.println("Out of range");
  }
  else {
    display.drawString(64, 20, String(distance50) + " cm");
    Serial.print(distance50);
    Serial.println(" cm");
  }
  delay(300);

  if (distance50 < 4) {  // This is where the LED On/Off happens
     drawText(0,20,"Too close");
     Serial.println("Too close");
}
  else {
  }
  if (distance50 >= 300 || distance50 <= 0){
    drawText(0,20,"Out of range");
    Serial.println("Out of range");
  }
  else {
    display.drawString(64, 20, String(distance50) + " cm");
    Serial.print(distance50);
    Serial.println(" cm");
  }
  delay(300);

//  if (Motion == HIGH) {
//    drawTextDetect();
//  // write the buffer to the display
//    display.display();
//    Serial.println("motion detected");
//  }
//  else {
//  drawTextNoDetect() ;
//  display.display();
//  Serial.println("NO motion detected");
//  }
//  
//  delay(100);
//  Serial.println(PIR);
//  if(PIR==HIGH)
//  {
//    drawText(0, 50, "Human detected");
//    display.display();
//    Serial.println("");
//  }
//  else
//  {
//    drawText(0, 50, "No Human detected");
//    display.display();
//  }
//  delay(100);









  
  
}
