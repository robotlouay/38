/*
  المشروع 3: التحكم في محرك السيرفو (Servo Motor)
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  التوصيل (SG90):
    - السلك البني/الأسود  ← GND
    - السلك الأحمر         ← 5V
    - السلك البرتقالي/الأصفر (الإشارة) ← Pin 9
*/

#include <Servo.h>

Servo myServo;               // كائن يمثل المحرك
const int SERVO_PIN = 9;
const int STEP_DELAY = 15;   // كلما زادت القيمة أصبحت الحركة أبطأ

void setup() {
  myServo.attach(SERVO_PIN); // ربط المحرك بالمنفذ 9
  myServo.write(90);         // البدء من المنتصف
  delay(1000);
}

void loop() {
  // من 0 إلى 180 درجة
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    delay(STEP_DELAY);
  }
  delay(500);
  // العودة من 180 إلى 0 درجة
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(STEP_DELAY);
  }
  delay(500);
}
