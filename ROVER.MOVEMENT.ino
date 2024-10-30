#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
LiquidCrystal lcd(2,3,4,5,6,7);
#define sound A0
const int bz = A5;
const int m11 = 8;
const int m12 = 9;
const int m21 = 11;
const int m22 = 10;
const int up = A2;
const int down =A1;
const int open1 = A4;
const int close1 = A3;
const int ip = 13;
int x,y,s;
void setup()
{
  Serial.begin (115200);
  pinMode(sound,INPUT);
  pinMode(ip,INPUT_PULLUP);
  pinMode(bz, OUTPUT);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(up, OUTPUT);
  pinMode(down, OUTPUT);
  pinMode(open1, OUTPUT);
  pinMode(close1, OUTPUT);
  stop();
  lcd.begin(16,2);
  lcd.print("WELCOME TO PICK ");
  lcd.setCursor(0,1);
  lcd.print("AND PLACE ROBOT ");
  delay(1000);
  //Serial.print("WELCOME...");
  sensor_note();
 /* forward();
  delay(2000);
  stop();
  backward(); 
  delay(2000);
  stop();
  left();  
  delay(2000);
  stop();
  right();
  delay(2000);
  stop();
  up1();
  delay(2000);
  stop();
  down1();
  delay(2000);
  stop();
  open();
  delay(2000);
  stop();
  close();
  delay(2000);
  stop();*/
}

void loop() {
  x = digitalRead(sound);
  y = digitalRead(ip);
  if(y == LOW)
  {
    if(s < 1)
    Serial.println("1");
    delay(500);
    s=2;
  }
    while(Serial.available()> 0)
    {
      String str = Serial.readString();
      //lcd.setCursor(0,0);
      //lcd.print("SERVER IP");
      str.trim(); 
      if(s>0)
      {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SERVER IP");
    lcd.setCursor(0,1);  
    lcd.print(str);
    delay(2000);
    s=0;
    sensor_note();
    }
    if(str == "Forward")
    {
    forward();    
    }
    if(str == "Backward")
    {
    backward();    
    }
    if(str == "Left")
    {
    left();    
    }
    if(str == "Right")
    {
    right();    
    }
    if(str == "Stop")
    {
    stop();    
    }
    if(str == "Up")
    {
    up1();    
    }
    if(str == "Down")
    {
    down1();    
    }
    if(str == "Open")
    {
    open();    
    }
    if(str == "Close")
    {
    close();    
    }
  }
  if(x == HIGH )
  {
   digitalWrite(bz, LOW); 
   lcd.setCursor(6,0);
   lcd.print("YES ");
   delay(1000);
  }
  else
  {
  digitalWrite(bz, HIGH);   
  lcd.setCursor(6,0);
  lcd.print("NO ");
  delay(400);
  }
}
void sensor_note()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SOUND:    IP:");
  lcd.setCursor(0,1);
  lcd.print("STATUS:");
}
void forward()
{
    digitalWrite(bz, LOW);
    digitalWrite(m11, HIGH);
    digitalWrite(m12, LOW);
    digitalWrite(m21, HIGH);
    digitalWrite(m22, LOW);
    lcd.setCursor(7,1);
    lcd.print("FORWARD ");
}
void backward()
{
   digitalWrite(bz, LOW);
    digitalWrite(m11, LOW);
    digitalWrite(m12, HIGH);
    digitalWrite(m21, LOW);
    digitalWrite(m22, HIGH);
    lcd.setCursor(7,1);
    lcd.print("BACKWARD ");
}
void left()
{
    digitalWrite(bz, LOW);
    digitalWrite(m11, HIGH);
    digitalWrite(m12, LOW);
    digitalWrite(m21, LOW);
    digitalWrite(m22, HIGH);
    lcd.setCursor(7,1);
    lcd.print("LEFT   ");
}
void right()
{
    digitalWrite(bz, LOW);
    digitalWrite(m11, LOW);
    digitalWrite(m12, HIGH);
    digitalWrite(m21, HIGH);
    digitalWrite(m22, LOW);
    lcd.setCursor(7,1);
    lcd.print("RIGHT   ");
}
void stop()
{
    digitalWrite(bz, LOW);
    digitalWrite(m11, LOW);
    digitalWrite(m12, LOW);
    digitalWrite(m21, LOW);
    digitalWrite(m22, LOW);
    digitalWrite(up, LOW);
    digitalWrite(down, LOW);
    digitalWrite(open1, LOW);
    digitalWrite(close1, LOW);
    lcd.setCursor(7,1);
    lcd.print("STOP   ");
}
void open()
{
   digitalWrite(bz, LOW);
    digitalWrite(open1, HIGH);
    digitalWrite(close1, LOW);
    lcd.setCursor(7,1);
    lcd.print("OPEN ");
}
void close()
{
    digitalWrite(bz, LOW);
    digitalWrite(open1, LOW);
    digitalWrite(close1, HIGH);
    lcd.setCursor(7,1);
    lcd.print("CLOSE  ");
}
void up1()
{
    digitalWrite(bz, LOW);
    digitalWrite(up, HIGH);
    digitalWrite(down, LOW);
    lcd.setCursor(7,1);
    lcd.print("UP..  ");
}
void down1()
{
    digitalWrite(bz, LOW);
    digitalWrite(up, LOW);
    digitalWrite(down, HIGH);
    lcd.setCursor(7,1);
    lcd.print("DOWN..  ");
}
