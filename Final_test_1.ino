// smart barrier for msst2016 thesis
// hatran3e
#include <NewPing.h>

#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`

#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
//set config for sonar sensors
#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 400 // Maximum distance  cm
#define MIN_DISTANCE 3  // Minimum distance  cm
#define max_sample 20 // Maximum sample

//display or close on LCD 1/0: display/close
#define PIR 1
#define RADAR 1
#define SONAR 1

// sending to cloud
#define CLOUD 0

// Set these to send data
#define FIREBASE_HOST "yourhost.firebaseio.com"
#define FIREBASE_AUTH "your_key"
#define WIFI_SSID "Mi Max"
#define WIFI_PASSWORD "you_pwr"

// define pins
#define PIN_RADAR1 17
#define PIN_RADAR2 35
#define PIN_RADAR3 39

#define PIN_PIR1 34
#define PIN_PIR2 25
#define PIN_PIR3 2
//Ultra Sonic
#define trig50 13 
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

// define LCD display config
#define SDA    4
#define SCL   15
#define RST   16 //RST must be set by software
SSD1306  display(0x3c, SDA, SCL, RST);

//variables used in program
long  distance50, distance100, distance150;
int i;
int n = 0;

void setup() {
  
  //set up IO
  pinMode(PIN_RADAR1, INPUT);
  pinMode(PIN_RADAR2, INPUT);
  pinMode(PIN_RADAR3, INPUT);
  
  pinMode(PIN_PIR1,INPUT);
  pinMode(PIN_PIR2,INPUT);
  pinMode(PIN_PIR3,INPUT);

  //set up LCD
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

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void drawText(int x, int y, char* input_text ) {
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

#if(SONAR)
  //Ultrasonic 1
  for( i = 0; i<max_sample; i++)
  {
  delay(30); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  distance50+=sonar[0].ping_cm();
  }
  
  distance50=distance50/max_sample; //avarage distance
  
  if (distance50 < MIN_DISTANCE) { 
      display.drawString(0, 30, "Too close"); 
      drawText(0,30,"Too close");
      Serial.println("Sensor1: Too close");
  }
  else if (distance50 > MAX_DISTANCE || distance50 <= MIN_DISTANCE){
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
  
  distance100=distance100/max_sample;  //avarage distance

  if (distance100 < MIN_DISTANCE) {  
     drawText(0,40,"Too close");
     Serial.println("Sensor2: Too close");
  }
  else if (distance100 > MAX_DISTANCE || distance100 <= MIN_DISTANCE){
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
  
  distance150=distance150/max_sample; //avarage distance

  if (distance150 < MIN_DISTANCE) {  
     drawText(0,50,"Too close");
     Serial.println("Sensor3: Too close");
  }
  else if (distance150 > MAX_DISTANCE || distance150 <= MIN_DISTANCE){
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
#endif

#if(RADAR)
  // Radar 1
  if (Motion1 == HIGH) {
    drawText(0,0,"R1 YES");
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
    display.display();
    Serial.println("motion 3 YES");
  }
  else {
  drawText(0,20,"R3 NO");
  display.display();
  Serial.println("NO motion 3 YES");
  } 
  delay(500); //delay before display 
  #endif

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

#if(CLOUD)
  
  // set value
  Firebase.setFloat("distance50", distance50);
  Firebase.setFloat("distance100", distance100);
  Firebase.setFloat("distance150", distance150);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  /* // update value
  Firebase.setFloat("distance100", distance100);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000); */

  // get value 
  Serial.print("distance50: ");
  Serial.println(Firebase.getFloat("distance50"));
  delay(500);

  /* // remove value
  Firebase.remove("distance50");
  delay(1000); */

  // set string value
  //Firebase.setString("message", "hello world");
  // handle error
  /* if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000); */
  
  // set bool value
  Firebase.setBool("truth", false);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // append a new value to /logs
  String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(1000);
  
#endif
  
}
