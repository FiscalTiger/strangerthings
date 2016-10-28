#include <Adafruit_NeoPixel.h>
#include <stdlib.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define A_LETTER 0
#define B_LETTER 1
#define C_LETTER 2
#define D_LETTER 3
#define E_LETTER 4
#define F_LETTER 5
#define G_LETTER 6
#define H_LETTER 7
#define I_LETTER 16
#define J_LETTER 15
#define K_LETTER 14
#define L_LETTER 13
#define M_LETTER 12
#define N_LETTER 11
#define O_LETTER 10
#define P_LETTER 9
#define Q_LETTER 8
#define R_LETTER 17
#define S_LETTER 18
#define T_LETTER 19
#define U_LETTER 20
#define V_LETTER 21
#define W_LETTER 22
#define X_LETTER 23
#define Y_LETTER 24
#define Z_LETTER 25

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

uint16_t button_count = 0;

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  printRand();
  
//  colorWipe(strip.Color(255, 0, 0), 50);
  delay(500);
//  printRun();
//  printHappy();
}

void printRun() {
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t blue = strip.Color(0, 0, 255);
  uint32_t green = strip.Color(0, 255, 0);
  uint32_t yellow = strip.Color(255, 255, 0);

  uint32_t colors[4] = {red, blue, green, yellow};

  uint8_t wait = 80;

  strip.setPixelColor(R_LETTER, R_LETTER % 4);
  delay(wait);
  strip.setPixelColor(U_LETTER, U_LETTER % 4);
  delay(wait);
  strip.setPixelColor(N_LETTER, N_LETTER % 4);
  delay(wait);
  
}

void printRand() {
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t blue = strip.Color(0, 0, 255);
  uint32_t green = strip.Color(0, 255, 0);
  uint32_t yellow = strip.Color(255, 255, 0);

  uint32_t colors[4] = {red, blue, green, yellow};

  uint8_t wait = 50;

  uint32_t randLetter = (int)(rand() * 6);

  colorWipe(strip.Color(0, 0, 0), 50);
  strip.setPixelColor(randLetter, colors[randLetter % 4]);
  strip.show();
  delay(wait);
}

void printHappy() {
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t blue = strip.Color(0, 0, 255);
  uint32_t green = strip.Color(0, 255, 0);
  uint32_t yellow = strip.Color(255, 255, 0);

  uint32_t colors[4] = {red, blue, green, yellow};

  uint8_t wait = 80;

  strip.setPixelColor(H_LETTER, colors[H_LETTER % 4]);
  delay(wait);
  strip.setPixelColor(A_LETTER, A_LETTER % 4);
  delay(wait);
  strip.setPixelColor(P_LETTER, P_LETTER % 4);
  delay(wait);
  strip.setPixelColor(P_LETTER, P_LETTER % 4);
  delay(wait);
  strip.setPixelColor(Y_LETTER, Y_LETTER % 4);
  delay(wait);
  strip.setPixelColor(A_LETTER, 0);
  delay(wait);

  strip.setPixelColor(H_LETTER, H_LETTER % 4);
  delay(wait);
  strip.setPixelColor(A_LETTER, A_LETTER % 4);
  delay(wait);
  strip.setPixelColor(L_LETTER, L_LETTER % 4);
  delay(wait);
  strip.setPixelColor(L_LETTER, L_LETTER % 4);
  delay(wait);
  strip.setPixelColor(O_LETTER, O_LETTER % 4);
  delay(wait);
  strip.setPixelColor(W_LETTER, W_LETTER % 4);
  delay(wait);
  strip.setPixelColor(E_LETTER, E_LETTER % 4);
  delay(wait);
  strip.setPixelColor(E_LETTER, E_LETTER % 4);
  delay(wait);
  strip.setPixelColor(N_LETTER, N_LETTER % 4);
  delay(wait);
  
  strip.setPixelColor(A_LETTER, 0);
  delay(wait);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
