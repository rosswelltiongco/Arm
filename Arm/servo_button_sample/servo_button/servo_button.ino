#include <Servo.h>

int  incSwitch = 9;
int  right = 13;
int  servoPin = 2;

int angle = 90;
int change = 2; // this value determines how much the angle changes each time through the loop

Servo servo1;

void setup(){

 digitalWrite(incSwitch, HIGH); // set internal pull up resistors
 digitalWrite(right, HIGH);

 servo1.attach(servoPin);
}

void loop(){

 if( digitalRead(incSwitch) == LOW){    // here if increment switch pressed
   angle = angle - change;
 }
 if( digitalRead(right) == LOW){    // here if decrement switch pressed
   angle = angle + change;
 }
angle = constrain(angle, 0, 180); // limit value of angle 
 servo1.write(angle);
 delay(20); 
}
