# Arduino2TouchDesigner
 Send Accelerometer +Roll/Pitch to Serial for Touch Designer
For deeper project description see:
    https://hackaday.io/project/174967-arduino-muliple-data-to-touchdesigner

Simple project for Arduino compatible Adafruit Circuit Playground Express (ACPE) to send roll/pitch data to Touch Designer

load the arduino2TouchDesigner.ino into Ardunio IDE, connect your ACPE and load the code
If you want to see outputs, use the Tools>Serial Plotter to show graph of the accelerations, and angles.
Be sure to close the plotter when done looking.

Open arduinoControl3dView.toe with TouchDesigner.  This is a slight modification to the default project.
Check the Serial DAT is connected to the correct Port for your arduino.
It should at this point start showing data streaming in and the cube should tilt as you move the ACPE.
