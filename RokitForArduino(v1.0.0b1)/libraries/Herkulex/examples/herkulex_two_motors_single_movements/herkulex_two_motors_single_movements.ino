#include <Herkulex.h>

void setup()  
{
  
  Herkulex.begin(115200); //open serial
  // Herkulex.reboot(BROADCAST_ID); //reboot all motor
  Herkulex.reboot(1); //reboot first motor
  Herkulex.reboot(2); //reboot second motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  delay(200);  
  
  Herkulex.moveSpeedOne(1, 300, 672, 1); //move motor with 300 speed  
  Herkulex.moveSpeedOne(2, -300, 672, 1); //move motor with -300 speed
  delay(2000);

  Herkulex.moveOne(1, 200, 1500,2); //move to position 200 in 1500 milliseconds
  Herkulex.moveOne(2, 820, 500,2); //move to 820 position in 500 milliseconds
  delay(1600);
 
  Herkulex.setLed(2,LED_PINK); //set the led 
  Herkulex.setLed(1,LED_GREEN2); //set the led
  
  Herkulex.end();
}

void loop(){
}


