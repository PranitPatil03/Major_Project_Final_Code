#include <TinyGPS++.h>            
#include <SoftwareSerial.h>       
#include <BleKeyboard.h>
TinyGPSPlus gps;
SoftwareSerial gpsSerial(7, 6);   
SoftwareSerial gsmSerial(8, 9);   

BleKeyboard bleKeyboard;

bool flag = 0;

float depth = 0, distance = 0;

bool flag = 0;

float depth_threshold = 20, distance_threshold = 10; 

int wettness = 0;

float duration;

const int floorWet = A0, DTrig = 12, DEcho = 3, DiTrig = 4, DiEcho = 5, buzz = 13, sms = 2;

const String phone = "+918698437788";                              

void setup() 
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  pinMode(4, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  gsmSerial.begin(9600);
  gpsSerial.begin(9600);
  pinMode(floorWet, INPUT); 
  pinMode(DTrig, OUTPUT);                                                                   
  pinMode(DEcho, INPUT);                                                                    
  pinMode(DiTrig, OUTPUT);                                                                 
  pinMode(DiEcho, INPUT);                                                                  
  pinMode(buzz, OUTPUT);
  pinMode(sms, INPUT_PULLUP);
  attachInterrupt(0, flagpost, LOW);
}

void loop() 
{
  measure_ultrasonic();
  measure_wettness();
  Serial.print(depth);
  Serial.print(" , ");
  Serial.print(distance);
  Serial.println("");
  if(flag == 1)
  {
    while (gpsSerial.available() > 0)
      if (gps.encode(gpsSerial.read())) 
      {
        if (gps.location.isValid()) 
        {
          gsmSerial.println("AT+CMGF=1");
          delay(1000);
          beep();
          gsmSerial.println("AT+CMGS=\""+phone+"\"\r"); 
          delay(1000);
          beep();
          gsmSerial.println("NEED HELP!!!");
          gsmSerial.print("http://maps.google.com/maps?q=loc:");      
          gsmSerial.print(gps.location.lat(), 6);                     
          gsmSerial.print(",");                                       
          gsmSerial.print(gps.location.lng(), 6);                     
          delay(1000);                                                
          beep();
          gsmSerial.write((char)26); //sms sent
          flag = 0;
          beep();
        }
      }
  }
  if(depth > depth_threshold) 
  {
    High_Depth(); //beep codes
  }
  if(distance < distance_threshold)
  {
    Low_Distance();
  }
  if(wettness > 200)
  {
    floor_wet();
  }

 if(digitalRead(4) == 0)
  {
    flag = 1;  
  }
  if(flag == 0)
  {
    digitalWrite(2, LOW);
  }
  if(flag == 1)
  {
    if(bleKeyboard.isConnected()) 
    {
      digitalWrite(2, HIGH);
      delay(1000);
      digitalWrite(2, LOW);
      bleKeyboard.write(KEY_LEFT_GUI);
      delay(2000);
      bleKeyboard.print("Navigate Me to");
      delay(1000);
      bleKeyboard.print(" Work using");
      delay(1000);
      bleKeyboard.print(" Google Maps");
      bleKeyboard.write(KEY_RETURN);
      bleKeyboard.write(KEY_RETURN);
      bleKeyboard.releaseAll();
      delay(2000);
      flag = 0;
    }
  }

}

void flagpost()
{
  flag = 1;
}

void measure_wettness()
{
  wettness = analogRead(A0);
}

void measure_ultrasonic()
{
  digitalWrite(DTrig, LOW); 
  digitalWrite(DiTrig, LOW); 
  delayMicroseconds(2);  
  digitalWrite(DTrig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(DTrig, LOW); 
  duration = pulseIn(DEcho, HIGH);
  depth = duration * 0.0172;
  digitalWrite(DiTrig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(DiTrig, LOW); 
  duration = pulseIn(DiEcho, HIGH);
  distance = duration * 0.0172;
}

void beep()
{
  digitalWrite(buzz, HIGH);
  delay(50);
  digitalWrite(buzz, LOW);
}

void floor_wet()
{
  digitalWrite(buzz, HIGH);   
  delay(150);
  digitalWrite(buzz, LOW);    
  delay(500);                 
}

void High_Depth() 
{
  digitalWrite(buzz, HIGH);   
  delay(150);
  digitalWrite(buzz, LOW);    
  delay(150);
  digitalWrite(buzz, HIGH);   
  delay(150);
  digitalWrite(buzz, LOW);    
  delay(500);                 
}

void Low_Distance() 
{
  digitalWrite(buzz, HIGH);   
  delay(150);
  digitalWrite(buzz, LOW);    
  delay(150);
  digitalWrite(buzz, HIGH);   
  delay(150);
  digitalWrite(buzz, LOW);    
  delay(150);
  digitalWrite(buzz, HIGH);   
  delay(150);
  digitalWrite(buzz, LOW);   
  delay(500);                 
}