#include <Servo.h> 
#include <IRRemocon.h>

#define  LedPin_01  8
#define  LedPin_02  9
#define  LedPin_03  10

int Data = 0;
IRRemocon Remocon;

Servo servo1;
Servo servo2;
Servo servo3;

int red = 0;
int blue = 0;
int green = 0;


void setup() {
  
    Remocon.rokitSetup();
    Remocon.attachCallback(remote);
    
    pinMode(LedPin_01, OUTPUT); 
    pinMode(LedPin_02, OUTPUT); 
    pinMode(LedPin_03, OUTPUT); 

    servo1.attach(16);  // attaches the servo on pin 16 to the servo object
    servo2.attach(17);  // attaches the servo on pin 17 to the servo object
    servo3.attach(18);  // attaches the servo on pin 18 to the servo object
}

void loop() {
  
    Remocon.update();

    if(green < 900) 
    {digitalWrite(LedPin_03, HIGH);}
    
    else if(blue < 700) 
    {digitalWrite(LedPin_02, HIGH);}
    
    else if(red < 700) 
    {digitalWrite(LedPin_01, HIGH);}
    
    else
   {digitalWrite(LedPin_01, LOW);
    digitalWrite(LedPin_02, LOW);
    digitalWrite(LedPin_03, LOW);}

}  


void remote()
{
  
    Data = Remocon.read();

    red = analogRead(A0);     
    blue = analogRead(A1);     
    green = analogRead(A2);   

     if(Data == KEY_U)
     { 
       servo1.write(180); 
       servo2.write(170); 
       servo3.write(90); 

       delay(2000);

       servo1.write(180); 
       servo2.write(30); 
       servo3.write(170); 

       delay(1500);
       Remocon._IRData = 0;
     }
     

       

}
