// Code made with luv 💙 by Kittyawn aka. Alvian

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int dutyCycle = 0, value = 0;

void setup() {
  attachInterrupt(0, ISR_INT0, RISING);
  pinMode(2, INPUT);  // zero crossing detection pin here
  pinMode(11, INPUT_PULLUP); // button 1 pin
  pinMode(10, INPUT_PULLUP); // button 2 pin
  pinMode(5, OUTPUT); // dimmer trigger pin
  digitalWrite(5, LOW);
  
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  if(digitalRead(11) == LOW){
    if(++dutyCycle > 100) dutyCycle = 100;
    delay(150);
  }
  if(digitalRead(10) == LOW){
    if(--dutyCycle < 0) dutyCycle = 0;
    delay(150);
  }
  value = map(dutyCycle, 0, 100, 10000, 0);
  lcd.setCursor(0,0);
  lcd.print(dutyCycle);
  lcd.print("% ");
}

void ISR_INT0(){ // ISR interrupt 0
  digitalWrite(5, LOW);
  delayMicroseconds(value);
  digitalWrite(5, HIGH);
}
