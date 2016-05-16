#include "LedControl.h"
#include "SPI.h"
#include "SD.h"
#include "LedPad.h"

const int DIN = 7;           //  выход данных с Arduino
const int CLK = 6;           //  частота синхронизации последовательной передачи данных Arduino
const int  CS = 5;           //  выбор Dot matrix module MAX7219
const int  ledCount = 4;     //  количество модулей  Dot matrix module MAX7219

const int fieldHeight = 8;
const int fieldWidth = 8 * ledCount;

int btnPin = 2;
LedPad ledpad = LedPad(2000);

void setup()
{
  Serial.begin (9600);
  while (!Serial);
  SD.begin(10);
  pinMode(btnPin, INPUT);

  ledpad.Start();
  Serial.println("Setup complete");
}

bool btnState = false;
File fileWrite;
bool isOn = false;
void loop()
{
  int mode = 0;
  int x = 0;
  int y = 0;
  if (Serial.available() == 4)
  {
    x = (Serial.read() - '0') * 10 + (Serial.read() - '0');
    y = (Serial.read() - '0') * 10 + (Serial.read() - '0');
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
    if (isOn)
    {
      isOn = false;
      ledpad.Reset();
    }
    ledpad.ToggleCell(x, y);
  }
  if (digitalRead(BUTTON_PIN) == HIGH)
  {
    btnState = true;
  }
  else
  {
    if (btnState)
    {
      btnState = false;
      //on click actions
      if (isOn)
      {
        isOn = false;
        ledpad.Stop();
      }
      else
      {
        isOn = true;
        ledpad.Start();
      }
    }
  }
  if (isOn)
  {
    ledpad.Next();    
  }
}


