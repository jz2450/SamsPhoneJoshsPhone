#include <Keyboard.h>
#include "passcodes.h"

unsigned long millisTilTimeOut = 10000;
const int coinPin = 18;
const int lockPin = 11;
const int threshold = 200;
bool isLocked = true;
int coinBuff = 0;

void setup() {
  pinMode(coinPin, INPUT);
  pinMode(lockPin, OUTPUT);
  digitalWrite(lockPin, HIGH);
  Keyboard.begin();
  delay(100);
}

void loop() {
  Serial.println(analogRead(coinPin));
  // coin detected
  int coinRead = analogRead(coinPin);
  if (coinRead < threshold && coinBuff > threshold) {
    Serial.println("unlocking phone");
    Keyboard.write(KEY_RETURN);
    delay(100);
    Keyboard.write(KEY_RETURN);
    delay(100);
    Keyboard.print(PASSCODE);
    Keyboard.end();
    digitalWrite(lockPin, LOW);
    delay(millisTilTimeOut);
    Serial.println("locking phone");
    Keyboard.begin();
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('q');
    delay(100);
    Keyboard.releaseAll();
    digitalWrite(lockPin, HIGH);
  }
  coinBuff = coinRead;
  delay(50);
}