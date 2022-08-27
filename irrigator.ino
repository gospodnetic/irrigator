#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

const int dry_val = 524;
const int wet_val = 206;
int moist_val = 0;
int moist_percent = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  moist_val = analogRead(A0);
  Serial.println(moist_val);

  moist_percent = map(moist_val, dry_val, wet_val, 0 , 100);
  if (moist_percent < 0)
    moist_percent = 0;
  else if (moist_percent > 100)
    moist_percent = 100;

  // Print to serial.
  Serial.print(moist_percent);
  Serial.println("%");

  // Print to LCD.
  lcd.setCursor(0, 0);
  lcd.print("Moisture");
  lcd.setCursor(0, 1);
  lcd.print(moist_percent);
  lcd.print(" %");

  delay(250);

  lcd.clear();
}
