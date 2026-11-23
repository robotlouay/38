/*
  المستوى المتقدم — المشروع 4: العين الروبوتية التفاعلية (Animatronic Eye)
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  التوصيل:
    سيرفو الحركة الأفقية (يمين/يسار) → Pin 9
    سيرفو الحركة العمودية (أعلى/أسفل) → Pin 10
    سيرفو الجفون → Pin 11
    تغذية السيرفوهات: مصدر خارجي 5V (2A) + توحيد GND مع الأردوينو
  عدّل حدود الزوايا بعد المعايرة حتى لا تنحشر الآلية.
*/

#include <Servo.h>

Servo eyeX, eyeY, lids;

// حدود آمنة لكل محرك (بعد المعايرة)
const int X_MIN = 60,  X_MAX = 120;
const int Y_MIN = 70,  Y_MAX = 110;
const int LID_OPEN = 40, LID_CLOSED = 100;

int curX = 90, curY = 90;

void moveSmooth(int tx, int ty, int stepDelay) {   // حركة ناعمة بدلاً من القفز
  tx = constrain(tx, X_MIN, X_MAX);
  ty = constrain(ty, Y_MIN, Y_MAX);
  while (curX != tx || curY != ty) {
    if (curX < tx) curX++; else if (curX > tx) curX--;
    if (curY < ty) curY++; else if (curY > ty) curY--;
    eyeX.write(curX);
    eyeY.write(curY);
    delay(stepDelay);
  }
}

void blink() {
  lids.write(LID_CLOSED);
  delay(120);
  lids.write(LID_OPEN);
}

void setup() {
  eyeX.attach(9);
  eyeY.attach(10);
  lids.attach(11);
  eyeX.write(curX);
  eyeY.write(curY);
  lids.write(LID_OPEN);
  randomSeed(analogRead(A0));
  delay(1000);
}

void loop() {
  // نظرة عشوائية مثل العين الطبيعية
  int tx = random(X_MIN, X_MAX + 1);
  int ty = random(Y_MIN, Y_MAX + 1);
  moveSmooth(tx, ty, random(3, 10));
  delay(random(400, 1500));

  if (random(0, 10) < 3) blink();              // رمشة بنسبة 30%
  if (random(0, 20) == 0) { blink(); delay(150); blink(); }  // رمشة مزدوجة أحياناً
}
