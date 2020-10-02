#include <PinChangeInterrupt.h>

const int TPIN = 11;
const int EPIN = 12;

unsigned long echo_duration = 0;

void echoISR() {
  static unsigned long echo_begin = 0;
  static unsigned long echo_end = 0;

  unsigned int echo_pin_state = digitalRead(EPIN);
  if (echo_pin_state == HIGH) {
    echo_begin = micros();
  } else {
    echo_end = micros();
    echo_duration = echo_end - echo_begin;
  }
}

void setup() {
  pinMode(TPIN, OUTPUT);
  pinMode(EPIN, INPUT);
  Serial.begin(115200);
  attachPCINT(digitalPinToPCINT(EPIN), echoISR, CHANGE);
}

void loop() {
  if (echo_duration == 0) {
    digitalWrite(TPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TPIN, LOW);
  } else {
    long distance = echo_duration / 58;
    Serial.print(distance);
    Serial.println(" cm");
    echo_duration = 0;
  }
}
