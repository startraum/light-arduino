void LED_begin() {
  NPLED1.begin();
  NPLED2.begin();
  NPLED3.begin();
}



void LED_update_all() {
  NPLED1.show();
  NPLED2.show();
  NPLED3.show();
}

void LED_update_one(byte element) {

  switch (element) {

    case 0x01: {
      NPLED1.show();
      break;
    }
    case 0x02: {
      NPLED2.show();
      break;
    }
    case 0x03: {
      NPLED3.show();
      break;
    }   
  }
}

void LED_setPixelColor_ELEMENT(byte elementNumber, int pixelNumber, byte r, byte g, byte b, byte w) {
    switch(elementNumber) {
      case 0x00: {
        NPLED1.setPixelColor(pixelNumber,r,g,b,w);
        NPLED1.setPixelColor(2*PIXELNUM-(pixelNumber+1),r,g,b,w);
        break;       
      }
      case 0x01: {
        NPLED2.setPixelColor(pixelNumber,r,g,b,w);
        NPLED2.setPixelColor(2*PIXELNUM-(pixelNumber+1),r,g,b,w);
        break;       
      }
      case 0x02: {
        NPLED3.setPixelColor(pixelNumber,r,g,b,w);
        NPLED3.setPixelColor(2*PIXELNUM-(pixelNumber+1),r,g,b,w);
        break;       
      }
      case 0x03: {
        NPLED1.setPixelColor(2*PIXELNUM+pixelNumber,r,g,b,w);
        NPLED1.setPixelColor(4*PIXELNUM-(pixelNumber+1),r,g,b,w);
        break;       
      }
      case 0x04: {
        NPLED2.setPixelColor(2*PIXELNUM+pixelNumber,r,g,b,w);
        NPLED2.setPixelColor(4*PIXELNUM-(pixelNumber+1),r,g,b,w);
        break;       
      }
      case 0x05: {
        NPLED3.setPixelColor(2*PIXELNUM+pixelNumber,r,g,b,w);
        NPLED3.setPixelColor(4*PIXELNUM-(pixelNumber+1),r,g,b,w);
        break;       
      }
    }
}


void LED_setPixelColor_MAPPED(int mode, int pixelNumber, byte r, byte g, byte b, byte w) {
    switch (mode) {
      case 1: {   //up
        if ((pixelNumber>=0)&&(pixelNumber<PIXELNUM/2)) {
          for (int i=3;i<=5; i++) {
            LED_setPixelColor_ELEMENT(i,PIXELNUM-(pixelNumber+1),r,g,b,w);
          }
        }
        else if ((pixelNumber>=PIXELNUM/2)&&(pixelNumber<PIXELNUM)) {
          for (int i=3;i<=5; i++) {
            LED_setPixelColor_ELEMENT(i,PIXELNUM-(pixelNumber+1),r,g,b,w);
          }
          for (int i=0;i<=2; i++) {
            LED_setPixelColor_ELEMENT(i,2*PIXELNUM-(pixelNumber+1+PIXELNUM/2),r,g,b,w);
          }
        }
        else if ((pixelNumber>=PIXELNUM)&&(pixelNumber<3*PIXELNUM/2)) {
          for (int i=0;i<=2; i++) {
            LED_setPixelColor_ELEMENT(i,2*PIXELNUM-(pixelNumber+1+PIXELNUM/2),r,g,b,w);
          }
        }
        break;
      }

      case 2: {   //down
        if ((pixelNumber>=0)&&(pixelNumber<PIXELNUM/2)) {
          for (int i=0;i<=2; i++) {
            LED_setPixelColor_ELEMENT(i,pixelNumber,r,g,b,w);
          }
        }
        else if ((pixelNumber>=PIXELNUM/2)&&(pixelNumber<PIXELNUM)) {
          for (int i=0;i<=2; i++) {
            LED_setPixelColor_ELEMENT(i,pixelNumber,r,g,b,w);
          }
          for (int i=3;i<=5; i++) {
            LED_setPixelColor_ELEMENT(i,pixelNumber-PIXELNUM/2,r,g,b,w);
          }
        }
        else if ((pixelNumber>=PIXELNUM)&&(pixelNumber<3*PIXELNUM/2)) {
          for (int i=3;i<=5; i++) {
            LED_setPixelColor_ELEMENT(i,pixelNumber-PIXELNUM/2,r,g,b,w);
          }
        }
        break;
      }
    

    case 3: {   //ext to int
        if ((pixelNumber>=0)&&(pixelNumber<PIXELNUM)) {
          for (int i=0;i<=2; i++) {
              LED_setPixelColor_ELEMENT(i,pixelNumber,r,g,b,w);
          }
          for (int i=3;i<=5; i++) {
              LED_setPixelColor_ELEMENT(i,PIXELNUM-(pixelNumber+1),r,g,b,w);
          }
        }
        break;
      }

      case 4: {   //int to ext
        if ((pixelNumber>=0)&&(pixelNumber<PIXELNUM)) {
          for (int i=3;i<=5; i++) {
              LED_setPixelColor_ELEMENT(i,pixelNumber,r,g,b,w);
          }
          for (int i=0;i<=2; i++) {
              LED_setPixelColor_ELEMENT(i,PIXELNUM-(pixelNumber+1),r,g,b,w);
          }
        }
        break;
      }
    }
}


void LED_staticColor_all(int r,int g,int b,int w) {
  for (int pixelNumber = 0; pixelNumber<DATA_LEDNUM; pixelNumber++) {
    NPLED1.setPixelColor(pixelNumber, r, g, b, w);
    NPLED2.setPixelColor(pixelNumber, r, g, b, w);
    NPLED3.setPixelColor(pixelNumber, r, g, b, w);
  }
}
