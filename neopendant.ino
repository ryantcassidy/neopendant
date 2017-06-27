#include <Adafruit_NeoPixel.h>
//#include "letters.h"

#define PIN 0

#define STRIP_LEN 19
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_LEN, PIN, NEO_GRB);

// Actual strip indices for pixels on pendant
uint8_t center = 12;
#define RING1_LEN 6
uint8_t ring1[RING1_LEN] = {13, 14, 15, 16, 17, 18};
#define RING2_LEN 12
uint8_t ring2[RING2_LEN] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0};

// COLS
#define COLS 5
uint8_t leftCol[3] = {10, 9, 8};
uint8_t leftMidCol[4] = {11, 17, 16, 7};
uint8_t centerCol[5] = {0, 12, 18, 15, 6};
uint8_t rightMidCol[4] = {1, 13, 14, 5};
uint8_t rightCol[3] = {2, 3, 4};
uint8_t colLengths[COLS] = {3, 4, 5, 4, 3};
uint8_t* cols[COLS] = {leftCol, leftMidCol, centerCol, rightMidCol, rightCol};

// ROWS
#define ROWS 7
uint8_t firstRow[3] = {11, 0, 1};
uint8_t secondRow[3] = {10, 2, 12};
uint8_t thirdRow[2] = {13, 17};
uint8_t fourthRow[3] = {9, 18, 3};
uint8_t fifthRow[2] = {14, 16};
uint8_t sixthRow[3] = {8, 4, 15};
uint8_t seventhRow[3] = {5, 6, 7};
uint8_t rowLengths[ROWS] = {3, 3, 2, 3, 2, 3, 3};
uint8_t* rows[ROWS] = {firstRow, secondRow, thirdRow, fourthRow, fifthRow, sixthRow, seventhRow};

uint8_t diagonalWipe[STRIP_LEN] = {8, 7, 6, 9, 16, 15, 5, 10, 17, 18, 14, 4, 11, 12, 13, 3, 0, 1, 2};

#define PEACE_LEN 17
uint8_t peaceSign[PEACE_LEN] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 18, 15, 16, 14};
#define SMILE_LEN 9
uint8_t smileyFace[SMILE_LEN] = {11, 1, 3, 4, 5, 6, 7, 8, 9};
#define SPOKES_LEN 13
uint8_t spokes[SPOKES_LEN] = {0, 2, 4, 6, 8, 10, 12, 13, 14, 15, 16, 17, 18};
#define LINE_LEN 5
uint8_t line[LINE_LEN] = {0, 12, 18, 15, 6};

uint32_t WHITE = strip.Color(255, 255, 255);

uint32_t RED = strip.Color(255, 0, 0);
uint32_t ORANGE = strip.Color(255, 128, 0);
uint32_t YELLOW = strip.Color(255, 255, 0);
uint32_t GREEN = strip.Color(0, 255, 0);
uint32_t BLUE = strip.Color(0, 0, 255);
uint32_t INDIGO = strip.Color(75, 0, 130);
uint32_t VIOLET = strip.Color(139, 0, 255);

#define RAINBOW_LEN 7
// ADD MORE
uint32_t rainbow[RAINBOW_LEN] = {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET};

/*
   Clock-style         Actual hardware addresses
        0                      1
    11     1                0    2
  10    12     2         11    13     3
     17     13              18    14
  9      18      3       10    12      4
    16    14               17    15
  8     15     4         9     16     5
     7     5                8     6
        6                      7
*/

// hardware -> clock-style
uint8_t cs(uint8_t coord) {
  if (coord == 18) {
    return 12;
  }
  else if (coord == 11) {
    return 0;
  }
  else {
    return coord + 1;
  }
}

// reverse translation -- clock-style -> hardware
uint8_t sc(uint8_t pixel) {
  if (pixel == 0) {
    return 11;
  }
  else if (pixel == 12) {
    return 18;
  }
  else {
    return pixel - 1;
  }
}

