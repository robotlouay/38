/*
  المستوى المتقدم — المشروع 1: التحكم في الروبوت عبر البلوتوث (HC-05)
  كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)

  التوصيل:
    HC-05: VCC → 5V   GND → GND
           TXD → Pin 0 (RX)
           RXD ← Pin 1 (TX) عبر مقسم جهد (1kΩ من Pin 1 ثم 2kΩ إلى GND) لأن RXD يعمل بـ 3.3V
    L298N: IN1 → 6   IN2 → 7   IN3 → 8   IN4 → 9 (كما في المشاريع السابقة)
  ⚠ افصل سلكي TXD/RXD قبل رفع الكود ثم أعد توصيلهما.
  التطبيق: أي تطبيق "Bluetooth RC Car" يرسل: F أمام، B خلف، L يسار، R يمين، S توقف.
  كلمة مرور الإقران الافتراضية: 1234 أو 0000
*/

const int IN1 = 6, IN2 = 7, IN3 = 8, IN4 = 9;
unsigned long lastCmd = 0;

void motors(int r, int l) {
  digitalWrite(IN1, r == 1);  digitalWrite(IN2, r == -1);
  digitalWrite(IN3, l == 1);  digitalWrite(IN4, l == -1);
}

void setup() {
  Serial.begin(9600);          // سرعة HC-05 الافتراضية
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  motors(0, 0);
}

void loop() {
  if (Serial.available()) {
    char c = toupper(Serial.read());
    lastCmd = millis();
    switch (c) {
      case 'F': motors(1, 1);   break;   // للأمام
      case 'B': motors(-1, -1); break;   // للخلف
      case 'L': motors(1, -1);  break;   // يسار (دوران في المكان)
      case 'R': motors(-1, 1);  break;   // يمين
      case 'S': motors(0, 0);   break;   // توقف
    }
  }
  // أمان: توقف إذا انقطع الاتصال لأكثر من ثانية
  if (millis() - lastCmd > 1000) motors(0, 0);
}
