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
