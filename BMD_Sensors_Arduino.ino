#include <PulseSensorPlayground.h>

//Pin setups
const int tempSensor=A0;
const int pulseSensor=A1;
const int bicep_muscle=A2;
const int tricep_muscle=A3;
const int abs_muscle=A4;
const int back_muscles=A5;
const int pulseWire = 0;

//Digital Pin Setup
const int tempSensorLED=8;
const int pulseSensorLED=4;


// Temp Sensor:
int baselineTemp = 0;
float A = 5000;
float B = 1024;
float C = 500;
float D = 10;

//function to convert 10-bit analog reading from sensor to temperature in Farenhit
double analogReadingToTemp(int reading) {
  double voltage;
  double temp;
  voltage = reading * (A/B);
  temp = (voltage - C) / D;
  temp = ((9.0/5.0) * temp) + 32;
  return temp;
// end for temp 
}


//Pulse sensor:
int baselinePulse = 0;
int Threshold = 550;  
PulseSensorPlayground pulseSensorInstance;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
//end for pulse

void setup() {
  Serial.begin(9600); // 3 Sensors' serial communication rate
 

  pinMode(muscleSensor1,INPUT);  // Input 3 sensors data
  pinMode(muscleSensor2,INPUT);
  pinMode(muscleSensor3,INPUT);
  pinMode(muscleSensor4,INPUT);
  pinMode(tempSensor,INPUT);

  pulseSensorInstance.analogInput(pulseWire);
  pulseSensorInstance.setThreshold(Threshold);
  

  pinMode(4,OUTPUT);  // LED for pulse
  pinMode(8,OUTPUT); // LED for temp
}

//LOOP Starts
void loop() {

  // temp sensor:
  baselineTemp = 100;
  int A0reading;
  int times;
  double temperature;
  A0reading=analogRead(A0);

  temperature=analogReadingToTemp(A0reading);
  Serial.println("Temperature (F)"); // for temp sensor
  Serial.println(temperature);
  Serial.println(",");
  delay(1000);

  if (temperature < baselineTemp) {
    digitalWrite(8, LOW);
  }
  if (temperature >= baselineTemp) {
    digitalWrite(8, HIGH);
  }
  //end for temp
//-----------------------------------------------------------------
  // pulse sensor:
  baselinePulse = 170;
  int myBPM = pulseSensorInstance.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                         
  
  Serial.print("BPM: ");
  Serial.println(myBPM);

 
  //if (myBPM < baselinePulse) {
    //digitalWrite(4, LOW);
  //}
  //if (myBPM >= baselinePulse) {
    //digitalWrite(4, HIGH);
  //}
  //delay(1000);
  //end for pulse
  //--------------------------------------------------------------------------
  //muscle sensor
  int bicepValue = analogRead(bicep_muscle);
  int tricepValue = analogRead(tricep_muscle);
  int absValue = analogRead(abs_muscle);
  int backValue = analogRead(back_muscles);

  //Bicep Muscle Feedback
  if (bicepValue < 100) {
    Serial.print("Work harder!!");
  }
  elif (bicepValue > 500){ 
    Serial.print("Cool Down!");
  }
  else{
    Serial.print("Keep Working!");
  }

  //Tricep Muscle Feedback
  if (tricepValue < 100) {
    Serial.print("Work harder!!");
  }
  elif (tricepValue > 500){ 
    Serial.print("Cool Down!");
  }
  else{
    Serial.print("Keep Working!");
  }

  //Abs Muscles Feedback
  if (absValue < 100) {
    Serial.print("Work harder!!");
  }
  elif (absValue > 500){ 
    Serial.print("Cool Down!");
  }
  else{
    Serial.print("Keep Working!");
  }

  //Back Muscles Feedback
  if (backValue < 100) {
    Serial.print("Work harder!!");
  }
  elif (backValue > 500){ 
    Serial.print("Cool Down!");
  }
  else{
    Serial.print("Keep Working!");
  }

  // print out the value you read: (MUSCLE)
  Serial.print("Biceps: ");
  Serial.println(bicepValue);
  Serial.print("Triceps: ");
  Serial.println(tricepValue);
  Serial.print("Abs: ");
  Serial.println(absValue);
  Serial.println("Back: ");
  Serial.println(backValue);
  Serial.println(",");
  delay(1000); // delay in between reads for stability
}
