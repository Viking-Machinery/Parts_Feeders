// Parts Escapement Technology Demonstration
// Viking Machinery Ltd
// Writted by: James Hussey
// November 2021
// Version 1.2
// www.vikingmachinery.co.nz

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// Define OUTPUT pin numbers & names
int step_pin = 2;  // Pin connected to Steps pin on DM542
int dir_pin = 3;   // Pin connected to Direction pin
int en_pin = 4;     // Pin connected to Enable pin

// Define INPUT pin numbers and names
int limit_1 = A1;  // Pin connected to limit switch one
int limit_2 = A2;  // Pin connected to limit switch two
int trigger_1 = A3; // Pin connected to input signal 1
int trigger_2 = A4; // Pin connected to input signal 1

// Define misc variables
int pulsetime = 100; // Integer value for pulse delay. Smaller makes stepper run faster

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() {
  // Setup code runs once when the Arduino powers on or is reset
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);
  pinMode(en_pin, OUTPUT);
  pinMode(limit_1, INPUT_PULLUP);
  pinMode(limit_2, INPUT_PULLUP);
  pinMode(trigger_1, INPUT_PULLUP);
  pinMode(trigger_2, INPUT_PULLUP);


  digitalWrite(en_pin, LOW);   // Enable Stepper Motor Driver
  digitalWrite(step_pin, LOW);
  digitalWrite(dir_pin, LOW);

stepperHome(); //Returns the stepper to the pick up position for start up. Sub routine is called at end of program.

 }

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void loop() {
  // Loop code runs over and over again indefinately

dropoff1();
dropoff2();
freeWheel();
stepperHome();

  
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void dropoff1(){                                                  // This routine moves the motor to drop off position 1 and then returns to pick up position. As long as the trigger signal is applied, this will loop.
    while (digitalRead(limit_2) && digitalRead(trigger_1)) {      // Do this until the switch is activated
      digitalWrite(dir_pin, HIGH);                                // (HIGH = anti-clockwise / LOW = clockwise)
      digitalWrite(step_pin, HIGH);
      delayMicroseconds(pulsetime);                               // Delay to slow down speed of Stepper
      digitalWrite(step_pin, LOW);
      delayMicroseconds(pulsetime);
    }
delay(200);                                                       // Pause to allow parts to fall
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void dropoff2(){                                                  // This routine moves the motor to drop off position 2 and then returns to pick up position. As long as the trigger signal is applied, this will loop.
    while (digitalRead(limit_2) && digitalRead(trigger_2)) {      // Do this until the switch is activated
      digitalWrite(dir_pin, LOW);                                 // (HIGH = anti-clockwise / LOW = clockwise)
      digitalWrite(step_pin, HIGH);
      delayMicroseconds(pulsetime);                               // Delay to slow down speed of Stepper
      digitalWrite(step_pin, LOW);
      delayMicroseconds(pulsetime);
    }
    delay(200);                                                   // Pause to allow parts to fall
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void stepperHome(){                     // This routine returns the motor to the home (pick up) position

      digitalWrite(en_pin, LOW);
                
    while (digitalRead(limit_1)) {      // Do this until the switch is activated
      digitalWrite(dir_pin, HIGH);      // (HIGH = anti-clockwise / LOW = clockwise)
      digitalWrite(step_pin, HIGH);
      delayMicroseconds(pulsetime);     // Delay to slow down speed of Stepper
      digitalWrite(step_pin, LOW);
      delayMicroseconds(pulsetime);
    }

delay(200);

    while (!digitalRead(limit_1)) {   // Do this until the switch is not activated
      digitalWrite(dir_pin, LOW);
      digitalWrite(step_pin, HIGH);
      delayMicroseconds(pulsetime);   // More delay
      digitalWrite(step_pin, LOW);
      delayMicroseconds(pulsetime);
    }

delay(100);                         // A short pause to allow time for parts to settle            
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void freeWheel(){                       // This routine disables the stepper mtoro drive, allowing for free handed movement of the escapement
                
    while (digitalRead(limit_2) && digitalRead(trigger_2)) {      // Do this while both triggers are depressed
      digitalWrite(en_pin, HIGH);      // (HIGH = disabled motors)

    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
