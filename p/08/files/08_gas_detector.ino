/*
  المشروع 8: كاشف الغازات والحرائق المبدئي (MQ-2)
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  التوصيل:
    MQ-2: VCC → 5V   GND → GND   AO → A0   (DO غير موصول)
    Buzzer (+) → Pin 8
    LED أحمر ← 220Ω ← Pin 12
    LED أخضر ← 220Ω ← Pin 13
*/

const int GAS_PIN    = A0;
const int BUZZER_PIN = 8;
const int RED_LED    = 12;
const int GREEN_LED  = 13;
const int MARGIN     = 150;   // الارتفاع عن قراءة الهواء النقي الذي يُعتبر خطراً

int baseline = 0;             // قراءة الهواء النقي (تُحسب عند التشغيل)

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // فترة الإحماء: نومض الأخضر لمدة 60 ثانية
  Serial.println("Warming up 60 s...");
  for (int i = 0; i < 60; i++) {
    digitalWrite(GREEN_LED, i % 2);
    delay(1000);
  }
  // معايرة: متوسط القراءات في الهواء النقي
  long sum = 0;
  for (int i = 0; i < 50; i++) { sum += analogRead(GAS_PIN); delay(20); }
  baseline = sum / 50;
  Serial.print("Baseline = "); Serial.println(baseline);
}

void loop() {
  int value = analogRead(GAS_PIN);
  Serial.print("Gas: "); Serial.println(value);

  if (value > baseline + MARGIN) {        // خطر!
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    tone(BUZZER_PIN, 2000);
    delay(150);
    digitalWrite(RED_LED, LOW);
    noTone(BUZZER_PIN);
    delay(100);
  } else {                                 // الجو آمن
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    noTone(BUZZER_PIN);
    delay(300);
  }
}
