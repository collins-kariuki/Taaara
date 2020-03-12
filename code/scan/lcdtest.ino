#include <LiquidCrystal.h>

//LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);      // put your pin numbers here

void setup()
  {
  lcd.begin(16, 2);                          // put your LCD parameters here
  lcd.print("hello, world!");
  lcd.setCursor(0,1);
  lcd.print("it works!");
  }

void loop()
  {
  }