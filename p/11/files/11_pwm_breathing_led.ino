/*
  المشروع 11: التحكم في شدة إضاءة LED (PWM) — تأثير التنفس
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  التوصيل:
    الطرف الطويل (+) للـ LED ← مقاومة 220Ω ← Pin 9 (~ يدعم PWM)
    الطرف القصير (−) ← GND
  منافذ PWM في Arduino Uno: 3، 5، 6، 9، 10، 11
*/

const int LED_PIN = 9;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // زيادة السطوع تدريجياً من 0 إلى 255
  for (int b = 0; b <= 255; b++) {
    analogWrite(LED_PIN, b);
    delay(8);
  }
  // إنقاص السطوع تدريجياً من 255 إلى 0
  for (int b = 255; b >= 0; b--) {
    analogWrite(LED_PIN, b);
    delay(8);
  }
  delay(300);
}
