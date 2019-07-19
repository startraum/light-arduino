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
byte mode;
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

void LEDStripInit() {
  for (int i=0; i<PinNum; i++) {
    LEDstrip[i].begin();
    LEDstrip[i].setBrightness(BRIGHTNESS);
    LEDstrip[i].show();
  }
}

void LED_update(byte element) {
  LEDstrip[ElementMap[element][0]].show();
}

void LED_update_all() {
  for (int i=0; i<PinNum; i++) {
    LEDstrip[i].show();
  }
}

void LED_setPixelColor(byte element, byte pixel, byte r,byte g,byte b,byte w) {   //Pixel sind jede individuelle LEDs
  int pixelNumber=ElementMap[element][2]*(ElementPixelNum-1)-pixel;
  pixelNumber=ElementMap[element][1]*ElementPixelNum+abs(pixelNumber);
  LEDstrip[ElementMap[element][0]].setPixelColor(pixelNumber, r, g, b, w);
}

void LED_setVoxelColor(byte element, byte voxel, byte r, byte g, byte b, byte w) { //Voxel beinhalten jeweils eine Led mit der direkt gegenüberliegenden zusammen
  if (voxel<ElementVoxelNum) {
    LED_setPixelColor(element,voxel,r,g,b,w);
    LED_setPixelColor(element, ElementPixelNum-1-voxel,r,g,b,w);
  }
}

void LED_setElementColor(byte element, byte r, byte g, byte b, byte w) {
  for (int i=0;i<ElementPixelNum;i++) {
    LED_setPixelColor(element,i,r,g,b,w);
  }
}

void LED_setSystemColor(byte r,byte g,byte b,byte w) {
  for (int i=0; i<ElementNum; i++) {
    LED_setElementColor(i,r,g,b,w);
  }
}

//***********Animationen*****************

void LED_setPixelColor_MAPPED(int mode, int pixelNumber, byte r, byte g, byte b, byte w) {
    switch (mode) {
      case 1: {   //up
        if ((pixelNumber>=0)&&(pixelNumber<ElementVoxelNum/2)) {
          for (int i=3;i<=5; i++) {
            LED_setVoxelColor(i,ElementVoxelNum-(pixelNumber+1),r,g,b,w);
          }
        }
        else if ((pixelNumber>=ElementVoxelNum/2)&&(pixelNumber<ElementVoxelNum)) {
          for (int i=3;i<=5; i++) {
            LED_setVoxelColor(i,ElementVoxelNum-(pixelNumber+1),r,g,b,w);
          }
          for (int i=0;i<=2; i++) {
            LED_setVoxelColor(i,2*ElementVoxelNum-(pixelNumber+1+ElementVoxelNum/2),r,g,b,w);
          }
        }
        else if ((pixelNumber>=ElementVoxelNum)&&(pixelNumber<3*ElementVoxelNum/2)) {
          for (int i=0;i<=2; i++) {
            LED_setVoxelColor(i,2*ElementVoxelNum-(pixelNumber+1+ElementVoxelNum/2),r,g,b,w);
          }
        }
        break;
      }

      case 2: {   //down
        if ((pixelNumber>=0)&&(pixelNumber<ElementVoxelNum/2)) {
          for (int i=0;i<=2; i++) {
            LED_setVoxelColor(i,pixelNumber,r,g,b,w);
          }
        }
        else if ((pixelNumber>=ElementVoxelNum/2)&&(pixelNumber<ElementVoxelNum)) {
          for (int i=0;i<=2; i++) {
            LED_setVoxelColor(i,pixelNumber,r,g,b,w);
          }
          for (int i=3;i<=5; i++) {
            LED_setVoxelColor(i,pixelNumber-ElementVoxelNum/2,r,g,b,w);
          }
        }
        else if ((pixelNumber>=ElementVoxelNum)&&(pixelNumber<3*ElementVoxelNum/2)) {
          for (int i=3;i<=5; i++) {
            LED_setVoxelColor(i,pixelNumber-ElementVoxelNum/2,r,g,b,w);
          }
        }
        break;
      }


    case 3: {   //ext to int
        if ((pixelNumber>=0)&&(pixelNumber<ElementVoxelNum)) {
          for (int i=0;i<=2; i++) {
              LED_setVoxelColor(i,pixelNumber,r,g,b,w);
          }
          for (int i=3;i<=5; i++) {
              LED_setVoxelColor(i,ElementVoxelNum-(pixelNumber+1),r,g,b,w);
          }
        }
        break;
      }

      case 4: {   //int to ext
        if ((pixelNumber>=0)&&(pixelNumber<ElementVoxelNum)) {
          for (int i=3;i<=5; i++) {
              LED_setVoxelColor(i,pixelNumber,r,g,b,w);
          }
          for (int i=0;i<=2; i++) {
              LED_setVoxelColor(i,ElementVoxelNum-(pixelNumber+1),r,g,b,w);
          }
        }
        break;
      }
    }
}

