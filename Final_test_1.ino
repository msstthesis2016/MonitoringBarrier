#include <NewPing.h>

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 400 // Maximum distance  cm
#define MIN_DISTANCE 3  // Minimum distance  cm
#define max_sample 20 // Maximum sample
#define PIR 0
#define RADAR 0
/*
#define FIREBASE_HOST "safe-barrier.firebaseapp.com" //Thay bằng địa chỉ firebase của bạn
#define FIREBASE_AUTH ""   //Không dùng xác thực nên không đổi
#define WIFI_SSID "ten_wifi"   //Thay wifi và mật khẩu
#define WIFI_PASSWORD "mat_khau"
*/

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


NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(trig50, echo50, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(trig100, echo100, MAX_DISTANCE), 
  NewPing(trig150, echo150, MAX_DISTANCE)
};

SSD1306  display(0x3c, 4, 15);
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;
long duration50, distance50,duration100, distance100,duration150, distance150;
int i;

void setup() {
  
  pinMode(PIN_RADAR1, INPUT);
  pinMode(PIN_RADAR2, INPUT);
  pinMode(PIN_RADAR3, INPUT);
  
  pinMode(PIN_PIR1,INPUT);
  pinMode(PIN_PIR2,INPUT);
  pinMode(PIN_PIR3,INPUT);

  /*
  pinMode(trig50, OUTPUT);
  pinMode(echo50, INPUT);
  pinMode(trig100, OUTPUT);
  pinMode(echo100, INPUT);
  pinMode(trig150, OUTPUT);
  pinMode(echo150, INPUT);
  */
  
  
  
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


  /*
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
  */
    
    


  
  //Ultrasonic 1
  for( i = 0; i<max_sample; i++)
  {
  delay(30); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  distance50+=sonar[0].ping_cm();
  }
  distance50=distance50/max_sample;
  if (distance50 < 5) {  
     drawText(0,30,"Too close");
     Serial.println("Sensor1: Too close");
  }
  else {
  }
  if (distance50 > MAX_DISTANCE || distance50 <= MIN_DISTANCE){
    drawText(0,30,"Out of range");
    Serial.println("Sensor1: Out of range");
  }
  else {
    display.drawString(64, 30, String(distance50) + " cm");
    display.display();
    Serial.print("Sensor1: ");
    Serial.print(distance50);
    Serial.print(" cm   ");
  }
  


  //Ultrasonic 2
  for( i = 0; i<max_sample; i++)
  {
  delay(30); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  distance100+=sonar[0].ping_cm();
  }
  distance100=distance100/max_sample;  //distance100=sonar[1].ping_cm();

  if (distance100 < 5) {  
     drawText(0,40,"Too close");
     Serial.println("Sensor2: Too close");
}
  else {
  }
  if (distance100 > MAX_DISTANCE || distance100 <= MIN_DISTANCE){
    drawText(0,40,"Out of range");
    Serial.println("Sensor2: Out of range");
  }
  else {
    display.drawString(64, 40, String(distance100) + " cm");
    display.display();
    Serial.print("Sensor2: ");
    Serial.print(distance100);
    Serial.print(" cm  ");
  }
  


  // Utrasonic 3
  for( i = 0; i<max_sample; i++)
  {
  delay(30); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  distance150+=sonar[0].ping_cm();
  }
  distance150=distance150/max_sample;

  if (distance150 < 5) {  
     drawText(0,50,"Too close");
     Serial.println("Sensor3: Too close");
  }
  else {
  }
  if (distance150 > MAX_DISTANCE || distance150 <= MIN_DISTANCE){
    drawText(0,50,"Out of range");
    Serial.println("Sensor3: Out of range");
  }
  else {
    display.drawString(64, 50, String(distance150) + " cm");
    display.display();
    Serial.print("Sensor3: ");
    Serial.print(distance150);
    Serial.print(" cm");
    Serial.println(" ");
  }
  

  delay(500);//delay before display

  #if(RADAR)
  // Radar 1
  if (Motion1 == HIGH) {
    drawText(0,0,"R1 YES");
  // write the buffer to the display
    display.display();
    Serial.println("motion 1 YES");
  }
  else {
  drawText(0,0,"R1 NO");
  display.display();
  Serial.println("NO motion 1 YES");
  }

  // Radar 2
  if (Motion2 == HIGH) {
    drawText(0,10,"R2 YES");
  // write the buffer to the display
    display.display();
    Serial.println("motion 2 YES");
  }
  else {
  drawText(0,10,"R2 NO");
  display.display();
  Serial.println("NO motion 2 YES");
  }
  
  //Radar 3
  if (Motion3 == HIGH) {
   drawText(0,20,"R3 YES");
  // write the buffer to the display
    display.display();
    Serial.println("motion 3 YES");
  }
  else {
  drawText(0,20,"R3 NO");
  display.display();
  Serial.println("NO motion 3 YES");
  }  
  #endif
  delay(500); //delay before display

  #if(PIR)
  
  if(PIR1==HIGH)
  {
    drawText(60, 0, "P1 YES");
    display.display();
    Serial.println("P1 YES");
  }
  else
  {
    drawText(60, 0, "P1 NO");
    display.display();
    Serial.println("P1 NO");
  }

  if(PIR2==HIGH)
  {
    drawText(60, 10, "P2 YES");
    display.display();
    Serial.println("P2 YES");
  }
  else
  {
    drawText(60, 10, "P2 NO");
    display.display();
    Serial.println("P2 NO");
  }
  
  

  if(PIR3==HIGH)
  {
    drawText(60, 20, "P3 YES");
    display.display();
    Serial.println("P3 YES");
  }
  else
  {
    drawText(60, 20, "P3 NO");
    display.display();
    Serial.println("P3 NO");
  }
  delay(500);//delay before display
  
  #endif
  
}
