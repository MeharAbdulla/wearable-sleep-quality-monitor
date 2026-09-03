#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);
const int MIC = 34;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
  pinMode(25, OUTPUT);
}

void loop() {
  int sound = analogRead(MIC);
  int restless = constrain(map(sound, 0, 4095, 10, 90), 0, 100);
  int arousal = constrain(restless / 4, 0, 100);
  int recovery = constrain(100 - restless, 0, 100);
  int quality = constrain((recovery + (100 - arousal)) / 2, 0, 100);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("SMART Sleep");
  display.printf("Restless %d/100\n", restless);
  display.printf("Arousal  %d/100\n", arousal);
  display.println(restless > 70 ? "REM Low" : "REM OK");
  display.printf("Recovery %d/100\n", recovery);
  display.printf("QUALITY %d", quality);
  display.display();
  delay(1000);
}
