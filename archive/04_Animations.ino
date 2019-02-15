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
  if (pixelCounter<3*PIXELNUM/2) {
    for (int i=0; i<=animationSpeed; i++) {
      LED_setPixelColor_MAPPED(LEDDirection,pixelCounter+i,r,g,b,w);
    }
    LED_update_all();
    pixelCounter=pixelCounter+animationSpeed+1;
    return true;
  }
  if (pixelCounter>=3*PIXELNUM/2) {
    return false;
  }
}



bool LED_StaticChange(int r,int g,int b,int w) {                       //returns false, when the animation is completed
        LED_staticColor_all(r,g,b,w);
        LED_update_all();
        return false;
}



//void startraum_wave_v1(int r1, int g1, int b1, int w1, int r2, int g2, int b2, int w2) {
//  r=r+r_dir;
//      g=g+g_dir;
//      b=b+b_dir;
//      w=w+w_dir;
//      
//  //    if (r<r1) {
//  //      r=r1;
//  //    }
//  //    if (r>r2) {
//  //      r=r2;
//  //    }
//      if ((r<=r1)||(r>=r2)) {
//        r_dir=(-1)*r_dir;
//      }
//  //    if (g<g1) {
//  //      g=g1;
//  //    }
//  //    if (g>g2) {
//  //      g=g2;
//  //    }
//      if ((g<=g1)||(g>=g2)) {
//        g_dir=(-1)*g_dir;
//      }
//  //    if (b<b1) {
//  //      b=b1;
//  //    }
//  //    if (b>b2) {
//  //      b=b2;
//  //    }
//      if ((b<=b1)||(b>=b2)) {
//        b_dir=(-1)*b_dir;
//      }
//  //    if (w<w1) {
//  //      w=w1;
//  //    }
//  //    if (w>w2) {
//  //      w=w2;
//  //    }
//      if ((w<=w1)||(w>=w2)) {
//        w_dir=(-1)*w_dir;
//      }
//      int l=i+wave_j;
//      if (l>=3*PIXELNUM/2) {
//        l=l-3*PIXELNUM/2;
//      }
//      LED_setPixelColor_MAPPED(1,l,r,g,b,w);
//  LED_update_all();
//  }
  

void startraum_wave(int r1, int g1, int b1, int w1, int r2, int g2, int b2, int w2) {
    r=r1;
    g=g1;
    b=b1;
    w=w1;
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
    LED_staticColor_all(r,g,b,w);
  LED_update_all();
}





void startraum_Cycle(uint8_t wait) {
  if ((rainbow_j<256)&&(rainbow_j>=128)) { // 5 cycles of all colors on wheel
    for(byte i=0; i< DATA_LEDNUM;i++) {
      NPLED1.setPixelColor(i, Wheel1(((i * 60 / DATA_LEDNUM) + rainbow_j) & 255));
      NPLED2.setPixelColor(i, Wheel1(((i * 60 / DATA_LEDNUM) + rainbow_j) & 255));
      NPLED3.setPixelColor(i, Wheel1(((i * 60 / DATA_LEDNUM) + rainbow_j) & 255));
    }
    rainbow_j=rainbow_j+rainbow_dir;
    LED_update_all();
    delay(wait);
  }
  else {
    rainbow_dir=-rainbow_dir;
    rainbow_j=255;
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel1(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return NPLED1.Color(0, 0, WheelPos * 3,0); //(255 - WheelPos * 3)
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return NPLED1.Color(0, (WheelPos * 3)&150, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return NPLED1.Color(0, 255 - WheelPos * 3, 0,0);  //(WheelPos * 3)
}

uint32_t Wheel2(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return NPLED1.Color(0, 0, WheelPos * 3,0); //(255 - WheelPos * 3)
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return NPLED1.Color(0, (WheelPos * 3)&150, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return NPLED1.Color(0, 255 - WheelPos * 3, 0,0);  //(WheelPos * 3)
}




////*******************FASTLED
//
//void FASTLED_crossfadepalette() {
//  ChangePalettePeriodically();
// 
//  // nblendPaletteTowardPalette() will crossfade current palette slowly toward the target palette.
//  //
//  // Each time that nblendPaletteTowardPalette is called, small changes
//  // are made to currentPalette to bring it closer to matching targetPalette.
//  // You can control how many changes are made in each call:
//  //   - the default of 24 is a good balance
//  //   - meaningful values are 1-48.  1=veeeeeeeery slow, 48=quickest
//  //   - "0" means do not change the currentPalette at all; freeze
//
//  EVERY_N_MILLISECONDS(100) {
//    uint8_t maxChanges = 30; 
//    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);
//  }
//
// EVERY_N_MILLISECONDS(thisdelay) {
//  static uint8_t startIndex = 0;
//  startIndex += 1;                                 // motion speed
//  FillLEDsFromPaletteColors(startIndex);
// }
//
//  FastLED.show();
//}
//
//void FillLEDsFromPaletteColors(uint8_t colorIndex) {
//  
//  for(int i = 0; i < NUM_LEDS; i++) {
//    FLED1[i] = ColorFromPalette(currentPalette, colorIndex + sin8(i*16), 255);
//    FLED2[i] = ColorFromPalette(currentPalette, colorIndex + sin8(i*16), 255);
//    FLED3[i] = ColorFromPalette(currentPalette, colorIndex + sin8(i*16), 255);
//    colorIndex += 3;
//  }
//
//} // FillLEDsFromPaletteColors()
//
//
// 
//void ChangePalettePeriodically() {
//  
//  uint8_t secondHand = (millis() / 1000) % 60;
//  static uint8_t lastSecond = 99;
//  
//  if(lastSecond != secondHand) {
//    lastSecond = secondHand;
//    CRGB p = CHSV(HUE_PURPLE, 255, 255);
//    CRGB g = CHSV(HUE_GREEN, 255, 255);
//    CRGB b = CRGB::Black;
//    CRGB w = CRGB::White;
//    if(secondHand ==  0)  { targetPalette = RainbowColors_p; }
//    if(secondHand == 10)  { targetPalette = CRGBPalette16(g,g,b,b, p,p,b,b, g,g,b,b, p,p,b,b); }
//    if(secondHand == 20)  { targetPalette = CRGBPalette16(b,b,b,w, b,b,b,w, b,b,b,w, b,b,b,w); }
//    if(secondHand == 30)  { targetPalette = LavaColors_p; }
//    if(secondHand == 40)  { targetPalette = CloudColors_p; }
//    if(secondHand == 50)  { targetPalette = PartyColors_p; }
//  }
//  
//} // ChangePalettePeriodically()
//        
