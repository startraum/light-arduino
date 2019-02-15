
//Definitions
//**********************************************
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



//***********************************************Setup()
//  LEDS.addLeds<LED_TYPE, LED_DT1, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2812
//  LEDS.addLeds<LED_TYPE, LED_DT2, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2812
//  LEDS.addLeds<LED_TYPE, LED_DT3, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2812



//**********************************************Function

//void FASTLED_Palletwave() {
//   EVERY_N_SECONDS( SECONDS_PER_PALETTE ) {
//    gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, gGradientPaletteCount);
//    gTargetPalette = gGradientPalettes[ gCurrentPaletteNumber ];
//  }
//
//  EVERY_N_MILLISECONDS(250) {           //das ändert wie lange die Überbeldnphase zwischen den Pallettes ist
//    nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 16);
//  }
//  
//  colorwaves( leds, NUM_LEDS, gCurrentPalette);
//
//  FastLED.show();
//  FastLED.delay(45);
//}
//
//// This function draws color waves with an ever-changing,
//// widely-varying set of parameters, using a color palette.
//void colorwaves( CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette) 
//{
//  static uint16_t sPseudotime = 0;
//  static uint16_t sLastMillis = 0;
//  static uint16_t sHue16 = 0;
// 
//  uint8_t sat8 = beatsin88( 87, 220, 250);
//  uint8_t brightdepth = beatsin88( 341, 96, 224);
//  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
//  uint8_t msmultiplier = beatsin88(147, 23, 60);
//
//  uint16_t hue16 = sHue16;//gHue * 256;
//  uint16_t hueinc16 = beatsin88(113, 300, 1500);
//  
//  uint16_t ms = millis();
//  uint16_t deltams = ms - sLastMillis ;
//  sLastMillis  = ms;
//  sPseudotime += deltams * msmultiplier;
//  sHue16 += deltams * beatsin88( 400, 5,9);
//  uint16_t brightnesstheta16 = sPseudotime;
//  
//  for( uint16_t i = 0 ; i < numleds; i++) {
//    hue16 += hueinc16;
//    uint8_t hue8 = hue16 / 256;
//    uint16_t h16_128 = hue16 >> 7;
//    if( h16_128 & 0x100) {
//      hue8 = 255 - (h16_128 >> 1);
//    } else {
//      hue8 = h16_128 >> 1;
//    }
//
//    brightnesstheta16  += brightnessthetainc16;
//    uint16_t b16 = sin16(0.2*brightnesstheta16  ) + 32768;      //der Multiplikator bestimmt wie schenll und viel die einzelnen Wellen sichtbar sind
//
//    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
//    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
//    bri8 += (255 - brightdepth);
//    
//    uint8_t index = hue8;
//    //index = triwave8( index);
//    index = scale8( index, 240);
//
//    CRGB newcolor = ColorFromPalette( palette, index, bri8);
//
//    uint16_t pixelnumber = i;
//    pixelnumber = (numleds-1) - pixelnumber;
//    
//    nblend( ledarray[pixelnumber], newcolor, 128);
//  }
//}
//
//// Alternate rendering function just scrolls the current palette 
//// across the defined LED strip.
//void palettetest( CRGB* ledarray, uint16_t numleds, const CRGBPalette16& gCurrentPalette)
//{
//  static uint8_t startindex = 0;
//  startindex--;
//  fill_palette( ledarray, numleds, startindex, (256 / NUM_LEDS) + 1, gCurrentPalette, 255, LINEARBLEND);
//}
//
//
//
//
//
//// Gradient Color Palette definitions for 33 different cpt-city color palettes.
////    956 bytes of PROGMEM for all of the palettes together,
////   +618 bytes of PROGMEM for gradient palette code (AVR).
////  1,494 bytes total for all 34 color palettes and associated code.
//
//// Gradient palette "ib_jul01_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul01.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 16 bytes of program space.
//
//
//
//
//
////hier kommen die Standard Gradients rein
//
//
//
//// Gradient palette "ib_jul01_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul01.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 16 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( ib_jul01_gp ) {
//    0, 194,  1,  1,
//   94,   1, 29, 18,
//  132,  57,131, 28,
//  255, 113,  1,  1};
//
//// Gradient palette "es_vintage_57_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_57.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 20 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_vintage_57_gp ) {
//    0,   2,  1,  1,
//   53,  18,  1,  0,
//  104,  69, 29,  1,
//  153, 167,135, 10,
//  255,  46, 56,  4};
//
//// Gradient palette "es_vintage_01_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_01.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 32 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_vintage_01_gp ) {
//    0,   4,  1,  1,
//   51,  16,  0,  1,
//   76,  97,104,  3,
//  101, 255,131, 19,
//  127,  67,  9,  4,
//  153,  16,  0,  1,
//  229,   4,  1,  1,
//  255,   4,  1,  1};
//
//
//// Gradient palette "rgi_15_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/rgi/tn/rgi_15.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 36 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( rgi_15_gp ) {
//    0,   4,  1, 31,
//   31,  55,  1, 16,
//   63, 197,  3,  7,
//   95,  59,  2, 17,
//  127,   6,  2, 34,
//  159,  39,  6, 33,
//  191, 112, 13, 32,
//  223,  56,  9, 35,
//  255,  22,  6, 38};
//
//// Gradient palette "Analogous_1_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/red/tn/Analogous_1.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 20 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( Analogous_1_gp ) {
//    0,   3,  0,255,
//   63,  23,  0,255,
//  127,  67,  0,255,
//  191, 142,  0, 45,
//  255, 255,  0,  0};
//
//// Gradient palette "es_pinksplash_08_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/pink_splash/tn/es_pinksplash_08.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 20 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_pinksplash_08_gp ) {
//    0, 126, 11,255,
//  127, 197,  1, 22,
//  175, 210,157,172,
//  221, 157,  3,112,
//  255, 157,  3,112};
//
//// Gradient palette "es_pinksplash_07_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/pink_splash/tn/es_pinksplash_07.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 28 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_pinksplash_07_gp ) {
//    0, 229,  1,  1,
//   61, 242,  4, 63,
//  101, 255, 12,255,
//  127, 249, 81,252,
//  153, 255, 11,235,
//  193, 244,  5, 68,
//  255, 232,  1,  5};
//  
//// Gradient palette "es_ocean_breeze_068_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_068.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 24 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_ocean_breeze_068_gp ) {
//    0, 100,156,153,
//   51,   1, 99,137,
//  101,   1, 68, 84,
//  104,  35,142,168,
//  178,   0, 63,117,
//  255,   1, 10, 10};
//
//// Gradient palette "es_ocean_breeze_036_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_036.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 16 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_ocean_breeze_036_gp ) {
//    0,   1,  6,  7,
//   89,   1, 99,111,
//  153, 144,209,255,
//  255,   0, 73, 82};
//
//
//// Gradient palette "es_landscape_64_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/landscape/tn/es_landscape_64.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 36 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_landscape_64_gp ) {
//    0,   0,  0,  0,
//   37,   2, 25,  1,
//   76,  15,115,  5,
//  127,  79,213,  1,
//  128, 126,211, 47,
//  130, 188,209,247,
//  153, 144,182,205,
//  204,  59,117,250,
//  255,   1, 37,192};
//
//// Gradient palette "es_landscape_33_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/landscape/tn/es_landscape_33.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 24 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_landscape_33_gp ) {
//    0,   1,  5,  0,
//   19,  32, 23,  1,
//   38, 161, 55,  1,
//   63, 229,144,  1,
//   66,  39,142, 74,
//  255,   1,  4,  1};
//
//// Gradient palette "gr64_hult_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/hult/tn/gr64_hult.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 32 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( gr64_hult_gp ) {
//    0,   1,124,109,
//   66,   1, 93, 79,
//  104,  52, 65,  1,
//  130, 115,127,  1,
//  150,  52, 65,  1,
//  201,   1, 86, 72,
//  239,   0, 55, 45,
//  255,   0, 55, 45};
//
//// Gradient palette "GMT_drywet_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_drywet.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 28 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( GMT_drywet_gp ) {
//    0,  47, 30,  2,
//   42, 213,147, 24,
//   84, 103,219, 52,
//  127,   3,219,207,
//  170,   1, 48,214,
//  212,   1,  1,111,
//  255,   1,  7, 33};
//
//// Gradient palette "ib15_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/general/tn/ib15.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 24 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( ib15_gp ) {
//    0, 113, 91,147,
//   72, 157, 88, 78,
//   89, 208, 85, 33,
//  107, 255, 29, 11,
//  141, 137, 31, 39,
//  255,  59, 33, 89};
//
//
//// Gradient palette "lava_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/elem/tn/lava.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 52 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( lava_gp ) {
//    0,   0,  0,  0,
//   46,  18,  0,  0,
//   96, 113,  0,  0,
//  108, 142,  3,  1,
//  119, 175, 17,  1,
//  146, 213, 44,  2,
//  174, 255, 82,  4,
//  188, 255,115,  4,
//  202, 255,156,  4,
//  218, 255,203,  4,
//  234, 255,255,  4,
//  244, 255,255, 71,
//  255, 255,255,255};
//
//
//
//
////New set 1
//// Sammlung der Gradients
//
//
//
//
//// Gradient palette "GMT_elevation_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_elevation.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 44 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( GMT_elevation_gp ) {
//    0,  25, 81, 50,
//    1,  34,103, 63,
//    7,  45,119, 73,
//   21,  82,136, 88,
//   36, 155,151,105,
//   72, 157,124, 84,
//  109, 157,136,108,
//  145, 161,164,149,
//  182, 177,186,180,
//  218, 213,219,214,
//  255, 232,237,233};
//
//
//// Gradient palette "ib_jul03_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul03.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 36 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( ib_jul03_gp ) {
//    0,  13, 70, 49,
//   30,   2, 38, 18,
//   43,  13, 70, 49,
//  119, 152,  1,  1,
//  127, 175,  1,  1,
//  142,  72,  2,  0,
//  211,  63, 49, 21,
//  247,  58,103, 62,
//  255,  58,103, 62};
//
//
//// Gradient palette "ib_jul06_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul06.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 8 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( ib_jul06_gp ) {
//    0,  24, 49, 57,
//  255, 169, 20, 25};
//
//// Gradient palette "ib_jul07_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul07.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 24 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( ib_jul07_gp ) {
//    0,  24, 49, 57,
//   48,  47, 16, 21,
//   66,  82,  1,  4,
//  147, 208, 21, 33,
//  173,  88, 33, 44,
//  255,  24, 49, 57};
//
//
//// Gradient palette "es_vintage_54_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_54.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 20 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_vintage_54_gp ) {
//    0,   0,  0,  0,
//  101,   7,  1,  1,
//  127,  20,  1,  2,
//  153,   8,  1,  1,
//  255,   0,  0,  0};
//
//
//  // Gradient palette "es_vintage_37_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_37.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 20 bytes of program space.
//
//
//
//// Gradient palette "es_coffee_29_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/coffee/tn/es_coffee_29.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 32 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_coffee_29_gp ) {
//    0, 169,20,25,
//   38,   7,  1,  0,
//   76,   1,  1,  1,
//  127,   0,  0,  0,
//  178,   1,  1,  1,
//  216,   7,  1,  0,
//  255, 82,1,4};
//
//// Gradient palette "es_emerald_dragon_01_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/emerald_dragon/tn/es_emerald_dragon_01.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 20 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_emerald_dragon_01_gp ) {
//    0,   1,  1,  1,
//   79,   1, 19,  7,
//  130,   1, 59, 25,
//  229,  28,255,255,
//  255,  28,255,255};
//
//// Gradient palette "es_emerald_dragon_02_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/emerald_dragon/tn/es_emerald_dragon_02.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 28 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_emerald_dragon_02_gp ) {
//    0,   0,  1,  0,
//   61,   1,  5,  2,
//   96,   2, 15, 11,
//  127,  23, 47, 40,
//  155,   2, 15, 11,
//  193,   1,  4,  2,
//  255,   0,  0,  0};
//
//// Gradient palette "es_emerald_dragon_30_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/emerald_dragon/tn/es_emerald_dragon_30.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 40 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_emerald_dragon_30_gp ) {
//    0,   0,  1,  1,
//   19,   0,  1,  1,
//   38,   1,  1,  1,
//   76,   1,  3,  4,
//  114,   1,  5,  6,
//  134,   1,  8, 10,
//  153,   2, 12, 15,
//  191,   9, 34, 35,
//  227,  48, 93, 99,
//  255, 133,186,205};
//
//
//DEFINE_GRADIENT_PALETTE( es_emerald_dragon_30_gp_1 ) {
//    0,   0,  1,  1,
//   19,   0,  1,  1,
//   38,   1,  1,  1,
//   76,   1,  3,  4,
//  114,   1,  5,  6,
//  134,   1,  8, 10,
//  153,   2, 12, 15,
//  191,   9, 50, 35,
//  227,  48, 93, 99,
//  255, 133,186,186};
//
//  DEFINE_GRADIENT_PALETTE( es_emerald_dragon_30_gp_2 ) {
//    0,   0,  1,  1,
//   19,   0,  1,  1,
//   38,   1,  1,  1,
//   76,   1,  3,  4,
//  114,   1,  5,  6,
//  134,   1,  8, 10,
//  153,   2, 17, 10,
//  191,   9, 34, 15,
//  227,  48, 110, 89,
//  255, 133,205,160};
//
//
//  DEFINE_GRADIENT_PALETTE( es_emerald_dragon_30_gp_red ) {
//    0,   1,  0,  0,
//   19,   1,  0,  0,
//   38,   1,  1,  1,
//   76,   4,  2,  1,
//  114,   6,  3,  1,
//  134,   10,  4, 1,
//  153,   15, 5, 2,
//  191,   35, 13, 5,
//  227,   100, 40, 15,
//  255,   205,66,30};
//
//
//// Gradient palette "es_ocean_breeze_070_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_070.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 20 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_ocean_breeze_070_gp ) {
//    0, 135,149,138,
//  101,   1, 19, 11,
//  104, 135,149,138,
//  178,   4, 43, 33,
//  255,   0,  0,  1};
//
//// Gradient palette "es_ocean_breeze_071_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_071.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 20 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_ocean_breeze_071_gp ) {
//    0,   1,  4,  1,
//  101,   1,  1,  1,
//  104,  91,  5,  1,
//  204,  87, 26,  2,
//  255,  74, 40,  2};
//
//// Gradient palette "es_seadreams_01_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/sea_dreams/tn/es_seadreams_01.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 28 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_seadreams_01_gp ) {
//    0,   4, 46, 91,
//   38,  20,128,192,
//   89,  41,184,186,
//  127, 137,227,233,
//  209, 232,225,182,
//  249, 220,225,207,
//  255, 220,225,207};
//
//  // Gradient palette "Afterdusk_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Afterdusk.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 44 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( Afterdusk_gp ) {
//    0,   0,  0,  0,
//   25,   1,  1,  1,
//   48,   1,  1,  1,
//   67,  41, 49, 52,
//   70, 210,219,216,
//   73, 155,115,137,
//   81, 109, 46, 78,
//   86, 109, 46, 78,
//   97, 109, 46, 78,
//  165,  50, 15, 79,
//  255,  16,  1, 80};
//
//// Gradient palette "Alien_Green_Planet_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Alien_Green_Planet.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 36 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( Alien_Green_Planet_gp ) {
//    0,   0,  0,  0,
//   25,   1,  1,  1,
//   51,   3,  7,  4,
//   96,  46, 71, 46,
//  102, 159,213,153,
//  107,  64,117, 87,
//  122,  16, 51, 42,
//  182,  56, 84, 52,
//  255, 132,125, 63};
//
//
//
//
//
//// New Set 2
//
//
//
//
//
//
//// Gradient palette "es_skywalker_06_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/skywalker/tn/es_skywalker_06.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 16 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_skywalker_06_gp ) {
//    0,   6, 29, 41,
//   76,   1, 17, 38,
//  153,   1,  9, 21,
//  255,   0,  1,  1};
//
//  // Gradient palette "es_seadreams_08_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/sea_dreams/tn/es_seadreams_08.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 20 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_seadreams_08_gp ) {
//    0,   0,  0,255,
//   63,  31, 45,233,
//  112, 213,169,247,
//  249,   4, 81,219,
//  255,   4, 81,219};
//
//
//// Gradient palette "es_ocean_breeze_074_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_074.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 28 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_ocean_breeze_074_gp ) {
//    0,   1,  1,  1,
//  101,  34, 23,  3,
//  127,  53, 26,  2,
//  130, 203, 65,  7,
//  153,  78, 56,  8,
//  191,  22, 37, 11,
//  255,   1,  4,  1};
//
//
//
//// Gradient palette "es_emerald_dragon_04_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/emerald_dragon/tn/es_emerald_dragon_04.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 12 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_emerald_dragon_04_gp ) {
//    0,  18, 60, 68,
//  153,   3,  1,  1,
//  255,   1,  1,  1};
//
//
//// Gradient palette "Night_Dark_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Night_Dark.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 36 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( Night_Dark_gp ) {
//    0,  11,  2, 19,
//   25,  10, 12, 33,
//   63,   9, 31, 51,
//   85,   9, 31, 51,
//  100,   9, 31, 50,
//  106,  31, 54, 69,
//  114,  69, 82, 92,
//  149,  34, 29, 48,
//  255,  12,  4, 19};
//
//  // Gradient palette "RedsandCyans_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/RedsandCyans.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 36 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( RedsandCyans_gp ) {
//    0,  15, 96,135,
//   78,  40, 87, 74,
//  102,  83, 80, 34,
//  114, 113, 71, 29,
//  127, 150, 63, 25,
//  143,  60, 79, 66,
//  182,  15, 96,135,
//  223,  15, 96,135,
//  255,  15, 96,135};
//
//// Gradient palette "BW_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/strips/tn/BW.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 96 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( BW_gp ) {
//   31,   0,  0,  0,
//   31, 255,255,255,
//   63, 255,255,255,
//   63,   0,  0,  0,
//   95,   0,  0,  0,
//  95, 255,255,255,
//  127, 255,255,255,
//  127,   0,  0,  0,
//  159,   0,  0,  0,
//  159, 255,255,255,
//  191, 255,255,255,
//  191,   0,  0,  0,
//  223,   0,  0,  0,
//  223, 255,255,255};
//
//DEFINE_GRADIENT_PALETTE( BW_gp_bigger ) {
//   42,   0,  0,  0,
//   42, 255,255,255,
//   84, 255,255,255,
//   84,   0,  0,  0,
//   126,   0,  0,  0,
//  126, 255,255,255,
//  168, 255,255,255,
//  168,   0,  0,  0,
//  212,   0,  0,  0,
//  212, 255,255,255};
//  
//
//  // Gradient palette "cw2_088_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cw/2/tn/cw2-088.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 12 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( cw2_088_gp ) {
//    0,   1,  4,  4,
//  127,   1,  2, 34,
//  255,  19, 21, 43};
//
//  
//// Gradient palette "Neutral_04_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/vermillion/tn/Neutral_04.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 12 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( Neutral_04_gp ) {
//    0,  20,  4,  1,
//  127, 132,  8,  2,
//  255, 255,  15,  4};
//
//
//// Gradient palette "es_ocean_breeze_078_gp", originally from
//// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_078.png.index.html
//// converted for FastLED with gammas (2.6, 2.2, 2.5)
//// Size: 20 bytes of program space.
//
//DEFINE_GRADIENT_PALETTE( es_ocean_breeze_078_gp ) {
//    0,   1,  3,  5,
//   63,   1,  1,  2,
//  127,   1,  1,  1,
//  130,  77, 77, 68,
//  255,   1, 40, 84};
//
//
//DEFINE_GRADIENT_PALETTE( ivory_gp ) {
//    0, 239,229,182,
//  255, 255,255,255};
//
//
//// Single array of defined cpt-city color palettes.
//// This will let us programmatically choose one based on
//// a number, rather than having to activate each explicitly 
//// by name every time.
//// Since it is const, this array could also be moved 
//// into PROGMEM to save SRAM, but for simplicity of illustration
//// we'll keep it in a regular SRAM array.
////
//// This list of color palettes acts as a "playlist"; you can
//// add or delete, or re-arrange as you wish.
//const TProgmemRGBGradientPalettePtr gGradientPalettes[] = {
//
//ivory_gp,
//
//es_ocean_breeze_036_gp,
////  rgi_15_gp,
////  Analogous_1_gp,
////  es_pinksplash_08_gp,
////  es_ocean_breeze_068_gp,
////  es_ocean_breeze_078_gp,
////  //es_pinksplash_07_gp,  //delete?
////  es_vintage_01_gp,
////  es_landscape_33_gp,
////  gr64_hult_gp,
////  GMT_drywet_gp,
////  ib_jul01_gp,  //niiiice
////  es_vintage_57_gp, 
////  ib15_gp,
////  
////  // hier wirds dunkel rot
////  lava_gp,      
////  es_emerald_dragon_30_gp_red,
////  es_emerald_dragon_30_gp_red,
//
//
//
//
//  // New Set 1
//
//// GMT_elevation_gp, //P finds gut bis medium
////ib_jul03_gp, //geil
////ib_jul06_gp,  //geil
////ib_jul07_gp,   // maybe too much of this?
////es_vintage_54_gp,  // nice dark - combo? - maybe more orange?
////es_coffee_29_gp,   // mit anderen Farben Vlt?#
////
////// hier kmmmt blau zu schwarz 
////es_emerald_dragon_01_gp,   //Porno
////es_emerald_dragon_02_gp,   //Porno
////es_emerald_dragon_30_gp,
////es_emerald_dragon_30_gp_1, //Porno -> mehr dunkel!
////es_emerald_dragon_30_gp_2,
////
////es_ocean_breeze_070_gp,
////
////
////es_ocean_breeze_071_gp, //KP Porno P porno - hammer muss mit anderen Farben angewandt werden
//////es_emerald_dragon_30_gp_red,  //make me red
////es_seadreams_01_gp,   // andere location?
////Afterdusk_gp, //was macht das?
////Alien_Green_Planet_gp,
////
////
////
//////New Set 2
////
////
////
////es_skywalker_06_gp,   //easy watch Blau
////es_seadreams_08_gp,   //easy watch Blau maybe zu lame?
////es_ocean_breeze_074_gp,  //Knaller jeah jeah 
////es_emerald_dragon_04_gp,  //najaaa
////Night_Dark_gp,  //medium eher
////
////
////
////RedsandCyans_gp,//nice nice nice - nochmal benutzen
////BW_gp_bigger,  //Combo Master
////cw2_088_gp,
//
//
// 
//
//  
//  };
//
//
//// Count of how many cpt-city gradients are defined:
//const uint8_t gGradientPaletteCount = 
//  sizeof( gGradientPalettes) / sizeof( TProgmemRGBGradientPalettePtr );
