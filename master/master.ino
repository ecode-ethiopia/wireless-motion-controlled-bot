#include <SoftwareSerial.h>

#include<Wire.h>
#include<ADXL345.h>
ADXL345 adxl;
int x,y,z,Y;
int rawx,rawy,rawz;
int mappedRawX,mappedRawY,mappedRawZ;
SoftwareSerial ntn(10, 11); // RX, TX
void setup()
{ ntn.begin(38400);
Serial.begin(38400); 
 adxl.powerOn(); 
 
}

 void loop()
  {
    
  adxl.readAccel(&x,&y,&z);
  rawx=x-7;
  rawy=y-6;
  rawz=z+10;
  if(rawx<-255)rawx=-255;else if(rawx>255)rawx=255;
   if(rawy<-255)rawy=-255;else if(rawy>255)rawy=255;
   if(rawz<-255)rawz=-255;else if(rawz>255)rawz=255;
   mappedRawX=map(rawx,-255,255,0,180);
   mappedRawY=map(rawy,-255,255,0,180); 
   mappedRawZ=map(rawz,-255,255,0,180);
//Serial.print("mappedRawX =");Serial.println(mappedRawX);
//Serial.print("mappedRawY =");Serial.println(mappedRawY);
//Serial.print("mappedRawZ =");Serial.println(mappedRawZ);


 
  if(50 <= mappedRawX && mappedRawX <= 110 && 50 <= mappedRawY && mappedRawY <= 110)
  {
   ntn.write(1);
    Serial.println("STAY");
  }
    if( 0 <= mappedRawY && mappedRawY <= 50)
  {  ntn.write(2);
        Serial.println("BACKWARD");
  }
  if(110 < mappedRawY && mappedRawY <= 180)
  {
      ntn.write(3);
        Serial.println("FORWARD");
  } 
  if(0 < mappedRawX && mappedRawX < 50 )
  {
     ntn.write(4);
        Serial.println("RIGHT");
  }
 
   if(110 < mappedRawX && mappedRawX<180)
  {
      ntn.write(5);
      Serial.println("LEFT");
  }

if(ntn.available())
Y=ntn.read();
Serial.println(Y);
if(Y<20)
digitalWrite(13,LOW);
else 
digitalWrite(13,HIGH);




  }

