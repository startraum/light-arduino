//LEDStrips
//*****************

void LEDStripInit() {
  for (int i=0; i<PinNum; i++) {
    LEDstrip[i].begin();
    LEDstrip[i].setBrightness(BRIGHTNESS);
    LEDstrip[i].show();
  }
}

