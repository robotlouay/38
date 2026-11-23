/*
  المشروع 10: التحكم في الإضاءة عن بُعد (IR Remote)
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  المكتبة: IRremote (الإصدار 4 أو أحدث) — Sketch > Include Library > Manage Libraries
  التوصيل (مستقبل VS1838B / KY-022):
    OUT → Pin 11   GND → GND   VCC → 5V
    LED ← 220Ω ← Pin 3

  الخطوة 1: ارفع الكود وافتح Serial Monitor، واضغط أزرار الريموت لترى أكوادها.
  الخطوة 2: ضع الأكواد في BTN_ON و BTN_OFF و BTN_TOGGLE ثم ارفع الكود من جديد.
*/

#include <IRremote.hpp>

const int IR_PIN  = 11;
const int LED_PIN = 3;

// أكواد ريموت الكيت الشائع (NEC) — غيّرها حسب ما يظهر لك في Serial Monitor
const uint16_t BTN_ON     = 0x0C;   // الزر 1
const uint16_t BTN_OFF    = 0x18;   // الزر 2
const uint16_t BTN_TOGGLE = 0x40;   // زر OK

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Press remote buttons...");
}

void loop() {
  if (IrReceiver.decode()) {
    uint16_t cmd = IrReceiver.decodedIRData.command;
    bool isRepeat = IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT;

    if (!isRepeat) {
      Serial.print("Command: 0x");
      Serial.println(cmd, HEX);

      if (cmd == BTN_ON)          digitalWrite(LED_PIN, HIGH);
      else if (cmd == BTN_OFF)    digitalWrite(LED_PIN, LOW);
      else if (cmd == BTN_TOGGLE) digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // زر واحد للتبديل
    }
    IrReceiver.resume();   // الاستعداد للإشارة التالية
  }
}
