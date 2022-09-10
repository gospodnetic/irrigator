#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

const int dry_val = 466;
const int wet_val = 212;
int moist_val = 0;
int moist_percent = 0;

// 0 - run system
// 1 - calibrate high
// 2 - calibrate low
int system_mode = 0;

bool keydown = false;
bool keyup = true;

#define RELAY 2
#define BUTTON 8

void run_irrigator()
{
  moist_val = analogRead(A0);
  
  moist_percent = map(moist_val, dry_val, wet_val, 0 , 100);
  if (moist_percent < 0)
    moist_percent = 0;
  else if (moist_percent > 100)
    moist_percent = 100;
    
  // Print to LCD.
  lcd.setCursor(0, 0);
  lcd.print("Moisture");
  lcd.setCursor(0, 1);
  lcd.print(moist_percent);
  lcd.print(" %");

  if (moist_percent < 50)
  {
    digitalWrite(RELAY, HIGH);
//    Serial.println("HIGH");
  }
  else
  {
    digitalWrite(RELAY, LOW);
    Serial.println("LOW");
  }

  delay(250);

  lcd.clear();
}

void read_button()
{
  int button = digitalRead(BUTTON);
  if (button == 0 && keyup)
  {
    keydown = true;
    keyup = false;

    system_mode = system_mode + 1 < 3
      ? system_mode + 1
      : 0;
  }
  else if (button == 1 && keydown)
  {
    keyup = true;
    keydown = false;  
  }
  Serial.println(button);
  Serial.println(system_mode);
}

void calibrate_wet()
{
  
}

void calibrate_dry()
{
  
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(RELAY, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop()
{
  read_button();
  switch (system_mode)
  {
    case 1:
      calibrate_dry();
      break;
    case 2:
      calibrate_wet();
      break;
    default:
      run_irrigator();
      break;
  }
}
