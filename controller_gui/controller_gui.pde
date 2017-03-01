import processing.serial.*;

Serial arduino;

void setup() {
  printArray(Serial.list());
  arduino = new Serial(this, Serial.list()[32], 9600);
}

void draw() {
  while (arduino.available() > 0) {
    String inBuffer = arduino.readString();   
    if (inBuffer != null) {
      println(inBuffer);
    }
  }
}

void keyPressed() {
  // Send the keystroke out:
  arduino.write(key);
  whichKey = key;
}