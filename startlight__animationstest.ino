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
unsigned long animation_timer=0;

int rainbow_i=0;
int rainbow_j=0;
int rainbow_dir=1;

int color_dir=5;
int r_dir=5;
int g_dir=5;
int b_dir=5;
int w_dir=5;

int animationState=0;
int animationRange[8];


int wave_j=0;
int wave_r[DATA_LEDNUM];
int wave_g[DATA_LEDNUM];
int wave_b[DATA_LEDNUM];
int wave_w[DATA_LEDNUM];




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
        newIncome=false;
        animation_timer=millis();
        animationState=0;
      }

      switch (animationState) {
        case 0: {
          newColor(0,120,60,0,0,255,150,0);
          startraum_wave_start();
          animationChange();
          animationState+=1;
          break;
        }
        case 1: {
          startraum_wave();
          if (millis()-animation_timer>20000) {
            animationState+=1;
            animation_timer=millis();
          }
          break;
        }
        case 2: {
          newColor(150,0,0,0,255,0,110,0);
          startraum_wave_start();
          animationChange();
          animationState+=1;
          break;
        }
        case 3: {
          startraum_wave();
          if (millis()-animation_timer>20000) {
            animationState=0;
            animation_timer=millis();
          }
          break;
        }
      }
      
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





















