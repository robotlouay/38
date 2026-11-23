/*
  المستوى المتقدم — المشروع 6: الذراع الروبوتية خماسية المحاور مع تسجيل الحركة
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  التوصيل:
    إشارات السيرفوهات: القاعدة → 3 ، الكتف → 5 ، المرفق → 6 ، الرسغ → 9 ، القابض → 10
    المقاومات المتغيرة (10kΩ): الطرفان → 5V و GND ، الأوسط → A0 / A1 / A2 / A3 / A4
    زر التسجيل → Pin 11 و GND      زر التشغيل → Pin 12 و GND   (INPUT_PULLUP)
    LED التسجيل: المدمج Pin 13
    تغذية السيرفوهات: مصدر خارجي 5V (3A على الأقل) + توحيد GND
  الاستعمال: اضغط "تسجيل" ثم حرّك المقاومات → اضغط "تشغيل" لإعادة الحركة تلقائياً.
  الحركات تُحفظ في EEPROM فتبقى بعد فصل الكهرباء.
*/

#include <Servo.h>
#include <EEPROM.h>

const int N = 5;
const int servoPins[N] = {3, 5, 6, 9, 10};
const int potPins[N]   = {A0, A1, A2, A3, A4};
const int minAngle[N]  = {0,  15, 15, 0,  10};   // حدود آمنة لكل مفصل
const int maxAngle[N]  = {180,165,165,180, 80};
const int REC_BTN = 11, PLAY_BTN = 12, LED_PIN = 13;

const int MAX_FRAMES = 180;          // 180 × 5 بايت = 900 بايت (EEPROM في Uno = 1024)
const int ADDR_COUNT = 1000;         // نحفظ عدد الإطارات هنا

Servo joints[N];
bool recording = false;
int frameCount = 0;

void readPotsAndMove(byte out[N]) {
  for (int i = 0; i < N; i++) {
    int a = map(analogRead(potPins[i]), 0, 1023, minAngle[i], maxAngle[i]);
    joints[i].write(a);
    out[i] = a;
  }
}

void playback() {
  int count = EEPROM.read(ADDR_COUNT);
  if (count == 0 || count > MAX_FRAMES) return;
  for (int f = 0; f < count; f++) {
    for (int i = 0; i < N; i++) joints[i].write(EEPROM.read(f * N + i));
    delay(100);
    if (digitalRead(REC_BTN) == LOW) return;     // زر التسجيل يوقف التشغيل
  }
}

void setup() {
  for (int i = 0; i < N; i++) joints[i].attach(servoPins[i]);
  pinMode(REC_BTN, INPUT_PULLUP);
  pinMode(PLAY_BTN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  byte angles[N];
  readPotsAndMove(angles);                       // التحكم اليدوي دائماً

  if (digitalRead(REC_BTN) == LOW) {             // بدء/إيقاف التسجيل
    delay(300);
    recording = !recording;
    if (recording) frameCount = 0;
    else EEPROM.update(ADDR_COUNT, frameCount);
    digitalWrite(LED_PIN, recording);
  }

  if (recording) {
    if (frameCount < MAX_FRAMES) {
      for (int i = 0; i < N; i++) EEPROM.update(frameCount * N + i, angles[i]);
      frameCount++;
    } else {                                     // امتلأت الذاكرة
      recording = false;
      EEPROM.update(ADDR_COUNT, frameCount);
      digitalWrite(LED_PIN, LOW);
    }
  }

  if (!recording && digitalRead(PLAY_BTN) == LOW) {
    delay(300);
    while (digitalRead(PLAY_BTN) == HIGH && digitalRead(REC_BTN) == HIGH) playback();  // تكرار حتى الضغط على زر
    delay(300);
  }
  delay(100);                                    // 10 إطارات في الثانية
}
