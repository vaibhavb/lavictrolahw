/******************************************************************************
The Victrola is triggered by two sensors:

1. Reed Switch (https://www.sparkfun.com/products/8642)
The reed switch is a two-terminal, magnetically-actuated, normally-open switch.
Connect one end of the switch to ground, and the other to Arduino's D2 pin.
The D2 pin's internal pull-up resistor is used to bias the pin high. When the
switch closes, the pin should go low.

2. Title Sensor (https://www.sparkfun.com/products/10289)


Development environment specifics:
Arduino 1.8,4
******************************************************************************/

const int REED_PIN = 2; // Pin connected to reed switch
const int TILT_PIN = 3; // Pin connected to tilt sensor
const int SOUND_PIN = 13; // LED pin - active-high

int tiltState;            // the current reading from the input pin
int lastTiltState = HIGH; // the previous reading from the input pin
int sensorReading;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() 
{
  Serial.begin(9600);
  // Since the other end of the reed switch is connected to ground, we need
  // to pull-up the reed switch pin internally.
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(TILT_PIN, INPUT);
  pinMode(SOUND_PIN, OUTPUT);
}

void loop() 
{
  int discOn = digitalRead(REED_PIN); // Read the state of the switch
  int needleDown = readTilt();
  if (proximity == LOW && needleDown == HIGH) // If the pin reads low, the switch is closed.
  {
    Serial.println("Switch closed");
    digitalWrite(SOUND_PIN, HIGH); // Turn the LED on
  }
  else
  {
    digitalWrite(SOUND_PIN, LOW); // Turn the LED off
  }
}

int readTilt()
{
  
  int tiltOutput = LOW;
  
  // read the sensor and store it in the variable sensorReading:
  sensorReading = digitalRead(TILT_PIN);    
  
  // check to see if the sensor was tilted
  // (i.e. the input went from HIGH to LOW), and you've waited 
  // long enough since the last change to ignore any noise:  

  // If the tilt changed, due to noise or tilting: 
  if (sensorReading != lastTiltState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    
    // if the button state has changed:
    if (sensorReading != tiltState){
      tiltState = sensorReading;
      
    // if the sensor reading is low
      if (sensorReading == LOW) {
        // make the status of the ledPin to go on:
        tiltOutput = HIGH;   
      }
      // otherwise if it is high
      else if (sensorReading == HIGH){
        // make the status of the ledPin to stay off:
        tiltOutput = LOW;
      }
     }
   }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastTiltState = sensorReading; 
  // delay to avoid overloading the serial port buffer:
  delay(100);
  return tiltOutput;
}

