/*
  المستوى المتوسط — المشروع 5: رادار كشف الأجسام (Ultrasonic Radar)
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  التوصيل:
    HC-SR04: VCC → 5V   GND → GND   Trig → Pin 10   Echo → Pin 11
    Servo:   أحمر → 5V   بني → GND   إشارة → Pin 12
  يرسل الأردوينو "الزاوية,المسافة." عبر المنفذ التسلسلي (9600).
  شاشة الرادار: شغّل الملف radar_display.pde في برنامج Processing
  (غيّر رقم المنفذ COM داخل الملف).
*/

#include <Servo.h>

const int TRIG_PIN = 10, ECHO_PIN = 11, SERVO_PIN = 12;
Servo radarServo;

int distanceCm() {
  digitalWrite(TRIG_PIN, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long t = pulseIn(ECHO_PIN, HIGH, 30000);
  return t == 0 ? 0 : t * 0.034 / 2;
}

void sendReading(int angle) {
  radarServo.write(angle);
  delay(30);                          // استقرار المحرك قبل القياس
  int d = distanceCm();
  Serial.print(angle);
  Serial.print(",");
  Serial.print(d);
  Serial.print(".");                  // الفاصلة تفصل القيم والنقطة تنهي القراءة
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  radarServo.attach(SERVO_PIN);
}

void loop() {
  for (int a = 15; a <= 165; a++) sendReading(a);
  for (int a = 165; a >= 15; a--) sendReading(a);
}
