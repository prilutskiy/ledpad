#include "LedControl.h"
#include "SPI.h"
#include "SD.h"

const int DIN = 7;           //  выход данных с Arduino
const int CLK = 6;           //  частота синхронизации последовательной передачи данных Arduino
const int  CS = 5;           //  выбор Dot matrix module MAX7219
const int  ledCount = 4;     //  количество модулей  Dot matrix module MAX7219

const int fieldHeight = 8;
const int fieldWidth = 8 * ledCount;

int btnPin = 2;

LedControl ledpad = LedControl(DIN, CLK, CS, ledCount);
File fieldsConfig;

const char* filename = "fields.txt";
void sdtest()
{
  fieldsConfig = SD.open(filename, FILE_WRITE);

  // if the file opened okay, write to it:
  if (fieldsConfig) {
    Serial.print("Writing to file...");
    fieldsConfig.println("testing 1, 2, 3.");
    // close the file:
    fieldsConfig.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
  }

  // re-open the file for reading:
  fieldsConfig = SD.open(filename);
  if (fieldsConfig) {
    Serial.println("file content:");

    // read from the file until there's nothing else in it:
    while (fieldsConfig.available()) {
      Serial.write(fieldsConfig.read());
    }
    // close the file:
    fieldsConfig.close();
    Serial.println("removing the file");
    SD.remove(filename);
    if (SD.exists(filename))
    {
      Serial.println("file still exists");
    }
    else
    {
      Serial.println("file removed");
    }
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
  }
}


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

void initLedpad()
{
  for (int i = 0; i < ledCount; i++)
  {
    ledpad.shutdown(i, false);  //
    ledpad.setIntensity(i, 8);  //  устанавливаем интенсивность свечения от  0 до 16
    ledpad.clearDisplay(i);     //  очистка дисплея от мусора
  }
}

void setup()
{
  Serial.begin (9600);
  SD.begin(10);  
  initLedpad();
  pinMode(btnPin, INPUT);
  sdtest();
}

int x = 0;
int y = 0;
bool btnState = false;
int delayFactor = 1;
void loop()
{    
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    Serial.print(c);
  }
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


