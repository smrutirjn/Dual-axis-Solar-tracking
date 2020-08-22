

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
float a[12];
float E[12]={0,30,60,30,90,90,90,90,150,120,150,180};
float N[12]={90,30,90,150,0,60,120,180,30,90,150,90};
int i,pos1,pos2;
float de,dn;
int r0 = 0;      //value of select pin at the 4051 (s0)

int r1 = 0;      //value of select pin at the 4051 (s1)

int r2 = 0;      //value of select pin at the 4051 (s2)

 

int s0 = 2;

int s1 = 3;

int s2 = 4;


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(s0, OUTPUT);

  pinMode(s1, OUTPUT);

  pinMode(s2, OUTPUT);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0,0);
  float  x,y,max1,max2;
  int p1,p2,k=0;
    for (i=0;i<6;i++)
    {
      r0 = bitRead(i,0);    // use this with arduino 0013 (and newer versions)     
      r1 = bitRead(i,1);    // use this with arduino 0013 (and newer versions)     
      r2 = bitRead(i,2); 

      digitalWrite(s0, r0);
      digitalWrite(s1, r1);
      digitalWrite(s2, r2);
      a[k]=map(analogRead(A0),0,1023,0,100);
      a[k+1]=map(analogRead(A1),0,1023,0,100);
      k=k+2;
    }
    
    
    for(i=0;i<12;i++)
    {    
    
      if(a[i]==100)
      {
        lcd.setCursor(0,0);
        lcd.print(String(N[i])+"N");
        lcd.setCursor(0,1);
        lcd.print(String(E[i])+"E");
      }
      
    }
    
  for(i=0;i<12;i++)
  {
    if(a[i]!=0)
    {
      x=a[i];
      p1=i;
      break;
    }
  }
  for(i=0;i<12;i++)
  {
    if(a[i]!=0 && a[i]!=x)
    {
      y=a[i];
      p2=i;
      break;
    }
  }
  if(x>y)
  {
    max1=x;
    pos1=p1;
    max2=y;
    pos2=p2;
  }
  else if(x<y)
  {
    max1=y;
    pos1=p2;
    max2=x;
    pos2=p1;
  }
  
  if(max1 < 100 && max2 <100)
  {
    de=(E[pos1]>E[pos2])?(E[pos1]-E[pos2]):(E[pos2]-E[pos1]);
    dn=(N[pos1]>N[pos2])?(N[pos1]-N[pos2]):(N[pos2]-N[pos1]);
    latitude();
    longitude();
    
  }
  delay (1000);
  lcd.clear();
}
void longitude()
{
  String str="";
  float deg,f;
  if(E[pos1]==E[pos2])
  {
    str=String(String(E[pos1])+"E");
  }
  else if(E[pos1]>E[pos2])
  {
    if(de==60)
    {
      f=E[pos2]/60.0;
      deg=((100-a[pos1])*(float(de/100.0)))+(f*60)+30;
    }
    else
    {
      deg=((100-a[pos1])*(float(de/100.0)))+E[pos2];
    }
    str=String(String(deg)+"E");
  }
  else if(E[pos2]>E[pos1])
  {
    deg=((100-a[pos2])*(float(de/100.0)))+E[pos1];
    str=String(String(deg)+"E");
  }
  lcd.setCursor(0,1);
  lcd.print(str);
}

void latitude()
{
  String str="";
  float deg,f;
  if(N[pos1]==N[pos2])
  {
    str=String(String(N[pos1])+"N");
  }
  else if(N[pos1]>N[pos2])
  {
    if(dn==60)
    {
      f=N[pos2]/60.0;
      deg=((100-a[pos1])*(float(dn/100.0)))+(f*60)+30;
    }
    else
    {
      deg=((100-a[pos1])*(float(dn/100.0))) + N[pos2];
    }
    str=String(String(deg)+"N");
  }
  else if(N[pos2]>N[pos1])
  {
    deg=((100-a[pos2])*(float(dn/100.0)))+N[pos1];
    str=String(String(deg)+"N");
  }
  lcd.setCursor(0,0);
  lcd.print(str);
}
