#include <Servo.h> 
#include <MsTimer2.h>
#include <DCM.h>
#include <IRRemocon.h>

int Data = 0;
IRRemocon Remocon;

int mode=0;

DCM motor1;
DCM motor2;

Servo servo1;
Servo servo2;

void setup() {
  
    Remocon.rokitSetup();
    Remocon.attachCallback(remote);
       
    motor1.attachPins(8,9);  
    motor2.attachPins(10,11);
    
    servo1.attach(16);  // attaches the servo on pin 9 to the servo object
    servo2.attach(17);  // attaches the servo on pin 9 to the servo object
    
    servo1.write(170); 
    servo2.write(10);  

}


void loop() {
  // put your main code here, to run repeatedly: 
     Remocon.update();
}

void remote()
{
   Data = Remocon.read();
   
   if(Data == KEY_U) {motor1.write(CCW,10); motor2.write(CCW, 10);}
   else if(Data == KEY_D) {motor1.write(CW, 10); motor2.write(CW,10);} 
   else if(Data == KEY_L)
   {
    if(mode == 0)
    {
       motor1.write(CCW,10); motor2.write(CW,10);
    }
    else if(mode == 1)
    {
      motor1.write(CW,10); motor2.write(CCW,10);
    }
  }
  else if(Data == KEY_R) 
  {
    if(mode == 0)
    {
        motor1.write(CW,10); motor2.write(CCW,10);
    }
    else if(mode == 1)
    {
      motor1.write(CCW,10); motor2.write(CW,10);
    }
  }
  else if(Data == KEY_5) 
  { 
     servo1.write(170);  servo2.write(10);  
     mode = 0;
  }
  else if(Data == KEY_6) 
  {
     servo1.write(90);   servo2.write(90);  
     mode = 1;
  }
   else { motor1.write(LOOSE,10); motor2.write(LOOSE,10);}
}
