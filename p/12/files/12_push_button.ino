/*
  المشروع 12: زر التحكم الذكي (Push Button)
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  التوصيل (مقاومة سحب للأسفل Pull-down):
    - طرف الزر الأول ← 5V
    - طرف الزر الثاني ← Pin 2  + مقاومة 10kΩ من Pin 2 إلى GND
    - LED ← 220Ω ← Pin 13 ، والطرف القصير ← GND
*/

const int BUTTON_PIN = 2;
const int LED_PIN    = 13;

void setup() {
  pinMode(BUTTON_PIN, INPUT);   // المقاومة الخارجية 10kΩ تُثبّت القراءة على LOW
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int state = digitalRead(BUTTON_PIN);
  if (state == HIGH) {          // الزر مضغوط
    digitalWrite(LED_PIN, HIGH);
  } else {                      // الزر محرر
    digitalWrite(LED_PIN, LOW);
  }
}

/*
  بديل بدون مقاومة خارجية:
    pinMode(BUTTON_PIN, INPUT_PULLUP);  وصِل الزر بين Pin 2 و GND
    عندها تنعكس القراءة: LOW = مضغوط
*/
