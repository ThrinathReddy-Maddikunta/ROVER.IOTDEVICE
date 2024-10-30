#include <WiFi.h>
#include "ThingSpeak.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <SPI.h> 
#include "DHT.h"
#define DHT11PIN 16
DHT dht(DHT11PIN, DHT11);
const char* ssid = "project";   // your network SSID (name) 
const char* password = "project1234";   // your network password
WiFiClient  client;
unsigned long myChannelNumber = 654604;
const char * myWriteAPIKey = "DPCN2JKMG8Q2X3ZP";
int tmp = 1,hm = 2,ms=3,wl=4;
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int ms1 = 36; 
const int wlvl = 39;
const int relay = 23;
int MS,WL=0;
float humi=0,temp = 0;
void setup() {
  Serial.begin(9600);  //Initialize serial
  pinMode(ms1,INPUT);
  pinMode(wlvl,INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay,LOW);// MOTOR OFF
  lcd.begin();         // initialize the lcd
  lcd.backlight();    // open the backlight
  welcome_note();
  Serial.println("STATION MODE");
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  lcd.setCursor(0,0);
  lcd.print("SSID:project");
  lcd.setCursor(0,1);
  lcd.print("PWD:project1234");
  delay(3000);
  sensors_name();
  dht.begin();
}
void loop() {
  MS = analogRead(ms1);
  MS = map(MS,0,4095,100,0);
  WL = analogRead(wlvl);
  WL = map(WL,0,4095,100,0); 
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(temp);
  lcd.setCursor(9,0);
  lcd.print("H:");
  lcd.print(humi); 
  lcd.setCursor(0,1);
  lcd.print("MS:");
  if(MS > 15)
  {
   lcd.print("WET "); 
   digitalWrite(relay,LOW);
   delay(500);
  }
  else
  {
   lcd.print("DRY ");
   digitalWrite(relay,HIGH); 
   delay(500);
  }
   
  lcd.setCursor(9,1);
  lcd.print("WL:");
  lcd.print(WL); 
  lcd.print("  "); 
  
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");int tmp = 1,hm = 2,ms=3,wl=4;
    }
    ThingSpeak.setField(tmp, temp);   // field  1
    ThingSpeak.setField(hm, humi);   //filed 2
    ThingSpeak.setField(ms, MS);   // field  3
    ThingSpeak.setField(wl, WL);   //filed 4
    //int x = ThingSpeak.writeField(myChannelNumber, field4, temperatureC, myWriteAPIKey);
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
}
void sensors_name()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.setCursor(9,0);
  lcd.print("H:");
  lcd.setCursor(0,1);
  lcd.print("MS:");
  lcd.setCursor(9,1);
  lcd.print("WL:");
}
void welcome_note()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WELCOME TO IOT");
  lcd.setCursor(0,1);
  lcd.print("BASED AGRICULTURE");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("FIELD MOITORING");
  lcd.setCursor(0,1);
  lcd.print("USING ESP32 ");
  delay(1000);
  lcd.clear();
}
