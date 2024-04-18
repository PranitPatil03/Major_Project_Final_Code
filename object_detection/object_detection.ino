#include <TinyGPS++.h>            
#include <SoftwareSerial.h>       

float depth = 0, distance = 0;

bool flag = 0;

float depth_threshold = 20, distance_threshold = 10;

float duration; 

const int floorWet = A0, DTrig = 12, DEcho = 3, DiTrig = 4, DiEcho = 5, buzz = 13, sms = 2;
                         
void setup() 
{
  Serial.begin(9600);
  pinMode(DTrig, OUTPUT);                                                                   
  pinMode(DEcho, INPUT);                                                                    
  pinMode(DiTrig, OUTPUT);                                                                  
  pinMode(DiEcho, INPUT);                                                                   
  pinMode(buzz, OUTPUT);
  attachInterrupt(0, flagpost, LOW);
}

void loop() 
{
  measure_ultrasonic();
  Serial.print(depth);
  Serial.print(" , ");
  Serial.print(distance);
  Serial.println("");
}

void flagpost()
{
  flag = 1;
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