void setup() {
  strip.begin();
  strip.setBrightness(15);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  paintAll(strip.Color(255, 255, 255));
  delay(100);
  clearPixels();

  //demoRaining(50);

  demoMatrix(50);

  rainbowBubblePop(300);
  demoRainbowRadiate(300);


  // paintShape(strip.Color(0, 200, 100), smileyFace, SMILE_LEN);
  //spinOneCircle(500);
  //clearPixels();

  paintShape(strip.Color(0, 200, 100), line, LINE_LEN);
  //  spinOneCircle(500);
  clearPixels();

  demoColumns(strip.Color(255, 0, 255), 100);
  demoColumns(strip.Color(0, 0, 255), 100);

  //  demoFallingRows(strip.Color(0, 255, 0));

  //rainbowLoop();
  clearPixels();

  /*rainbowShape(letterF, F_LEN, 5);
    rainbowShape(letterI, I_LEN, 5);
    rainbowShape(letterR, R_LEN, 5);
    rainbowShape(letterE, E_LEN, 5);
    rainbowShape(letterF, F_LEN, 5);
    rainbowShape(letterL, L_LEN, 5);
    rainbowShape(letterY, Y_LEN, 5);*/

  demoColorWipe(200);

  demoDiagonalColorWipe(200);

  rainbowShape(diagonalWipe, STRIP_LEN, 100);

  //demoColumns(strip.Color(0,128,255), 200);
//  lToRFill(strip.Color(255, 10,10), 4, 200);

  /*demoShapeWipe(letterE, E_LEN, RED, 100);
    demoShapeWipe(letterK, K_LEN, BLUE, 100);
    demoShapeWipe(letterA, A_LEN, YELLOW, 100);
    demoShapeWipe(letterV, V_LEN, GREEN, 100);
    demoShapeWipe(letterQ, Q_LEN, VIOLET, 100);*/
}

// UTIL-----------------------------------------
// set functions -- just change the pixel, don't call show()
void setPixel(uint8_t i, uint32_t c) {
  strip.setPixelColor(i, c);
}

void setCenter(uint32_t c) {
  strip.setPixelColor(center, c);
}

void setRing1(uint32_t c) {
  for (uint8_t i = 0; i < RING1_LEN; i++) {
    strip.setPixelColor(ring1[i], c);
  }
}

void setRing2(uint32_t c) {
  for (uint8_t i = 0; i < RING2_LEN; i++) {
    strip.setPixelColor(ring2[i], c);
  }
}

void setAll(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
}

// paint functions -- call show() after changing the pixels
void paintPixel(uint8_t i, uint32_t c) {
  setPixel(i, c);
  strip.show();
}

void paintCenter(uint32_t c) {
  setCenter(c);
  strip.show();
}

void paintRing1(uint32_t c) {
  setRing1(c);
  strip.show();
}

void paintRing2(uint32_t c) {
  setRing2(c);
  strip.show();
}

void paintAll(uint32_t c) {
  setAll(c);
  strip.show();
}

void paintShape(uint32_t c, uint8_t shape[], uint8_t shape_len) {
  for (uint8_t i = 0; i < shape_len; i++) {
    strip.setPixelColor(cs(shape[i]), c);
  }
  strip.show();
}


// clear functions -- blank out a pixel and call show()
void clearPixel(uint8_t i) {
  strip.setPixelColor(i, strip.Color(0, 0, 0));
  strip.show();
}

void clearPixels() {
  paintAll(strip.Color(0, 0, 0));
}

void clearShape(uint8_t shape[], uint8_t shape_len) {
  paintShape(strip.Color(0, 0, 0), shape, shape_len);
}

// bubble pop and rainbow radiate!
void bubblePop(uint32_t c, int delayTime) {
  paintCenter(c);
  delay(delayTime);
  clearPixels();

  paintRing1(c);
  delay(delayTime);
  clearPixels();

  paintRing2(c);
  delay(delayTime);
  clearPixels();
}

void fillRings(uint32_t c, int wait) {
  paintCenter(c);
  delay(wait);
  paintRing1(c);
  delay(wait);
  paintRing2(c);
  delay(wait);
}

void demoRainbowRadiate(int waitTime) {
  for (uint8_t times = 0; times < 2; times++) {
    for (uint8_t i = 0; i < RAINBOW_LEN; i++) {
      fillRings(rainbow[i], 150);
    }
  }
  clearPixels();
}

