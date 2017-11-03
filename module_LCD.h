#include <LiquidCrystal_I2C.h>
#include <LCD.h>

#define I2C_ADDR 0x27  // Define I2C Address for the PCF8574T

//---(Following are the PCF8574 pin assignments to LCD connections )----
// This are different than earlier/different I2C LCD displays
#define BACKLIGHT_PIN  3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define  LED_OFF  1
#define  LED_ON  0

LiquidCrystal_I2C  lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

void LCDdisplay() {
  lcd.home();
  lcd.print("Light: "); lcd.print((int)root["Light"]); lcd.print(" lx     ");
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print("Level: "); lcd.print((int)root["Level"]); lcd.print("     ");
}

void setup_function_LCD(){
    // Switch on the backlight
  lcd.begin (16, 2);  // 20x4 characters
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(LED_ON);

  // Reset the display
  lcd.clear();
  delay(500);
  lcd.home();
}

void loop_function_LCD() {
  LCDdisplay();
}

