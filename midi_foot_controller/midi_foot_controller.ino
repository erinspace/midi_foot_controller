#include <SoftwareSerial.h>

const int switchPin1 = 10;
const int switchPin2 = 9;
const int LEDpin = 13;

// Variables:
int AnalogValue = 0;

byte note1 = 0;
int lastNote1Played = 0;
int lastSwitch1State = 0;
int currentSwitch1State = 0;

byte note2 = 0;
int lastNote2Played = 0;
int lastSwitch2State = 0;
int currentSwitch2State = 0;

//software serial
SoftwareSerial midiSerial(2, 3); // digital pins that we'll use for soft serial RX & TX

void setup() {
  //  set the states of the I/O pins:
  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
  pinMode(LEDpin, OUTPUT);
  
  //  Set MIDI baud rate:
  Serial.begin(9600);
  blink(3);

  midiSerial.begin(31250);

}

void loop() {
  setSwitch(note1, lastNote1Played, currentSwitch1State, lastSwitch1State);
  setSwitch(note2, lastNote2Played, currentSwitch2State, lastSwitch2State);
}

// check and set the switch!
void setSwitch(byte switchPressed, int lastNotePlayed, int currentSwitchState, int lastSwitchState) {
  if (currentSwitchState == 1) {
    if (lastSwitchState == 0) {
      noteOn(0x90, switchPressed, 0x40);
      // save the note sent, so we can turn it off
      lastNotePlayed = switchPressed;
      digitalWrite(LEDpin, HIGH);
    }
  } else {
    if (lastSwitchState == 1) {
      noteOn(0x90, switchPressed, 0x00);
      digitalWrite(LEDpin, LOW);
    }
  }

  // save state of the switch for next time
  lastSwitchState = currentSwitchState;
  
}

void noteOn(byte cmd, byte data1, byte  data2) {
  midiSerial.write(cmd);
  midiSerial.write(data1);
  midiSerial.write(data2);
}

// Blinks an LED 3 times
void blink(int howManyTimes) {
  int i;
  for (i = 0; i < howManyTimes; i++) {
    digitalWrite(LEDpin, HIGH);
    delay(100);
    digitalWrite(LEDpin, LOW);
    delay(100);
  }
}

