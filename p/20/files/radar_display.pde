// شاشة الرادار — برنامج Processing (processing.org)
// كتاب: 38 مشروع في شهر — لؤي النصري (@robotlouay)
// غيّر "COM3" إلى منفذ الأردوينو عندك (في لينكس/ماك مثل "/dev/ttyUSB0")

import processing.serial.*;

Serial port;
String buffer = "";
int angle = 0, distance = 0;
int maxCm = 40;                 // أقصى مسافة تُعرض على الشاشة

void setup() {
  size(1200, 700);
  smooth();
  port = new Serial(this, "COM3", 9600);
  port.bufferUntil('.');
}

void draw() {
  // أثر خافت للخط السابق
  noStroke();
  fill(0, 8);
  rect(0, 0, width, height - 60);
  fill(0);
  rect(0, height - 60, width, 60);

  translate(width / 2, height - 80);
  drawArcs();
  drawLine();
  drawObject();
  resetMatrix();
  drawText();
}

void serialEvent(Serial p) {
  String data = p.readStringUntil('.');
  if (data == null) return;
  data = trim(data.substring(0, data.length() - 1));
  int comma = data.indexOf(',');
  if (comma < 0) return;
  angle = int(data.substring(0, comma));
  distance = int(data.substring(comma + 1));
}

void drawArcs() {
  noFill();
  strokeWeight(2);
  stroke(98, 245, 31);
  float r = width * 0.9;
  for (int i = 1; i <= 4; i++) arc(0, 0, r * i / 4, r * i / 4, PI, TWO_PI);
  for (int a = 30; a <= 150; a += 30) line(0, 0, -r / 2 * cos(radians(a)), -r / 2 * sin(radians(a)));
}

void drawLine() {
  strokeWeight(6);
  stroke(30, 250, 60);
  float r = width * 0.45;
  line(0, 0, r * cos(radians(angle)), -r * sin(radians(angle)));
}

void drawObject() {
  if (distance <= 0 || distance > maxCm) return;
  float r = width * 0.45;
  float pd = distance * r / maxCm;
  strokeWeight(8);
  stroke(255, 10, 10);
  line(pd * cos(radians(angle)), -pd * sin(radians(angle)), r * cos(radians(angle)), -r * sin(radians(angle)));
}

void drawText() {
  fill(98, 245, 31);
  textSize(24);
  String status = (distance > 0 && distance <= maxCm) ? "Object: " + distance + " cm" : "Out of range";
  text("Angle: " + angle + "°", 40, height - 20);
  text(status, width / 2 - 80, height - 20);
  text("robotlouay radar", width - 260, height - 20);
}
