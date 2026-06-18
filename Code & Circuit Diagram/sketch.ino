#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIR 27
#define VIB 26
#define LED 14
#define BUZZER 25

LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long lastTrigger = 0;
const int cooldown = 3000;

void setup() {
  Serial.begin(115200);

  pinMode(PIR, INPUT_PULLUP);
  pinMode(VIB, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.print("System Ready");
  delay(1500);
  lcd.clear();
}

void loop() {

  bool motion = digitalRead(PIR) == LOW;
  bool vibration = digitalRead(VIB) == LOW;

  if ((motion || vibration) && millis() - lastTrigger > cooldown) {

    lastTrigger = millis();

    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    lcd.clear();

    if (motion && vibration) {
      lcd.print("HIGH ALERT!");
      lcd.setCursor(0,1);
      lcd.print("MOTION+VIB");
    }
    else if (motion) {
      lcd.print("MOTION DETECT");
    }
    else {
      lcd.print("VIBRATION!");
    }

    delay(800);
    digitalWrite(BUZZER, LOW);
  }

  if (!motion && !vibration) {
    digitalWrite(LED, LOW);

    lcd.setCursor(0,0);
    lcd.print("NO INTRUSION ");
    lcd.setCursor(0,1);
    lcd.print("SYSTEM SAFE  ");
  }

  delay(100);
}