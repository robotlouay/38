/*
  المستوى المتوسط — المشروع 7: البيانو الإلكتروني وتوليد النغمات
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  التوصيل:
    4 أزرار: طرف كل زر → 5V ، والطرف الآخر → Pin 2 / 3 / 4 / 5
             + مقاومة 10kΩ من كل منفذ (2..5) إلى GND (Pull-down)
    Buzzer غير نشط: (+) → Pin 8 ، (−) → GND
*/

const int BUZZER_PIN = 8;
const int keys[4]  = {2, 3, 4, 5};
const int notes[4] = {262, 294, 330, 349};   // Do  Ré  Mi  Fa  (C4 D4 E4 F4)

void setup() {
  for (int i = 0; i < 4; i++) pinMode(keys[i], INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int pressed = -1;
  for (int i = 0; i < 4; i++) {
    if (digitalRead(keys[i]) == HIGH) { pressed = i; break; }
  }
  if (pressed >= 0) tone(BUZZER_PIN, notes[pressed]);  // يعزف ما دام الزر مضغوطاً
  else              noTone(BUZZER_PIN);
  delay(10);
}
