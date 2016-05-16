#include "const.h"

class GameOfLife
{
  private:
    int getNeighbourCount(int x, int y)
    {
      int leftX = (x - 1) < 0 ? LED_WIDTH - 1 : (x - 1);
      int rightX = (x + 1) > (LED_WIDTH - 1) ? 0 : (x + 1);
      int lowerY = (y - 1) < 0 ? (LED_HEIGHT - 1) : (y - 1);
      int upperY = (y + 1) > (LED_HEIGHT - 1) ? 0 : (y + 1);
      int count = (int)field[leftX][upperY] + (int)field[x][upperY] + (int)field[rightX][upperY]
                  + (int)field[leftX][y] + (int)field[rightX][y]
                  + (int)field[leftX][lowerY] + (int)field[x][lowerY] + (int)field[rightX][lowerY];
      return count;
    }
  public:
    bool field[LED_WIDTH][LED_HEIGHT];
    GameOfLife()
    {
    }
    void SetField(bool _field[LED_WIDTH][LED_HEIGHT])
    {
      for (int i = 0; i < LED_WIDTH; i++)
        for (int j = 0; j < LED_HEIGHT; j++)
          {
            field[i][j] = _field[i][j];
          }
    }
    void GenerateNext()
    {
      bool nextField[LED_WIDTH][LED_HEIGHT];
      for (int y = 0; y < LED_HEIGHT; y++)
      {
        for (int x = 0; x < LED_WIDTH; x++)
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
      SetField(nextField);
    }
};
