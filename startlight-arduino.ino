#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      3

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

union ArrayToInteger {
  byte byte;
  uint32_t integer;
};


uint32_t toInt(byte b) {
  ArrayToInteger converter;
  converter.byte = b;
  return converter.integer;
}
void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  pixels.begin();
  Serial.begin(9600);
  while (!Serial);

  pixels.setPixelColor(0, 0, 0, 0, 255);
  pixels.setPixelColor(1, 0, 0, 0, 255);
  pixels.show();
}

uint32_t r = 0;
uint32_t g = 0;
uint32_t b = 0;
uint32_t w = 255;

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
        pixels.setPixelColor(pixelNumber, r, g, b, w);
      }
      pixels.show();
      break;
    }

    default: {
      pixels.setPixelColor(0, 0, 0, 0, 0);
      pixels.setPixelColor(1, 0, 0, 0, 0);
      pixels.show();
      delay(5000);
      pixels.setPixelColor(0, 0, 0, 0, 255);
      pixels.setPixelColor(1, 0, 0, 0, 255);
      pixels.show();
    }
  }
}
