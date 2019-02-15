#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN1            5
#define PIN2            6
#define PIN3            7
#define NUMPIXELS      240

Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUMPIXELS, PIN3, NEO_GRBW + NEO_KHZ800);

union ArrayToInteger {
  byte byte;
  uint32_t integer;
};


uint32_t toInt(byte b) {
  ArrayToInteger converter;
  converter.byte = b;
  return converter.integer;
}

uint32_t r = 0;
uint32_t g = 0;
uint32_t b = 0;
uint32_t w = 255;

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  pixels1.begin();
  pixels2.begin();
  pixels3.begin();
  Serial.begin(115200);
  while (!Serial);

  for(int pixelNumber = 0; pixelNumber < NUMPIXELS; pixelNumber++){
    pixels1.setPixelColor(pixelNumber, r, g, b, w);
    pixels2.setPixelColor(pixelNumber, r, g, b, w);
    pixels3.setPixelColor(pixelNumber, r, g, b, w);
  }
  pixels1.show();
  pixels2.show();
  pixels3.show();
}

void loop() {
  while (Serial.available() <= 0);
  byte mode[1];
  Serial.readBytes(mode, 1);

  switch (mode[0]) {
    case 0x00: {
      Serial.write(r);
      Serial.write(g);
      Serial.write(b);
      Serial.write(w);
      break;
    }

    case 0x01: {
      byte color[4];
      Serial.readBytes(color, 4);

      r = toInt(color[0]);
      g = toInt(color[1]);
      b = toInt(color[2]);
      w = toInt(color[3]);

      for(int pixelNumber = 0; pixelNumber < NUMPIXELS; pixelNumber++){
        pixels1.setPixelColor(pixelNumber, r, g, b, w);
        pixels2.setPixelColor(pixelNumber, r, g, b, w);
        pixels3.setPixelColor(pixelNumber, r, g, b, w);
      }
      pixels1.show();
      pixels2.show();
      pixels3.show();
      break;
    }

    default: {
      pixels1.setPixelColor(0, 0, 0, 0, 0);
      pixels2.setPixelColor(0, 0, 0, 0, 0);
      pixels3.setPixelColor(0, 0, 0, 0, 0);

      pixels1.setPixelColor(1, 0, 0, 0, 0);
      pixels2.setPixelColor(1, 0, 0, 0, 0);
      pixels3.setPixelColor(1, 0, 0, 0, 0);

      pixels1.show();
      pixels2.show();
      pixels3.show();

      delay(5000);
      pixels1.setPixelColor(0, 0, 0, 0, 255);
      pixels2.setPixelColor(0, 0, 0, 0, 255);
      pixels3.setPixelColor(0, 0, 0, 0, 255);
      pixels1.setPixelColor(1, 0, 0, 0, 255);
      pixels2.setPixelColor(1, 0, 0, 0, 255);
      pixels3.setPixelColor(1, 0, 0, 0, 255);

      pixels1.show();
      pixels2.show();
      pixels3.show();
    }
  }
}
