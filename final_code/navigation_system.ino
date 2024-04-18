#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

bool flag = 0;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  pinMode(4, INPUT_PULLUP);
  pinMode(2, OUTPUT);
}

void loop() 
{
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
      bleKeyboard.print("Navigate Me to ");
      delay(1000);
      bleKeyboard.print("Work using");
      delay(1000);
      bleKeyboard.print("Google Maps");
      bleKeyboard.write(KEY_RETURN);
      bleKeyboard.write(KEY_RETURN);
      bleKeyboard.releaseAll();
      delay(2000);
      flag = 0;
    }
  }
}