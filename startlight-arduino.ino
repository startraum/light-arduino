#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      120

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

uint32_t r = 0;
uint32_t g = 0;
uint32_t b = 0;
uint32_t w = 255;

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  pixels.begin();
  Serial.begin(115200);
  while (!Serial);

  for(int pixelNumber = 0; pixelNumber < NUMPIXELS; pixelNumber++){
    pixels.setPixelColor(pixelNumber, r, g, b, w);
  }
  pixels.show();
}

void loop() {
  while (Serial.available() <= 0);
  byte mode = Serial.read();

  switch (mode) {
    case 0x00: {
      Serial.write(r);
      Serial.write(g);
      Serial.write(b);
      Serial.write(w);
      break;
    }

    case 0x01: {
      while (Serial.available() <= 0);

      r = toInt(Serial.read());
      g = toInt(Serial.read());
      b = toInt(Serial.read());
      w = toInt(Serial.read());
      
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
