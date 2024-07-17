#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Adjust this threshold based on your environment and sound sensor
const int SOUND_THRESHOLD = 50; // Example threshold

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  int soundLevel = analogRead(A0);
  float dB = map(soundLevel, 0, 1023, 0, 100);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  if (dB >= SOUND_THRESHOLD) {
    display.println("Sound Detected");
  } else {
    display.println("Sound Not Detected");
  }

  display.display();

  delay(1000);
}

