///
/// Example Serial payload: `CPU: 42°C\GPU: 62°C`
/// Will render to (`\` is interpretted as newline):
///
/// CPU: 42°C
/// GPU: 62°C
///
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

bool ignoreNextFlag = false;

void loop() {
  if (Serial.available()) {
    delay(100);

    lcd.setCursor(0, 0);
    lcd.clear();

    while (Serial.available() > 0) {
      int v = Serial.read();

      // For debugging:
      // char str[20];
      // sprintf(str, "%d", v);
      // Serial.write(str);
      // Serial.write("\n");

      if (ignoreNextFlag && v == 176) {
        ignoreNextFlag = false;
      } else if (v == 194) {
        lcd.write(B11011111);
        ignoreNextFlag = true;
      } else if (v == 92) {
        lcd.setCursor(0, 1);
      } else {
        lcd.write(v);
      }
    }
  }
}