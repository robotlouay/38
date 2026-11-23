/*
  المشروع 6: جهاز قياس المسافات (Ultrasonic HC-SR04)
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  التوصيل:
    VCC → 5V    Trig → Pin 9    Echo → Pin 10    GND → GND
  افتح Serial Monitor على سرعة 9600 لرؤية المسافة.
*/

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

float readDistanceCm() {
  // نبضة 10 ميكروثانية على Trig
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // زمن عودة الصدى (مع مهلة 30ms ≈ 5 أمتار)
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;          // لا يوجد صدى (خارج المدى)
  return duration * 0.034 / 2;           // سرعة الصوت 0.034 سم/µs ذهاباً وإياباً
}

void loop() {
  float d = readDistanceCm();
  if (d < 0) {
    Serial.println("Out of range");
  } else {
    Serial.print("Distance: ");
    Serial.print(d, 1);
    Serial.println(" cm");
  }
  delay(300);
}
