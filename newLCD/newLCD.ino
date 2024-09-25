#include <Wire.h>                  // Include the Wire library for I2C communication
#include <LiquidCrystal_I2C.h>     // Include the LiquidCrystal_I2C library for the LCD display

LiquidCrystal_I2C lcd(0x27, 20, 4); // Initialize the LCD object with the I2C address (0x27), 20 columns, and 4 rows

void setup() {
  lcd.init();            // Initialize the LCD
  lcd.backlight();       // Turn on the backlight
  
  lcd.clear();           // Clear any previous content displayed on the LCD

  // Print text on each line
  lcd.setCursor(5, 0);
  lcd.print("Selecione");

  lcd.setCursor(9, 1);
  lcd.print("a");

  lcd.setCursor(4, 2);
  lcd.print("dificuldade");
}

void loop() {
}