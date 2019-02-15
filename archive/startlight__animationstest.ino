//***********************************FASTLED
//#include "FastLED.h"                                          // FastLED library.
//
//#if FASTLED_VERSION < 3001000
//#error "Requires FastLED 3.1 or later; check github for latest code."
//#endif
//
//// Fixed definitions cannot change on the fly.
//#define LED_DT1 5                                              // Data pin to connect to the strip.
//#define LED_DT2 6                                              // Data pin to connect to the strip.
//#define LED_DT3 7                                              // Data pin to connect to the strip.
//#define LED_CK 11                                             // Clock pin for WS2801 or APA102.
//#define COLOR_ORDER GRB                                       // It's GRB for WS2812 and BGR for APA102.
//#define LED_TYPE WS2812                                       // Using APA102, WS2812, WS2801. Don't forget to modify LEDS.addLeds to suit.
//#define NUM_LEDS 240                                           // Number of LED's.
//
//// Global variables can be changed on the fly.
//uint8_t max_bright = 255;                                      // Overall brightness definition. It can be changed on the fly.
//uint8_t thisdelay = 20;
//
//struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.
////struct CRGB FLED2[NUM_LEDS];                                   // Initialize our LED array.
////struct CRGB FLED3[NUM_LEDS];                                   // Initialize our LED array.
//
//
//#define SECONDS_PER_PALETTE 30                             // NOBLEND or LINEARBLEND
//
//extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
//  extern const uint8_t gGradientPaletteCount;
//  
//  // Current palette number from the 'playlist' of color palettes
//  uint8_t gCurrentPaletteNumber = 0;
//
//  CRGBPalette16 gCurrentPalette( CRGB::Black);
//  CRGBPalette16 gTargetPalette( gGradientPalettes[0] );

//***********************************FASTLED




#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN1            5
#define PIN2            6
#define PIN3            7
#define DATA_LEDNUM     240
#define PIXELNUM        60
#define BRIGHTNESS      255

Adafruit_NeoPixel NPLED1 = Adafruit_NeoPixel(DATA_LEDNUM, PIN1, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel NPLED2 = Adafruit_NeoPixel(DATA_LEDNUM, PIN2, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel NPLED3 = Adafruit_NeoPixel(DATA_LEDNUM, PIN3, NEO_GRBW + NEO_KHZ800);

int r = 0;
int g = 0;
int b = 0;
int w = 255;

byte mode_old=0;
byte mode[1];
bool newIncome=false;
bool command=false;
bool animate=false;

int animationDelay=100;
int animationSpeed=2;

int pixelCounter=0;
byte LEDDirection=1;
unsigned long anim_timer=0;

int rainbow_i=0;
int rainbow_j=0;
int rainbow_dir=1;

int r_dir=10;
int g_dir=10;
int b_dir=10;
int w_dir=10;

int wave_j=0;




//*******************************************Setup()

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif


  LED_begin();
  Serial.begin(115200);

  LED_staticColor_all(r,g,b,w);
  LED_update_all();

  anim_timer=millis();

  

  //*****************************************FASTLED
//  LEDS.addLeds<LED_TYPE, LED_DT1, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2812
//  LEDS.addLeds<LED_TYPE, LED_DT2, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2812
//  LEDS.addLeds<LED_TYPE, LED_DT3, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2812

  
  

  //*****************************************FASTLED

}


//************************************************** loop()
//***************************************************************

void loop() {
  mode_old=mode[0];
  newIncome=false;  
  if (Serial.available()) {
    newIncome=true;
    Serial.readBytes(mode, 1);
  }
  
  switch (mode[0]) {   
    
    case 0x00: {
      if (newIncome) {
        newIncome=SerialWrite_actualState();
      }
      mode[0]=mode_old;
      break;
    }    
    
    case 0x01: {
      if (newIncome) {
        newIncome=SerialRead_Color();         //returns false if the colors are read out
        LEDDirection=LED_change_direction();       // direction of change animation
        animate=animationCheck();        
        command=true;                 //current command is active
        pixelCounter=0;               //reset the Counter for the animation 
      }

      if ((command)&&(animate)) {
        command=LED_AnimationChange(animationSpeed);    //returns false, when the animation is completed
        }
      else if ((command)&&(!animate)) {
        command=LED_StaticChange(r,g,b,w);                        //returns false, when the animation is completed
        }
      break;
    }

    case 0x02: {
      if (newIncome) {
        r=0;
        g=255;
        b=255;
        w=0;
        newIncome=false;
      }
      startraum_wave(0,50,100,0,0,255,255,0);
      //startraum_Cycle(50);
      //FASTLED_crossfadepalette();
       //FASTLED_Palletwave();
      break;
    }

//    default: {
//      LED_staticColor_all(0,0,0,0);
//      LED_setPixelColor_MAPPED(2,1,255,0,0,0);
//      LED_update_all();
//      delay(200);
//      LED_setPixelColor_MAPPED(2,1,255,0,0,0);      
//      LED_update_all();
//      delay(200);
//    }
  }
}





















