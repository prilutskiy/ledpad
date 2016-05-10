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

LedControl ledpad = LedControl(DIN, CLK, CS, ledCount);
bool field[fieldWidth][fieldHeight];
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
void redrawCells(bool _field[fieldWidth][fieldHeight])
{
  for (int y = 0; y < fieldHeight; y++)
  {
    for (int x = 0; x < fieldWidth; x++)
    {
      field[x][y] = _field[x][y];
      setCell(x, y, field[x][y]);
    }
  }
}

void initField()
{
  field[2][2] = true;
  field[3][2] = true;
  field[4][2] = true;
  field[4][3] = true;
  field[3][4] = true;
  redrawCells(field);
}
int getNeighbourCount(int x, int y)
{
  int leftX = (x - 1) < 0 ? fieldWidth - 1 : (x - 1);
  int rightX = (x + 1) > (fieldWidth - 1) ? 0 : (x + 1);
  int lowerY = (y - 1) < 0 ? (fieldHeight - 1) : (y - 1);
  int upperY = (y + 1) > (fieldHeight - 1) ? 0 : (y + 1);
  int count = (int)field[leftX][upperY] + (int)field[x][upperY] + (int)field[rightX][upperY]
              + (int)field[leftX][y] + (int)field[rightX][y]
              + (int)field[leftX][lowerY] + (int)field[x][lowerY] + (int)field[rightX][lowerY];
  return count;
}

void nextField()
{
  bool nextField[fieldWidth][fieldHeight];
  for (int y = 0; y < fieldHeight; y++)
  {
    for (int x = 0; x < fieldWidth; x++)
    {
      bool currentState = field[x][y];
      bool nextState = false;
      int neighbourCount = getNeighbourCount(x, y);
      if (currentState == true)
      {
        if (neighbourCount == 2 || neighbourCount == 3)
        {
          nextState = true;
        }
        else
        {
          nextState = false;
        }
      }
      else
      {
        if (neighbourCount == 3)
        {
          nextState = true;
        }
        else
        {
          nextState = false;
        }
      }
      nextField[x][y] = nextState;
    }
  }
  redrawCells(nextField);
}

void setup()
{
  Serial.begin (9600);
  SD.begin(10);
  initLedpad();
  pinMode(btnPin, INPUT);
  sdtest();
  initField();
}

bool btnState = false;
void loop()
{
  char inputData[1536];
  int counter = 0;
  while (Serial.available() > 0)
  {
    char data = Serial.read();
    if (data == 'g') // if 'g' then send back config file content
    {
      //TODO: open and read the file
    }
    else
    {
      inputData[counter++] = data;
    }
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

    }
    nextField();
  }
  //delay(100);
}


