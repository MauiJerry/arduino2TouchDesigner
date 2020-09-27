/* 
 * arduino/Adafruit Circuit Playground Express feed to TouchDesigner
# reads many of the ACPE inputs; outputs them in one CSV line
# decide what data to send using Serial.print();Serial.print(",")
# lastly uses Serial.println() to close off line.
# yeah, not great printing but thats Arduino for ya
#
# TouchDesigner reads with SerialDAT node, one per line
# feeds to SelectDAT, taking only first row
# feeds to ? DAT parsing CSV into table columns
# transpose table so it is one row per data type
# mergeDAT with table of data names, so first column is name
# ConvertCHOP converts table to Channels
*/
#include <Adafruit_CircuitPlayground.h>

float X, Y, Z, roll, pitch, soundValue;
bool  leftSwitch, rightSwitch, slideSwitch;
int lightValue;
float soundPressure;
float tempC, tempF;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  // set for small accelerations, good for tilt sensing +/- 1G
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G); 
  // these for other ranges
  //CircuitPlayground.setAccelRange(LIS3DH_RANGE_4_G);
  //CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
}

void loop() {
  //first we grab data from CPExpress...
  // not doing capactive touch yet
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();
  leftSwitch = CircuitPlayground.leftButton();
  rightSwitch = CircuitPlayground.rightButton();
  slideSwitch = CircuitPlayground.slideSwitch();
  lightValue = CircuitPlayground.lightSensor();
  soundPressure = CircuitPlayground.mic.soundPressureLevel(10);
  tempC = CircuitPlayground.temperature();

  // Derive Roll and Pitch from 3 axis acceleration under gavity
  // code from https://howtomechatronics.com/tutorials/arduino/how-to-track-orientation-with-arduino-and-adxl345-accelerometer/
  // which uses different accelerometer, etc.  Here is a PDF on use of ACPE's device
  // for tilt sensing - some background articles
  //   https://www.nxp.com/files-static/sensors/doc/app_note/AN3461.pdf
  //   https://www.st.com/resource/en/application_note/dm00119046-tilt-measurement-using-a-lowg-3axis-accelerometer-stmicroelectronics.pdf
  // Calculate Roll and Pitch (rotation around X-axis, rotation around Y-axis)
  roll = atan(Y / sqrt(pow(X, 2) + pow(Z, 2))) * 180 / PI;
  pitch = atan(-1 * X / sqrt(pow(Y, 2) + pow(Z, 2))) * 180 / PI;

////// Now we send data out serial as Comma Separated Values(CSV) 
// each value is two statements on one line
// first to print the value, second to print the comma
// be sure you get the order right so you know how to extract
// on the other end (TouchDesigner)

// send them all on one line, separated by commas
//  Serial.print("accel,");
  Serial.print(X); Serial.print(",");
  Serial.print(Y); Serial.print(",");
  Serial.print(Z); Serial.print(",");

  Serial.print(roll); Serial.print(",");
  Serial.print(pitch); Serial.print(",");

//  Serial.print("switch lrs:,");
//  Serial.print(leftSwitch); Serial.print(",");
//  Serial.print(rightSwitch); Serial.print(",");
//  Serial.print(slideSwitch);  Serial.print(",");
//
//  Serial.print("lightSoundDegC:,");
//  Serial.print(lightValue); Serial.print(",");
//  Serial.print(soundPressure); Serial.print(",");
//  Serial.print(tempC); Serial.print(","); 
  
  // lastly terminate the line/message
  Serial.println();
  
  // slight pause between sends
  delay(50);
}
