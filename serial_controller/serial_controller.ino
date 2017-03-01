#include <Servo.h>

Servo left, right, middle, claw; // create servo object to control a servo
int moveDelay = 10;
void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  left.attach(10);  // attaches the servo on pin 9 to the servo object
  right.attach(9);
  middle.attach(11);
  claw.attach(6);

  //Set Default Aagle
  reset_to_home_position();
}


void loop() {

}

void serialEvent() {
  String text = Serial.readString();  // for incoming serial data
  // say what you got:
  //Serial.print("received = ");
  //Serial.println(text);

  char cmd = text[0];
  text.remove(0, 1);

  int angle = text.toInt();

  switch (cmd) {
    //Middle Motor
    case 'm': {
        moveServo("Middle", middle, 0, 180, angle);
        break;
      }
    //Left Motor
    case 'l': {
        moveServo("Left", left, 30, 105, angle);
        break;
      }
    //Right Motor
    case 'r': {
        moveServo("Right", right, 0, 180, angle);
        break;
      }
    //Claw Motor
    case 'g' : {
        moveServo("Claw", claw, 0, 90, angle);
        break;
      }
    //Open Claw
    case 'o': {
        moveServo("Claw", claw, 0, 90, 0);
        break;
      }
    //Close Claw
    case 'c': {
        moveServo("Claw", claw, 0, 90, 85);
        break;
      }
    case 'h': {
        reset_to_home_position();
        break;
      }
    case 'd': {
        if (angle >= 0 and angle <= 3000) {
          moveDelay = angle;
          returnMessage("New Movement Delay for smooth motion is = " + String(moveDelay) + " milli-seconds");
        } else {
          returnMessage("Invalid value for Movement Delay; it should be in range 0 - 3000 ms, received = " + String(moveDelay));
        }
        break;
      }
    default: {
        returnMessage("Invaid Command, should be one of m,l,r,c, received = " + String(cmd));
        break;
      }
  }
}

void returnMessage(String err_msg) {
  Serial.println(err_msg);
}

void reset_to_home_position() {
  moveServo("Right", right, 0, 180, 85);
  moveServo("Left", left, 30, 105, 45);
  moveServo("Claw", claw, 0, 90, 80);
  moveServo("Middle", middle, 0, 180, 105);
  Serial.println("Arm is in home position.");
}

void moveServo(String motorPos, Servo motor, int minDeg, int maxDeg, int angle) {
  if (angle <= maxDeg and angle >= minDeg) {
    Serial.println("Moving " + motorPos + " Servo to " + String(angle) + " degrees.");
    int curPos = motor.read();
    if (curPos > angle) {
      //Gradually decrease angle
      while (curPos > angle) {
        curPos--;
        motor.write(curPos);
        delay(moveDelay);
      }
    } else {
      //Gradually increase angle
      while (curPos < angle) {
        curPos++;
        motor.write(curPos);
        delay(moveDelay);
      }
    }
  } else {
    returnMessage("Invalid angle for " + motorPos + "Motor, it should be in range " + String(minDeg) + " to " + String(maxDeg) + ", received = " + String(angle));
  }
}