void rainbowBubblePop(int delayTime) {
  for (uint8_t i = 0; i < RAINBOW_LEN; i++) {
    bubblePop(rainbow[i], delayTime);
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    paintPixel(cs(i), c);
    delay(wait);
  }
}

void demoColorWipe(uint8_t wait) {
  for (uint8_t i = 0; i < RAINBOW_LEN; i++) {
    colorWipe(rainbow[i], wait);
  }
}

// Fill the dots one after the other with a color
void diagonalColorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    paintPixel(cs(diagonalWipe[i]), c);
    delay(wait);
  }
}

void demoDiagonalColorWipe(uint8_t wait) {
  for (uint8_t i = 0; i < RAINBOW_LEN; i++) {
    diagonalColorWipe(rainbow[i], wait);
  }
}

void demoShapeWipe(uint8_t shape[], uint8_t shapeLen, uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < shapeLen; i++) {
    paintPixel(cs(shape[i]), c);
    delay(wait);
  }
  clearPixels();
  delay(wait);
  paintShape(c, shape, shapeLen);
  delay(wait * 5);
  clearShape(shape, shapeLen);
}

void demoShape(uint32_t c, uint8_t shape[], uint8_t shape_len, int waitTime) {
  clearPixels();
  paintShape(c, shape, shape_len);
  delay(waitTime);
  clearPixels();
}

/*void demoBlinkInOrder(int timedelay) {
  clearPixels();
  for (uint8_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(cs(i), 255, 255, 255);
    strip.show();
    delay(timedelay);
    clearPixel(cs(i));
  }
}*/

// Rows & Columns
void demoColumns(uint32_t c, uint16_t wait) {
  clearPixels();
  // todo: shorthand this like rows?
  uint8_t i, x;
  for (i = 0; i < 2; i++) {
    for (x = 0; x < COLS; x++) {
      paintShape(c, cols[x], colLengths[x]);
      delay(wait);
    }
    for (x = 0; x < COLS; x++) {
      clearShape(cols[x], colLengths[x]);
      delay(wait);
    }
  }

  clearPixels();
}

/*void tronSwipe(uint16_t wait) {
  for (uint8_t i = 0; i < RAINBOW_LEN; i++) {
    columnStripe(rainbow[i], wait);
  }
}*/

/*void lToRFill(uint8_t times, uint32_t c, uint16_t wait) {
  for (uint8_t i = 0; i < times; i++) {
    for (uint8_t x = 0; x < COLS; x++) {
      paintShape(c, cols[x], colLengths[x]);
      delay(wait);
    }
    for (uint8_t x = 0; x <= COLS; x++) {
      clearShape(cols[COLS - x], colLengths[COLS - x]);
      delay(wait);
    }
  }
}*/

/*void columnStripe(uint32_t c, uint16_t wait) {
  for (uint8_t x = 0; x < COLS; x++) {
    paintShape(c, cols[x], colLengths[x]);
    delay(wait);
    clearShape(cols[x], colLengths[x]);
  }
}*/

/*void demoFallingRows(uint32_t c) {
  clearPixels();
  for (uint8_t rowsDropped = 0; rowsDropped < 7; rowsDropped++) {
    for (uint8_t rowsBlinked = 0; rowsBlinked < 7; rowsBlinked++) {
      paintShape(c, rows[rowsBlinked], rowLengths[rowsBlinked]);
      delay(100);
      if (rowsDropped >= 6 - rowsBlinked) {
        break;
      }
      clearShape(rows[rowsBlinked], rowLengths[rowsBlinked]);
    }
  }
  delay(300);
  clearPixels();
  }*/

void demoRaining(uint16_t wait) {
  clearPixels();
  uint8_t order[COLS] = {3, 2, 0, 4, 1};
  for (uint8_t colsRained = 0; colsRained < COLS; colsRained++) {
    uint8_t numFrames = colLengths[order[colsRained]] + 2; // for trail
    for (uint8_t frame = 0; frame < numFrames; frame++) {
      if (frame < (numFrames - 2)) {
        setPixel(cs(cols[order[colsRained]][frame]), strip.Color(0, 0, 255));
      }
      if (frame > 0 && frame < (numFrames - 1)) {
        setPixel(cs(cols[order[colsRained]][frame - 1]), strip.Color(0, 0, 128));
      }
      if (frame > 1) {
        setPixel(cs(cols[order[colsRained]][frame - 2]), strip.Color(0, 0, 30));
      }
      strip.show();
      delay(wait);
      clearShape(cols[order[colsRained]], colLengths[order[colsRained]]);
    }
  }
  }


