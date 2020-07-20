
#include <LiquidCrystal.h>
uint16_t s[5];    // select the input pin for the potentiometer      // select the pin for the LED
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.print()
}

void loop() 
{
  int i;
  float x;
  
  // read the value from the sensor:
  s[0] = analogRead(A0);
  s[1] = analogRead(A1);
  s[3] = analogRead(A2);
  s[4] = analogRead(A3);
  s[5] = analogRead(A4);

  //checking if the sun is exactly over it and map it
  for(i=0;i<5;i++)
  {
    s[i]=map(s[i],0,1023,0,99);
    if(s[i]==99)
    {x=i*45;}
    else if((s[i]>0)&&(s[i+1]>0))
    {
      x=i*45;
      x+= s[i+1]*0.45;
    }
  }
  lcd.print(x);
  
}
