/*
  المشروع 1: التحكم بإضاءة LED (Blink)
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  التوصيل:
    - الطرف الطويل (+) للـ LED  ← مقاومة 220Ω ← Pin 13
    - الطرف القصير (−) للـ LED  ← GND
*/

const int LED_PIN = 13;      // المنفذ المتصل بالـ LED
const int WAIT_MS = 1000;    // مدة الانتظار بالملي ثانية (1000 = ثانية واحدة)

void setup() {
  pinMode(LED_PIN, OUTPUT);  // نجعل المنفذ مخرجاً
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // تشغيل الـ LED (5 فولت)
  delay(WAIT_MS);               // انتظار ثانية
  digitalWrite(LED_PIN, LOW);   // إطفاء الـ LED (0 فولت)
  delay(WAIT_MS);               // انتظار ثانية ثم التكرار
}
