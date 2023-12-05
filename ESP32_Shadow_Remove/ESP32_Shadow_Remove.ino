#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_VEML7700.h>

Adafruit_VEML7700 veml7700 = Adafruit_VEML7700();

#define PIN1 13 // GIPO13 D7
#define PIN2 2  // GIPO2 D9

#define PIN3 4  // GIPO4 D12
#define PIN4 12 // GIPO12 D13

#define NUM_PIXELS 8
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 0
#define BRIGHTNESS_STEP 5

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_PIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_PIXELS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM_PIXELS, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(NUM_PIXELS, PIN4, NEO_GRB + NEO_KHZ800);

float targetLux = 200.0;      // 초기 Lux 목표값 설정
const float luxTolerance = 20.0; // 목표값과의 허용 오차 범위

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }
  
  if (!veml7700.begin()) {
    Serial.println("Sensor not found");
    while (1);
  }
  Serial.println("Sensor found");

  strip1.begin();
  strip2.begin();
  strip3.begin();
  strip4.begin();

  strip1.show(); // 모든 픽셀을 "꺼진" 상태로 초기화
  strip2.show();
  strip3.show();
  strip4.show();

  strip1.setBrightness(0);
  strip2.setBrightness(0);
  strip3.setBrightness(0);
  strip4.setBrightness(0);
}

void loop() {
  float lux = veml7700.readLux();
  int Brightness = strip1.getBrightness();
  Serial.println(lux);
  Serial.print("Brightness");
  Serial.println(Brightness);

  if (lux > targetLux + luxTolerance) {
    decreaseBrightness();
  } else if (lux < targetLux - luxTolerance) {
    increaseBrightness();
  }
}

void setWhiteColor(Adafruit_NeoPixel &strip, int brightness) {
  for (int j = 0; j < NUM_PIXELS; j++) {
    strip.setPixelColor(j, strip.Color(brightness, brightness, brightness));
  }
}

void increaseBrightness() {
  int currentBrightness1 = strip1.getBrightness();
  //int currentBrightness2 = strip2.getBrightness();
  // int currentBrightness3 = strip3.getBrightness();
  // int currentBrightness4 = strip4.getBrightness();

  int newBrightness1 = min(MAX_BRIGHTNESS, currentBrightness1 + BRIGHTNESS_STEP);
  int newBrightness2 = min(MAX_BRIGHTNESS, currentBrightness1 + BRIGHTNESS_STEP);
  int newBrightness3 = min(MAX_BRIGHTNESS, currentBrightness1 + BRIGHTNESS_STEP);
  int newBrightness4 = min(MAX_BRIGHTNESS, currentBrightness1 + BRIGHTNESS_STEP);

  setWhiteColor(strip1, newBrightness1);
  setWhiteColor(strip2, newBrightness2);
  setWhiteColor(strip3, newBrightness3);
  setWhiteColor(strip4, newBrightness4);

  strip1.setBrightness(newBrightness1);
  strip2.setBrightness(newBrightness2);
  strip3.setBrightness(newBrightness3);
  strip4.setBrightness(newBrightness4);

  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
}

void decreaseBrightness() {
  int currentBrightness1 = strip1.getBrightness();
  // int currentBrightness2 = strip2.getBrightness();
  // int currentBrightness3 = strip3.getBrightness();
  // int currentBrightness4 = strip4.getBrightness();

  int newBrightness1 = max(MIN_BRIGHTNESS, currentBrightness1 - BRIGHTNESS_STEP);
  int newBrightness2 = max(MIN_BRIGHTNESS, currentBrightness1 - BRIGHTNESS_STEP);
  int newBrightness3 = max(MIN_BRIGHTNESS, currentBrightness1 - BRIGHTNESS_STEP);
  int newBrightness4 = max(MIN_BRIGHTNESS, currentBrightness1 - BRIGHTNESS_STEP);

  setWhiteColor(strip1, newBrightness1);
  setWhiteColor(strip2, newBrightness2);
  setWhiteColor(strip3, newBrightness3);
  setWhiteColor(strip4, newBrightness4);

  strip1.setBrightness(newBrightness1);
  strip2.setBrightness(newBrightness2);
  strip3.setBrightness(newBrightness3);
  strip4.setBrightness(newBrightness4);

  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
}
