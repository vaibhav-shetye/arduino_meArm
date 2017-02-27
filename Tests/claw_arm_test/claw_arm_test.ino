
#include <Servo.h>

Servo left, right, middle, claw; // create servo object to control a servo

String angle;   // for incoming serial data
int deg = 90;
int m = 90;
int smooth = 10;
int state = 1;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  left.attach(10);  // attaches the servo on pin 9 to the servo object
  right.attach(9);
  middle.attach(11);
  claw.attach(6);

  //Set Default Aagle
  left.write(95);
  right.write(85);
  middle.write(100);
  claw.write(0);
}


void loop() {
  if (state) {
    m--;
    if (m <= 0) {
      state = 1 - state;
    } else {

    }
  } else {
    m++;
    if (m >= 90) {
      state = 1 - state;
    }
  }
  //middle.write(m);
  //right.write(m);
  //left.write(m);
  claw.write(m);
  Serial.println(m);
  delay(smooth);
}

void serialEvent() {
  angle = Serial.readString();
  // say what you got:
  Serial.print("I received: ");
  Serial.println(angle);
  deg = angle.toInt();
  claw.write(deg);
}
