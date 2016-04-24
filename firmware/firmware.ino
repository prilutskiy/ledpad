#include "LedControl.h"
#include "SPI.h"
#include "SD.h"

const int DIN = 12;           //  выход данных с Arduino
const int CLK = 11;           //  частота синхронизации последовательной передачи данных Arduino
const int  CS = 10;           //  выбор Dot matrix module MAX7219
const int  ledCount = 4;     //  количество модулей  Dot matrix module MAX7219

const int fieldHeight = 8;
const int fieldWidth = 8 * ledCount;

int btnPin = 7;

LedControl ledpad = LedControl(DIN,CLK,CS,ledCount);


void setCell(int x, int y, bool value)
{
  int ledIndex = x / 8;
  int _x = x % 8;
  ledpad.setLed(ledIndex, _x, y, value);
}

void clearLeds()
{
  for (int i = 0; i < ledCount; i++)
  {
    ledpad.clearDisplay(i);
  }
}

void setup()
{
    Serial.begin (9600);
    for (int i = 0; i < ledCount; i++)
    {
        ledpad.shutdown(i,false);   // 
        ledpad.setIntensity(i,8);   //  устанавливаем интенсивность свечения от  0 до 16
        ledpad.clearDisplay(i);     //  очистка дисплея от мусора
    }
    pinMode(btnPin, INPUT);
}

int x = 0;
int y = 0;
bool btnState = false;
int delayFactor = 1;
void loop()
{    
  if (digitalRead(btnPin) == HIGH) 
  {
    btnState = true;
  }
  else
  {
    if (btnState)
    {
      //on click actions 
      delayFactor++;
      if (delayFactor > 10)
      {
        delayFactor = 1;
      }
      //reset btn state
      btnState = false;
    }
    if (x >= fieldWidth)
    {
      x = 0;
      y++;
    }
    if (y >= fieldHeight)
    {
      y = 0;
      clearLeds();
    }
    setCell(x++, y, true);    
  }  
  delay(50*delayFactor); 
}



