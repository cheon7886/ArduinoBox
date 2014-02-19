#include <Herkulex.h>

void setup()  
{
  int n=1; //set the motor ID

  Herkulex.begin(115200); //open serial
  Herkulex.reboot(n); //reboot first motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  delay(200);  
  
  /*
  LED_GREEN
  LED_BLUE
  LED_CYAN
  LED_RED
  LED_GREEN2
  LED_PINK
  LED_WHITE
  */

  Herkulex.setLed(n,LED_GREEN2); //set the led to green

  Herkulex.end();
}

void loop(){
}


