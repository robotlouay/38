/*
  المشروع 15: شاشة عرض النصوص والبيانات (LCD 16x2 I2C)
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  المكتبة: LiquidCrystal I2C (Frank de Brabander)
  التوصيل:
    VCC → 5V   GND → GND   SDA → A4   SCL → A5
  إذا لم يظهر شيء: اضبط مقاومة التباين الزرقاء خلف الشاشة،
  أو جرّب العنوان 0x3F بدلاً من 0x27.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // العنوان، عدد الأعمدة، عدد الأسطر

const char message[] = "   Welcome to robotlouay - 38 projects in a month   ";

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello Arduino!");
}

void loop() {
  static unsigned long lastScroll = 0;
  static int pos = 0;

  // السطر الثاني: نص متحرك كل 300ms
  if (millis() - lastScroll >= 300) {
    lastScroll = millis();
    char window[17];
    int len = strlen(message);
    for (int i = 0; i < 16; i++) window[i] = message[(pos + i) % len];
    window[16] = '\0';
    lcd.setCursor(0, 1);
    lcd.print(window);
    pos = (pos + 1) % len;
  }

  // عدّاد الثواني في نهاية السطر الأول
  lcd.setCursor(14, 0);
  unsigned long s = (millis() / 1000) % 100;
  if (s < 10) lcd.print('0');
  lcd.print(s);
}
