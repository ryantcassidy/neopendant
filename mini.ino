#include <Adafruit_NeoPixel.h>

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
  delay(100);
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
