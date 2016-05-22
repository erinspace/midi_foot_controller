#include <SoftwareSerial.h>

const int switchPin1 = 1;
const int switchPin2 = 2;
const int switchPin3 = 3;
const int switchPin4 = 4;
const int switchPin5 = 5;
const int switchPin6 = 6;
const int switchPin7 = 7;
const int switchPin8 = 8;
const int switchPin9 = 9;
const int switchPin10 = 10;

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

byte note3 = 0;
int lastNote3Played = 0;
int lastSwitch3State = 0;
int currentSwitch3State = 0;

byte note4 = 0;
int lastNote4Played = 0;
int lastSwitch4State = 0;
int currentSwitch4State = 0;

byte note5 = 0;
int lastNote5Played = 0;
int lastSwitch5State = 0;
int currentSwitch5State = 0;

byte note6 = 0;
int lastNote6Played = 0;
int lastSwitch6State = 0;
int currentSwitch6State = 0;

byte note7 = 0;
int lastNote7Played = 0;
int lastSwitch7State = 0;
int currentSwitch7State = 0;

byte note8 = 0;
int lastNote8Played = 0;
int lastSwitch8State = 0;
int currentSwitch8State = 0;

byte note9 = 0;
int lastNote9Played = 0;
int lastSwitch9State = 0;
int currentSwitch9State = 0;

byte note10 = 0;
int lastNote10Played = 0;
int lastSwitch10State = 0;
int currentSwitch10State = 0;

//software serial
SoftwareSerial midiSerial(2, 3); // digital pins that we'll use for soft serial RX & TX

void setup() {
  //  set the states of the I/O pins:
  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
  pinMode(switchPin3, INPUT);
  pinMode(switchPin4, INPUT);
  pinMode(switchPin5, INPUT);
  pinMode(switchPin6, INPUT);
  pinMode(switchPin7, INPUT);
  pinMode(switchPin8, INPUT);
  pinMode(switchPin9, INPUT);
  pinMode(switchPin10, INPUT);

  pinMode(LEDpin, OUTPUT);

  //  Set MIDI baud rate:
  Serial.begin(9600);
  blink(3);

  midiSerial.begin(31250);
}

void loop() {

  AnalogValue = analogRead(0);

  note1 = 10;
  note2 = 20;
  note3 = 30;
  note4 = 40;
  note5 = 50;
  note6 = 60;
  note7 = 70;
  note8 = 80;
  note9 = 90;
  note10 = 100;

  currentSwitch1State = digitalRead(switchPin1);
  currentSwitch2State = digitalRead(switchPin2);
  currentSwitch2State = digitalRead(switchPin3);
  currentSwitch2State = digitalRead(switchPin4);
  currentSwitch2State = digitalRead(switchPin5);
  currentSwitch2State = digitalRead(switchPin6);
  currentSwitch2State = digitalRead(switchPin7);
  currentSwitch2State = digitalRead(switchPin8);
  currentSwitch2State = digitalRead(switchPin9);
  currentSwitch2State = digitalRead(switchPin10);

  setSwitch(note1, lastNote1Played, currentSwitch1State, lastSwitch1State);
  setSwitch(note2, lastNote2Played, currentSwitch2State, lastSwitch2State);
  setSwitch(note3, lastNote3Played, currentSwitch3State, lastSwitch3State);
  setSwitch(note4, lastNote4Played, currentSwitch4State, lastSwitch4State);
  setSwitch(note5, lastNote5Played, currentSwitch5State, lastSwitch5State);
  setSwitch(note6, lastNote6Played, currentSwitch6State, lastSwitch6State);
  setSwitch(note7, lastNote7Played, currentSwitch7State, lastSwitch7State);
  setSwitch(note8, lastNote8Played, currentSwitch8State, lastSwitch8State);
  setSwitch(note9, lastNote9Played, currentSwitch9State, lastSwitch9State);
  setSwitch(note10, lastNote10Played, currentSwitch10State, lastSwitch10State);
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