byte LED_change_direction() {
  if ((r==0)&&(g==0)&&(b==0)&&(w==0)) {
    return 1;
  }
  else {
    return 2;
  }
}

bool animationCheck() {
  bool enoughtime=false;
  if (millis()-anim_timer>animationDelay) {
    enoughtime=true;
  }
  anim_timer=millis();
  if ((enoughtime)&&(animate)) {
    return true;
  }
  else {
    return false;
  }
}

bool LED_AnimationChange(int animationSpeed) {
  if (pixelCounter<3*ElementVoxelNum/2) {
    for (int i=0; i<=animationSpeed; i++) {
      LED_setPixelColor_MAPPED(LEDDirection,pixelCounter+i,r,g,b,w);
    }
    LED_update_all();
    //for (int i=0; i<=2;i++) {
    //  LED_update(2*i);
    //}
    pixelCounter=pixelCounter+animationSpeed+1;
    return true;
  }
  if (pixelCounter>=3*ElementVoxelNum/2) {
    return false;
  }
}



bool LED_StaticChange(int r,int g,int b,int w) {                       //returns false, when the animation is completed
        LED_setSystemColor(r,g,b,w);
        LED_update_all();
        return false;
}

void newColor(int r1, int g1, int b1, int w1, int r2, int g2, int b2, int w2) {
  animationRange[0]=r1;
  animationRange[1]=g1;
  animationRange[2]=b1;
  animationRange[3]=w1;
  animationRange[4]=r2;
  animationRange[5]=g2;
  animationRange[6]=b2;
  animationRange[7]=w2;
}


int nextColor(int colornumber, int c, int cmin, int cmax, int cdir) {
    c=c+cdir;
    if (c<cmin) {
      c=cmin;
    }
    if (c>cmax) {
      c=cmax;
    }
    if ((c==cmin)||(c==cmax)) {
      cdir=(-1)*cdir;
    }
    switch (colornumber) {
      case 1: {
        r_dir=cdir;
        break;
      }
      case 2: {
        g_dir=cdir;
        break;
      }
      case 3: {
        b_dir=cdir;
        break;
      }
      case 4: {
        w_dir=cdir;
        break;
      }
    }
    return c;
}

void startraum_wave_start() {
  wave_r[0]=animationRange[0];
  wave_g[0]=animationRange[1];
  wave_b[0]=animationRange[2];
  wave_w[0]=animationRange[3];
  for (int i=1;i<ElementPixelNum*2;i++) {
    wave_r[i]=nextColor(1, wave_r[i-1], animationRange[0], animationRange[4], r_dir);
    wave_g[i]=nextColor(2, wave_g[i-1], animationRange[1], animationRange[5], g_dir);
    wave_b[i]=nextColor(3, wave_b[i-1], animationRange[2], animationRange[6], b_dir);
    wave_w[i]=nextColor(4, wave_w[i-1], animationRange[3], animationRange[7], w_dir);
  }
}

