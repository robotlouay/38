/*
  المشروع 9: نظام كشف الحركة والأمن (PIR HC-SR501)
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  التوصيل:
    PIR: VCC → 5V   OUT → Pin 2   GND → GND
    Buzzer (+) → Pin 8
    LED أحمر ← 220Ω ← Pin 11
    LED أخضر ← 220Ω ← Pin 12
  ملاحظة: يحتاج الحساس حوالي 30–60 ثانية بعد التشغيل ليستقر.
*/

const int PIR_PIN    = 2;
const int BUZZER_PIN = 8;
const int RED_LED    = 11;
const int GREEN_LED  = 12;

void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  Serial.println("PIR warming up...");
  delay(30000);
  Serial.println("System armed");
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH) {     // تم رصد حركة
    Serial.println("MOTION DETECTED!");
    digitalWrite(GREEN_LED, LOW);
    for (int i = 0; i < 10; i++) {        // وضع الطوارئ: وميض + صفارة
      digitalWrite(RED_LED, HIGH);
      tone(BUZZER_PIN, 1500);
      delay(100);
      digitalWrite(RED_LED, LOW);
      tone(BUZZER_PIN, 1000);
      delay(100);
    }
    noTone(BUZZER_PIN);
  } else {                                // لا توجد حركة: وضع الأمان
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }
}
