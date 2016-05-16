#include "const.h"
#include "LedControl.h"
#include "SPI.h"
#include "SD.h"
#include "GameOfLife.h"

class LedPad
{
  private:
    LedControl ledControl = LedControl(LED_DATA_PIN, LED_CLK_PIN, LED_CS_PIN, LED_COUNT);
    GameOfLife gameOfLife = GameOfLife();
    bool field[LED_WIDTH][LED_HEIGHT];
    int mode;
    int startupDelay;
    void setCell(int x, int y, bool value)
    {
      int ledIndex = x / 8;
      int _x = x % 8;
      ledControl.setLed(ledIndex, _x, y, value);
    }
    void SetCells(bool _field[LED_WIDTH][LED_HEIGHT])
    {
      for (int y = 0; y < LED_HEIGHT; y++)
        for (int x = 0; x < LED_WIDTH; x++)
        {
          setCell(x, y, _field[x][y]);
        }
    }
  public:
    LedPad(int startupDelay = 1000)
    {
      randomSeed(analogRead(0));
      this->mode = 0;
      this->startupDelay = startupDelay;
      for (int i = 0; i < LED_COUNT; i++)
      {
        ledControl.shutdown(i, false);  //
        ledControl.setIntensity(i, 8);  //  устанавливаем интенсивность свечения от  0 до 16
        ledControl.clearDisplay(i);     //  очистка дисплея от мусора
      }
    }
    void ToggleCell(int x, int y)
    {      
      field[x][y] = !field[x][y];
      setCell(x, y, field[x][y]);
    }
    int GetWidth()
    {
      return LED_WIDTH;
    }
    int GetHeight()
    {
      return LED_HEIGHT;
    }
    
    void Start()
    {
      gameOfLife.SetField(field);
      /*
      LoadStartScreen();
      delay(startupDelay);
      NextMode();
      */
    }
    void Stop()
    {
      for (int y = 0; y < LED_HEIGHT; y++)
        for (int x = 0; x < LED_WIDTH; x++)
          {
            field[x][y] = gameOfLife.field[x][y];
          }
    }
    void Next()
    {
      gameOfLife.GenerateNext();      
      this->SetCells(gameOfLife.field);
      
    }    
};

