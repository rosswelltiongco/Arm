//Servo library
#include <Servo.h>

//Make servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;

//Attaching servos to pins. Making variables instead of directly .attach(pin) makes
//it easier to change just one number and makes it easier to understand code
int servo1Pin = 2;
int servo2Pin = 3;
int servo3Pin = 4;
int servo4Pin = 5;
int servo5Pin = 6;
int servo6Pin = 10;
int servo7Pin = 12;


//Potentiometer analog pin assignment. Don't need to have 'A' for 'analog' in front. Just makes for easier identification.
int joystick1XPin = A0;
int joystick1YPin = A1;
int joystick2XPin = A2;
int joystick2YPin = A3;
int incSwitch = 9;
int right = 13;
int clawCounter = 0; //time keeping for the claw


//Servo's halfway/at rest position/button state
int servo1Position = 120;
int servo2Position = 50;
int servo3Position = 50;
int servo4Position = 90;
int servo5Position = 90;
int servo7Position = 90;
int buttonPosition = 90;
int angle = 90;
int claw = 165;

//Joystick default speed
int joystick1Acceleration = 0;
int joystick2Acceleration = 0;
int joystick3Acceleration = 0;
int joystick4Acceleration = 0;
int change = 3; // this value determines how much the angle changes each time through the loop
void setup()
{
  digitalWrite(incSwitch, HIGH); // set internal pull up resistors
  digitalWrite(right, HIGH);
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  servo5.attach(servo5Pin);
  servo6.attach(servo6Pin);
  servo7.attach(servo7Pin);
}


void loop()
{
  //joystick acceleration breaks joystick's range of motion into 50 equally small parts.
  // -512 to provide equal +/- numbers
  // +/- 50 to swap directions
  // -50. Synchronizes joystick to servos. Rotating joystick clockrise makes servos rotate clockwise
  // +50 Reverse joystick and servos controls
  // Why -512?
  joystick1Acceleration = (analogRead(joystick1YPin) - 512) / +75;
  joystick2Acceleration = (analogRead(joystick1XPin) - 512) / -75; // pos 50 to direct w/ second servo
  joystick3Acceleration = (analogRead(joystick2XPin) - 512) / -75; //multiply 50 *1.50 to get 75
  joystick4Acceleration = (analogRead(joystick2YPin) - 512) / -75;


  if ( digitalRead(incSwitch) == LOW) {  // here if increment switch pressed
    angle = angle - change;
  }
  if ( digitalRead(right) == LOW) {  // here if decrement switch pressed
    angle = angle + change;
  }

  CLAW();

  angle = constrain(angle, 0, 180); // limit value of angle
  servo2Position = constrain((servo2Position + .5 * joystick2Acceleration), 1, 180); //Halved acceleration to slow down by by mult .5. More incrementatinos
  servo3Position = constrain((servo3Position + .5 * joystick2Acceleration), 1, 180);
  servo4Position = constrain((servo4Position + .5 * joystick3Acceleration), 1, 180);
  servo5Position = constrain((servo5Position + .5 * joystick1Acceleration), 1, 180);
  claw = constrain(claw, 60, 165);
  servo7Position = constrain((servo7Position + .5 * joystick4Acceleration), 1, 180);

  //Making servo move to the auto-updating position, servoXPosition
  servo1.write(angle);
  servo2.write(servo2Position);
  servo3.write(servo3Position);
  servo4.write(servo4Position);
  servo5.write(servo5Position);
  servo6.write(claw);
  servo7.write(servo7Position);

  //controls speed. Found 50 to be sweetspot for speed and smoothness
  delay(25); // 50 * .5 to get 25 for balance b/w speed and smoothne

}

//  //First/failed method based on speeding up claw after reaching certain position
//void CLAW(){ //decision process for the claw
//  if ((digitalRead(incSwitch) == LOW) and (digitalRead(right) == LOW)) {  // here if both buttons pushed
//      claw = claw - 1.5 * change; //open at normal speed.
//    }
//  else { //here when nothing pushed (normal state)
//      if (100 < claw){
//      claw = claw + 1.5*change; //tighten at full speed
//      }
//      else{
//        claw++ ;  //tighten slowly until 100 degrees is hit.
//        delay(100); //Slows down entire robot while < 100 for precision
//      }
//    }
//}

void CLAW() { //decision process for the claw //remember tat this is in a contin  uous loop!! So putting counter at the start doesn't help, has to be initialized from the very beginnin
  //int counter = 0; //initialize counter/time to be no time passed, but DOES NOT work as the fxn will always reset to 0. Therefore, claw will never close.
  if ((digitalRead(incSwitch) == LOW) and (digitalRead(right) == LOW)) {  // here if both buttons pushed
    claw = claw - change; //open at normal speed.
    clawCounter = 0; //reset counter to 0 when buttons are pushed
  }
  else { //when nothing pushed. Closing state.
    //int counter = 0; //will also continuously be 0, never closing claw
    clawCounter++; //add to counter when nothing pushed
    if (clawCounter > 200) { //when counter reaches 10, start closing. Exactly after 5 seconds. 25(delay) * 200 = 25
      claw = claw + change; //start moving
    }
    if (claw > 100){ //claw closes without delay  or use of counter if claw isn't opened past 100
      claw = claw + change;
    }
  }
}
