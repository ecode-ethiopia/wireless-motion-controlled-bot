#include <Servo.h>

#include <SoftwareSerial.h>
SoftwareSerial bluetooth(10, 11); // RX, TX
# define Ln 7
# define Lp 4
# define El 5 
# define Rn 12 
# define Rp 8
# define Er 6 
int x,Y,u;
int w=0;
#define trig A0 
#define echo A1
Servo ntn;
 void setup()
  {     Serial.begin(38400);  
        bluetooth.+begin(38400);  
        pinMode(Lp, OUTPUT);  
        pinMode(Ln, OUTPUT);  
        pinMode(El, OUTPUT);  
        pinMode(Rp, OUTPUT);  
        pinMode(Rn, OUTPUT);
        pinMode(Er, OUTPUT);     
        analogWrite(El, 255);
        analogWrite(Er, 255); 
        pinMode(trig,OUTPUT);
        pinMode(echo,INPUT);
        ntn.attach(3);
  }

 

void loop()
      {
 if(w!=180)       
  w=w+1;    
  else
  w=0;
  ntn.write(w);     
  // Switch signalpin to output
  digitalWrite(trig, LOW); // Send low pulse
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(trig, HIGH); // Send high pulse
  delayMicroseconds(10); // Wait for 5 microseconds
  digitalWrite(trig, LOW); // Holdoff
   // Switch signalpin to input
 // Turn on pullup resistor
  // please note that pulseIn has a 1sec timeout, which may
  // not be desirable. Depending on your sensor specs, you
  // can likely bound the time like this -- marcmerlin
  // echo = pulseIn(trig, HIGH, 38000)
  u = pulseIn(echo, HIGH); //Listen for echo
  Y = (u / 58.138) * .39; //convert to CM then to inches

  Serial.println(Y);





  
  if(bluetooth.available())
            { x=bluetooth.read();
              bluetooth.flush();
            }
            else 
       MotorControl(0,0);
{ 
    if(x==1)
    {
        MotorControl(0,0);
        Serial.println("STAY");
    }
    if( x==5)
    {
        MotorControl(2,1);
        Serial.println("LEFT");
       
    }
    if(x==4)
    {
        MotorControl(1,2);
        Serial.println("RIGHT");
      
    } 
    if(x==3)
    {
        MotorControl(1,1);
        Serial.println("FORWARD");
    }
 
    if(x==2)
    {
        MotorControl(2,2);
        Serial.println("BACKWARD");
      
     }
 }









  bluetooth.write(Y);
// delay(1900);                       
 }

 
void MotorControl(int driveL, int driveR)
{
  switch(driveL) 
  {
  case 0:    digitalWrite(Ln, LOW);    digitalWrite(Lp, LOW);    break; 
  case 1:    digitalWrite(Ln, LOW);    digitalWrite(Lp, HIGH);    break;      
  case 2:    digitalWrite(Ln, HIGH);    digitalWrite(Lp, LOW);    break;   
  default: break;  
  }  
  switch(driveR)
  {
    case 0:    digitalWrite(Rn, LOW);    digitalWrite(Rp, LOW);    break;       
    case 1:    digitalWrite(Rn, LOW);    digitalWrite(Rp, HIGH);    break;       
    case 2:    digitalWrite(Rn, HIGH);    digitalWrite(Rp, LOW);    break;    
    default: break;   
    }
    }

  
