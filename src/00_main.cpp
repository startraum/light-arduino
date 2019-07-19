#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


const byte BRIGHTNESS=255;
const byte ElementNum=6;
const int ElementPixelNum=120;
const byte ElementVoxelNum=ElementPixelNum/2;
const byte PinNum=3;          //Anzahl an (unterschiedlichen) Anschlusspins
const byte LEDPins[][2]={      //Anschlusspins der Datenkabel. {Pin, Anzahl an angeschlossenen Elementen}
  {3,2},      //0
  {4,2},      //1
  {5,2},      //2
  {22,2},      //3
  {24,1},      //4
  {26,2},      //5
  {49,1},      //6
  {51,3},     //7
  {53,1},     //8
};
const byte ElementMap[][3]= {      //{Pin-Nummer, Seriennummer des Elements pro Pin (0,1,2,3,...), Zählrichtungsumkehr?}
  {0,0,0},    //0
  {0,1,0},    //1
  {1,0,0},    //2
  {1,1,0},    //3
  {2,0,0},    //4
  {2,1,0},    //5
  {2,2,0},    //6
  {3,0,0},    //7
  {3,1,0},    //8
  {4,0,0},    //9
  {4,1,0},    //10
  {5,0,0},    //11
  {5,1,0},    //12
  {6,0,0},    //13
  {7,0,0},    //14
  {7,1,0},    //15
  {7,2,0},    //16
  {8,0,0},    //17
};


  Adafruit_NeoPixel LEDstrip[9]= {
    Adafruit_NeoPixel((LEDPins[0][1]*ElementPixelNum), LEDPins[0][0], NEO_GRBW + NEO_KHZ800),
    Adafruit_NeoPixel((LEDPins[1][1]*ElementPixelNum), LEDPins[1][0], NEO_GRBW + NEO_KHZ800),
    Adafruit_NeoPixel((LEDPins[2][1]*ElementPixelNum), LEDPins[2][0], NEO_GRBW + NEO_KHZ800),
    Adafruit_NeoPixel((LEDPins[3][1]*ElementPixelNum), LEDPins[3][0], NEO_GRBW + NEO_KHZ800),
    Adafruit_NeoPixel((LEDPins[4][1]*ElementPixelNum), LEDPins[4][0], NEO_GRBW + NEO_KHZ800),
    Adafruit_NeoPixel((LEDPins[5][1]*ElementPixelNum), LEDPins[5][0], NEO_GRBW + NEO_KHZ800),
    Adafruit_NeoPixel((LEDPins[6][1]*ElementPixelNum), LEDPins[6][0], NEO_GRBW + NEO_KHZ800),
    Adafruit_NeoPixel((LEDPins[7][1]*ElementPixelNum), LEDPins[7][0], NEO_GRBW + NEO_KHZ800),
    Adafruit_NeoPixel((LEDPins[8][1]*ElementPixelNum), LEDPins[8][0], NEO_GRBW + NEO_KHZ800),
  };

byte state=0;
unsigned long timer0=0;
unsigned long timer1=0;
unsigned long timer2=0;
unsigned long timer3=0;
byte colorstate=0;


byte r = 0;
byte g = 0;
byte b = 0;
byte w = 255;

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
int wave_r[ElementPixelNum*2];
int wave_g[ElementPixelNum*2];
int wave_b[ElementPixelNum*2];
int wave_w[ElementPixelNum*2];




//*******************************************Setup()

void setup() {
  LEDStripInit();   // Initialize all pixels to 'off'
  Serial.begin(115200);

  LED_setSystemColor(r,g,b,w);
  LED_update_all();

  anim_timer=millis();

  pinMode(12,INPUT);
  digitalWrite(12,HIGH);
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
        //command=LED_AnimationChange(animationSpeed);    //returns false, when the animation is completed
        command=LED_StaticChange(r,g,b,w);
        }
      else if ((command)&&(!animate)) {
        command=LED_StaticChange(r,g,b,w);               //returns false, when the animation is completed
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
      break;
    }


//    default: {
//      LED_setSystemColor(0,0,0,0);
//      LED_setPixelColor_MAPPED(2,1,255,0,0,0);
//      LED_update_all();
//      delay(200);
//      LED_setPixelColor_MAPPED(2,1,255,0,0,0);
//      LED_update_all();
//      delay(200);
//    }
  }
}
