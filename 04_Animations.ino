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
  for (int i=1;i<DATA_LEDNUM;i++) {
    wave_r[i]=nextColor(1, wave_r[i-1], animationRange[0], animationRange[4], r_dir);
    wave_g[i]=nextColor(2, wave_g[i-1], animationRange[1], animationRange[5], g_dir);
    wave_b[i]=nextColor(3, wave_b[i-1], animationRange[2], animationRange[6], b_dir);
    wave_w[i]=nextColor(4, wave_w[i-1], animationRange[3], animationRange[7], w_dir);
  }
}

void startraum_wave() {
  for (int i=0;i<DATA_LEDNUM;i++) {
    NPLED1.setPixelColor(i, wave_r[i], wave_g[i], wave_b[i], wave_w[i]);
    NPLED2.setPixelColor(i, wave_r[i], wave_g[i], wave_b[i], wave_w[i]);
    NPLED3.setPixelColor(i, wave_r[i], wave_g[i], wave_b[i], wave_w[i]);
    wave_r[i]=nextColor(1, wave_r[i], animationRange[0], animationRange[4], r_dir);
    wave_g[i]=nextColor(2, wave_g[i], animationRange[1], animationRange[5], g_dir);
    wave_b[i]=nextColor(3, wave_b[i], animationRange[2], animationRange[6], b_dir);
    wave_w[i]=nextColor(4, wave_w[i], animationRange[3], animationRange[7], w_dir);
  }
  LED_update_all();
  delay(10);
}


void animationChange() {
  for (int i=0; i<PIXELNUM;i++) {
    NPLED1.setPixelColor(i, wave_r[i], wave_g[i], wave_b[i], wave_w[i]);
    NPLED2.setPixelColor(i, wave_r[i], wave_g[i], wave_b[i], wave_w[i]);
    NPLED3.setPixelColor(i, wave_r[i], wave_g[i], wave_b[i], wave_w[i]);
    int j= 2*PIXELNUM-i-1;
    NPLED1.setPixelColor(j, wave_r[j], wave_g[j], wave_b[j], wave_w[j]);
    NPLED2.setPixelColor(j, wave_r[j], wave_g[j], wave_b[j], wave_w[j]);
    NPLED3.setPixelColor(j, wave_r[j], wave_g[j], wave_b[j], wave_w[j]);
    LED_update_all();
  }
  for (int i=0; i<PIXELNUM;i++) {
    int k= i+2*PIXELNUM;
    NPLED1.setPixelColor(k, wave_r[k], wave_g[k], wave_b[k], wave_w[k]);
    NPLED2.setPixelColor(k, wave_r[k], wave_g[k], wave_b[k], wave_w[k]);
    NPLED3.setPixelColor(k, wave_r[k], wave_g[k], wave_b[k], wave_w[k]);
    int j= 4*PIXELNUM-i-1;
    NPLED1.setPixelColor(j, wave_r[j], wave_g[j], wave_b[j], wave_w[j]);
    NPLED2.setPixelColor(j, wave_r[j], wave_g[j], wave_b[j], wave_w[j]);
    NPLED3.setPixelColor(j, wave_r[j], wave_g[j], wave_b[j], wave_w[j]);
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
    LED_staticColor_all(r,g,b,w);
  LED_update_all();
  delay(20);
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