void startraum_wave() {
  for (int i=0;i<ElementPixelNum*2;i++) {
    if (i<2*ElementVoxelNum) {
      for (int e=0; e<3; e++) LED_setPixelColor(e, i, wave_r[i], wave_g[i], wave_b[i], wave_w[i]);
    }
    else {
      for (int e=3; e<6; e++) LED_setPixelColor(e, (i-2*ElementVoxelNum), wave_r[i], wave_g[i], wave_b[i], wave_w[i]);
    }
    wave_r[i]=nextColor(1, wave_r[i], animationRange[0], animationRange[4], r_dir);
    wave_g[i]=nextColor(2, wave_g[i], animationRange[1], animationRange[5], g_dir);
    wave_b[i]=nextColor(3, wave_b[i], animationRange[2], animationRange[6], b_dir);
    wave_w[i]=nextColor(4, wave_w[i], animationRange[3], animationRange[7], w_dir);
  }
  LED_update_all();
  delay(10);
}


void animationChange() {
  for (int i=0; i<ElementVoxelNum;i++) {
    for (int e=0; e<3; e++) LED_setPixelColor(e, i, wave_r[i], wave_g[i], wave_b[i], wave_w[i]);
    int j= 2*ElementVoxelNum-i-1;
    for (int e=0; e<3; e++) LED_setPixelColor(e, j, wave_r[j], wave_g[j], wave_b[j], wave_w[j]);
    LED_update_all();
  }
  for (int i=0; i<ElementVoxelNum;i++) {
    int k= i+2*ElementVoxelNum;
    for (int e=3; e<6; e++) LED_setPixelColor(e, i, wave_r[k], wave_g[k], wave_b[k], wave_w[k]);
    int j= 4*ElementVoxelNum-i-1;
    for (int e=3; e<6; e++) LED_setPixelColor(e, j-2*ElementVoxelNum, wave_r[j], wave_g[j], wave_b[j], wave_w[j]);
    LED_update_all();
  }

}

void startraum_collorchange_static(int r1, int g1, int b1, int w1, int r2, int g2, int b2, int w2) {
    r=r+r_dir;
    g=g+g_dir;
    b=b+b_dir;
    w=w+w_dir;

   if (r<r1) {
      r=r1;
    }
    if (r>r2) {
      r=r2;
    }
    if ((r==r1)||(r==r2)) {
      r_dir=(-1)*r_dir;
    }
    if (g<g1) {
      g=g1;
    }
    if (g>g2) {
      g=g2;
    }
    if ((g==g1)||(g==g2)) {
      g_dir=(-1)*g_dir;
    }
    if (b<b1) {
      b=b1;
    }
    if (b>b2) {
      b=b2;
    }
    if ((b==b1)||(b==b2)) {
      b_dir=(-1)*b_dir;
    }
    if (w<w1) {
      w=w1;
    }
    if (w>w2) {
      w=w2;
    }
    if ((w==w1)||(w==w2)) {
      w_dir=(-1)*w_dir;
    }
    LED_setSystemColor(r,g,b,w);
  LED_update_all();
  delay(20);
}

bool SerialRead_Color() {
  byte color[5];
  Serial.readBytes(color, 5);
  r = color[0];
  g = color[1];
  b = color[2];
  w = color[3];
  animate=color[4];
  return false;
}

bool SerialWrite_actualState() {
  Serial.write(r);
  Serial.write(g);
  Serial.write(b);
  Serial.write(w);
  return false;
 }

byte SerialRead_Mode() {
  byte mode[1];
  Serial.readBytes(mode, 1);

  return mode[0];
}

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
  mode_old=mode;
  newIncome=false;
  if (Serial.available()) {
    newIncome=true;
    mode = SerialRead_Mode();
  }

  switch (mode) {

    case 0x00: {
      if (newIncome) {
        newIncome=SerialWrite_actualState();
      }
      mode=mode_old;
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
