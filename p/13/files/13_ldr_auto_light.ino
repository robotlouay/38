/*
  المشروع 13: نظام الإنارة التلقائي للعتمة (LDR)
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  التوصيل (مقسم جهد):
    - طرف الـ LDR الأول ← 5V ، والطرف الآخر ← A0
    - مقاومة 10kΩ بين A0 و GND
    - LED ← 220Ω ← Pin 9 ، والطرف القصير ← GND
  الخطوة 1: افتح Serial Monitor ولاحظ القيم في الضوء وفي الظلام.
  الخطوة 2: ضع قيمة بينهما في DARK_LEVEL.
*/

const int LDR_PIN    = A0;
const int LED_PIN    = 9;
const int DARK_LEVEL = 300;   // أقل من هذه القيمة = ظلام (عدّلها حسب غرفتك)
const int MARGIN     = 30;    // هامش لتجنب الوميض عند الحد الفاصل

bool lightOn = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int light = analogRead(LDR_PIN);   // ضوء أكثر = قيمة أعلى
  Serial.print("Light: ");
  Serial.println(light);

  if (light < DARK_LEVEL - MARGIN)      lightOn = true;   // حلّ الظلام
  else if (light > DARK_LEVEL + MARGIN) lightOn = false;  // عاد الضوء

  digitalWrite(LED_PIN, lightOn ? HIGH : LOW);
  delay(200);

  // تطوير: سطوع متدرج حسب الظلام
  // analogWrite(LED_PIN, map(constrain(light, 0, 800), 0, 800, 255, 0));
}