void demoMatrix(uint16_t wait) {
  clearPixels();
  uint8_t order[COLS] = {3, 2, 0, 4, 1};
  paintAll(strip.Color(0, 20, 0));
  for (uint8_t colsRained = 0; colsRained < COLS; colsRained++) {
    uint8_t numFrames = colLengths[order[colsRained]] + 2; // for trail
    for (uint8_t frame = 0; frame < numFrames; frame++) {
      if (frame < (numFrames - 2)) {
        setPixel(cs(cols[order[colsRained]][frame]), strip.Color(0, 255, 0));
      }
      if (frame > 0 && frame < (numFrames - 1)) {
        setPixel(cs(cols[order[colsRained]][frame - 1]), strip.Color(0, 128, 0));
      }
      if (frame > 1) {
        setPixel(cs(cols[order[colsRained]][frame - 2]), strip.Color(0, 40, 0));
      }
      strip.show();
      delay(wait);
      paintShape(strip.Color(0, 20, 0), cols[order[colsRained]], colLengths[order[colsRained]]);
    }
  }
}

// Letters...

/*void demoAlphabet(uint32_t c, uint16_t wait) {
  for (uint8_t i = 0; i < ALPHABET; i++) {
    demoShapeWipe(letters[i], letter_len[i], c, wait);
  }
  }*/



/*// Rotation! Uses current pendant lit pixels
  // one 'tick' of the pendant, aka 1/6 rotation
  void rotatePendant() {
  uint32_t prev1, prev2, temp;
  for (uint8_t x = 0; x < RING2_LEN; x++) {
    if (x == 0) {
      prev2 = strip.getPixelColor(ring2[RING2_LEN - 2]);
      prev1 = strip.getPixelColor(ring2[RING2_LEN - 1]);
    }
    temp = strip.getPixelColor(ring2[x]);
    strip.setPixelColor(ring2[x], prev2);
    prev2 = prev1;
    prev1 = temp;
  }
  for (uint8_t x = 0; x < RING1_LEN; x++) {
    if (x == 0) {
      prev1 = strip.getPixelColor(ring1[RING1_LEN - 1]);
    }
    temp = strip.getPixelColor(ring1[x]);
    strip.setPixelColor(ring1[x], prev1);
    prev1 = temp;
  }
  strip.show();
  }

  // take current design and spin one full time
  void spinOneCircle(int timeDelay) {
  for (int a = 0; a < 7; a++) {
    delay(timeDelay);
    rotatePendant();

  }
  }*/

// Rainbow Math

void rainbowShape(uint8_t shape[], uint8_t shape_len, uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 3; j++) { // 3 cycles of all colors on wheel
    for (i = 0; i < shape_len; i++) {
      strip.setPixelColor(cs(shape[i]), Wheel(((i * 256 / shape_len) + j) & 255));
    }
    strip.show();
    delay(wait);
  }

  clearPixels();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3, 0);
  } else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0, 0);
  }
}

/*void rainbowLoop() {
  uint8_t rgbColour[3];

  // Start off with red.
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0;

  // Choose the colours to increment and decrement.
  for (uint8_t decColour = 0; decColour < 3; decColour += 1) {
    uint8_t incColour = decColour == 2 ? 0 : decColour + 1;

    // cross-fade the two colours.
    for (uint8_t i = 0; i < 255; i += 1) {
      rgbColour[decColour] -= 1;
      rgbColour[incColour] += 1;

      uint32_t c = strip.Color(rgbColour[0], rgbColour[1], rgbColour[2]);
      // TODO: modular-ize this
      paintShape(c, peaceSign, PEACE_LEN);
      delay(10);
    }
  }
  }*/
