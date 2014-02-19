#include <Herkulex.h>

int n=1; //motor ID - verify your ID !!!!

void setup()  
{

  Herkulex.begin(115200); //open serial
  Herkulex.reboot(n); //reboot first motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  delay(200);  
  
}

void loop(){

  Herkulex.moveOneAngle(n, -100, 1000, LED_BLUE); //move motor with 300 speed  
  delay(1200);

  Herkulex.moveOneAngle(n, 100, 1000, LED_BLUE); //move motor with 300 speed  
  delay(1200);

  
}


