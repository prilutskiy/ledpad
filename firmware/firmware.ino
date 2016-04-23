#include "LedControl.h"

const int DIN = 12;           //  выход данных с Arduino
const int CLK = 11;           //  частота синхронизации последовательной передачи данных Arduino
const int  CS = 10;           //  выбор Dot matrix module MAX7219
const int  Numbe_MAX = 4;     //  количество модулей  Dot matrix module MAX7219

int curnum = 0;
int btnPin = 7; 

LedControl my_MAX7219=LedControl(DIN,CLK,CS,Numbe_MAX);

unsigned long delaytime=100;

// представление цифр 0 до 10 для Dot matrix module MAX7219 в виде двоичных массивов

  byte dig_0[5]={B01111110, B10000001, B10000001, B10000001, B01111110};

  byte dig_1[5]={B00000001, B11111111, B01000001, B00100001, B00000000};

  byte dig_2[5]={B01110001, B10001001, B10001001, B10000101, B01000011};

  byte dig_3[5]={B01101110, B10010001, B10010001, B10000001, B01000010};

  byte dig_4[5]={B11111111, B01000100, B00100100, B00010100, B00001100};

  byte dig_5[5]={B00001110, B10010001, B10010001, B10010001, B11100010};

  byte dig_6[5]={B00001110, B10010001, B10010001, B10010001, B01111110};

  byte dig_7[5]={B11100000, B10010000, B10001000, B10000111, B10000000};

  byte dig_8[5]={B01101110, B10010001, B10010001, B10010001, B01101110};

  byte dig_9[5]={B01111110, B10001001, B10001001, B10001001, B01110000};

void setup()

{

    Serial.begin (9600);

  for (int j=0; j< Numbe_MAX;j++)

     { 

       // инициализация всех подключенных Dot matrix module MAX7219

        my_MAX7219.shutdown(j,false);   // 

        my_MAX7219.setIntensity(j,8);   //  устанавливаем интенсивность свечения от  0 до 16

        my_MAX7219.clearDisplay(j);     //  очистка дисплея от мусора

     }
    pinMode(btnPin, INPUT);
}
void loop()

{ 

  if (digitalRead(btnPin) == HIGH)
  {
   curnum++;   
  }
  if (curnum >= 1000) 
  {
    curnum = 0;
  }
  Write_Number(curnum);
/*
  for (int k=0; k<1000; k++)

  {
    Write_Number(k);
  } 
  */
//Write_Number(192);

//Write_One_Digit (5, 0);

//Write_One_Digit (4, 1);

//Write_One_Digit (3, 2);

}

void Write_Number (int num)

{  // выводит трехразрядное число на 3-х каскадный модуль Dot matrix module MAX7219

   int a_100 = num/100;

   int a_10 = (num-a_100*100)/10;

   int a_1 = num%10;

//************************************************************************

//проверяем  как разложили число на цифры

   Serial.print(num,DEC);

   Serial.print("  ");

   Serial.print(a_100,DEC);

   Serial.print(" ");

   Serial.print(a_10,DEC);

   Serial.print(" ");

   Serial.print(a_1,DEC);

   Serial.print(" ");

   Serial.print(" ");

//********************************************************************************/  

   Write_One_Digit (a_100, 0); 

   Write_One_Digit (a_10, 1); 

   Write_One_Digit (a_1, 2);

   //delay(delaytime);

};

void Write_One_Digit (int dig, int col)

{

  // выводит на  Dot matrix module MAX7219  цифру "dig"  в разряд "col"

  // col=0   -   разряд сотен

  // col=1   -   разряд десятков

  // col=2   -   разряд единиц

  switch (dig)

  {

     case 0:

          for (int t=0; t<5; t++)

             {

                my_MAX7219.setRow(col,t,dig_0[t]);

             }

           break;

    case 1:

         for (int t=0; t<5; t++)

            {

              my_MAX7219.setRow(col,t,dig_1[t]);

            }

         break;

   case 2:

       for (int t=0; t<5; t++)

         {

            my_MAX7219.setRow(col,t,dig_2[t]);

         }

       break;

    case 3:

       for (int t=0; t<5; t++)

          {

            my_MAX7219.setRow(col,t,dig_3[t]);

          }

      break;

    case 4:

       for (int t=0; t<5; t++)

           {

            my_MAX7219.setRow(col,t,dig_4[t]);

           }

       break;

    case 5:

       for (int t=0; t<5; t++)

      {

        my_MAX7219.setRow(col,t,dig_5[t]);

      }

       break;

   case 6:

         for (int t=0; t<5; t++)

      {

        my_MAX7219.setRow(col,t,dig_6[t]);

      }

       break;

   case 7:

       for (int t=0; t<5; t++)

      {

        my_MAX7219.setRow(col,t,dig_7[t]);

      }

      break;

   case 8:

       for (int t=0; t<5; t++)

         {

            my_MAX7219.setRow(col,t,dig_8[t]);

          }

       break;

    case 9:

       for (int t=0; t<5; t++)

          {

             my_MAX7219.setRow(col,t,dig_9[t]);

           }

        break;

   default:

      {

        // выполняется, если не выбрана ни одна альтернатива

      }

  }

};
