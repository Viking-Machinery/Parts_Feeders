/*
Driver Sketch for the MKIII Stepper Driven Vibratory Bowl Feeder
James Hussey - Viking Machinery Ltd.
21-10-2020
Origianally programmed on an Arduino Nano

Funtion:
- Connecting "RunPin" to GND sends run signal.
- Program calculates the required movements based on "Frequency", "Displacement" and "MicroStepping".
- Stepper drives forward the allocated amount and then back the same. Displacement and Frequncy are controlled as above.
- Removing "RunPin" from GND cancels operation
*/

// Set names to physical pins
const int EnablePin = 4;
const int DirectionPin = 3;
const int StepPin = 2;
const int RunPin = 12;

// Sets operating variables
const int Frequency = 65;
const int Displacement = 20; //Maximum number of rotaional steps, in breaks of 1.8 degree as per stepper motor
const int MicroStepping = 2; //Set to match microstepping on the board (i.e 1/Microstepping)

// Sets variables to their initial values
int Count = 0;
int RunCheck = HIGH;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(StepPin, OUTPUT);
  pinMode(DirectionPin, OUTPUT);
  pinMode(EnablePin, OUTPUT);
  pinMode(RunPin, INPUT_PULLUP);

  digitalWrite(StepPin, HIGH);
  digitalWrite(DirectionPin, HIGH);
  digitalWrite(EnablePin, LOW);
}

// the loop function runs over and over again forever
void loop() {

RunCheck = digitalRead(RunPin);
 
if (RunCheck == LOW){
digitalWrite(EnablePin, LOW);
}
else{
digitalWrite(EnablePin, HIGH);
}


  while (Count < Displacement/MicroStepping) {
  digitalWrite(DirectionPin, LOW);
  digitalWrite(StepPin, LOW);
  delay((2000/Displacement) / Frequency);
  digitalWrite(StepPin, HIGH);
Count++;
}
Count = 0;

  while (Count < Displacement/MicroStepping) {
  digitalWrite(DirectionPin, HIGH);
  digitalWrite(StepPin, LOW);
  delay((2000/Displacement) / Frequency);
  digitalWrite(StepPin, HIGH);
Count++;
}
Count = 0;


}
