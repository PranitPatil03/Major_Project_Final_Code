#include <TinyGPS++.h>            
#include <SoftwareSerial.h>       

bool flag = 0;

int wettness = 0;

float duration; 

const int floorWet = A0, DTrig = 12, DEcho = 3, DiTrig = 4, DiEcho = 5, buzz = 13;
                         
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
  measure_wettness();
  if(wettness > 200)
  {
    floor_wet();
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
