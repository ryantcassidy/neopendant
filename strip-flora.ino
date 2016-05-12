#include <Adafruit_NeoPixel.h>

#define PIN 0

#define STRIP_LEN 19
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_LEN, PIN, NEO_GRB);

#define CENTER 12
#define RING1 6
#define RING2 12

#define ROWS 7
#define COLS 5

// in clock order
uint8_t ring1[RING1] = {13, 14, 15, 16, 17, 18};
uint8_t ring2[RING2] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0};

// COLS
uint8_t leftCol[3] = {8, 9, 10};
uint8_t rightCol[3] = {2, 3, 4};
uint8_t leftMidCol[4] = {11, 16, 17, 7};
uint8_t rightMidCol[4] = {1, 13, 14, 5};
uint8_t centerCol[5] = {0, 12, 18, 6, 15};

// ROWS
uint8_t firstRow[3] = {11, 0, 1};
uint8_t secondRow[3] = {10, 2, 12};
uint8_t thirdRow[2] = {13, 17};
uint8_t fourthRow[3] = {9, 18, 3};
uint8_t fifthRow[2] = {14, 16};
uint8_t sixthRow[3] = {8, 4, 15};
uint8_t seventhRow[3] = {5, 6, 7};
uint8_t rowLengths[ROWS]={3,3,2,3,2,3,3};
uint8_t* rows[ROWS] = {firstRow, secondRow, thirdRow, fourthRow, fifthRow, sixthRow, seventhRow};

#define PEACE_LEN 17
uint8_t peaceSign[PEACE_LEN] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 18, 15, 16, 14};
#define SMILE_LEN 9
uint8_t smileyFace[SMILE_LEN] = {11, 1, 3, 4, 5, 6, 7, 8, 9};
#define SPOKES_LEN 13
uint8_t spokes[SPOKES_LEN] = {0, 2, 4, 6, 8, 10, 12, 13, 14, 15, 16, 17, 18};
#define LINE_LEN 5
uint8_t line[LINE_LEN] = {0, 12, 18, 15, 6};

void drawShape(uint32_t c, uint8_t shape[], uint8_t shape_len) {
    for (uint8_t i = 0; i < shape_len; i++) {
        strip.setPixelColor(cs(shape[i]), c);
    }
    strip.show();
}

void clearShape(uint8_t shape[], uint8_t shape_len) {
    drawShape(strip.Color(0,0,0), shape, shape_len);
}

// clock style coords
// outer ring is 0-11,
// inner ring is 12-17,
// center is 18
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

// reverse translation
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
    strip.setBrightness(50);
    strip.show(); // Initialize all pixels to 'off'
}

void loop() {

    setAll(strip.Color(255, 255, 255));

    //blinkInOrder(500);

    fillRings();

    bubblePop(strip.Color(0, 255, 100));
    bubblePop(strip.Color(100, 255, 100));
    bubblePop(strip.Color(255, 255, 255));
    bubblePop(strip.Color(255, 0, 255));
    bubblePop(strip.Color(10, 20, 166));

    // Some example procedures showing how to display to the pixels:
    drawShape(strip.Color(255, 255, 0), peaceSign, PEACE_LEN);
    delay(1000);
    clearPixels();
    drawShape(strip.Color(255, 255, 0), smileyFace, SMILE_LEN);
    delay(1000);
    clearPixels();
    drawShape(strip.Color(255, 255, 0), spokes, SPOKES_LEN);
    delay(1000);
    clearPixels();
    drawShape(strip.Color(255, 255, 0), line, LINE_LEN);
    delay(1000);
    spinOneCircle(100);
    spinOneCircle(100);
    spinOneCircle(100);
    clearPixels();

    /*for (uint8_t j = 0; j < 255; j++) {
      drawShape(Wheel(j), peaceSign, PEACE_LEN);
      delay(100);
      }*/

    spinOneCircle(400);
    clearPixels();

    fillColumns(strip.Color(255,0,255));
    clearPixels();
    fallingRows(strip.Color(0, 255, 0));

    rainbowLoop();

    clearPixels();

    colorWipe(strip.Color(255, 0, 0), 500); // Red
    colorWipe(strip.Color(0, 255, 0), 500); // Green
    colorWipe(strip.Color(0, 0, 255), 500); // Blue

    //rainbowCycle(20);
}

void setCenter(uint32_t c) {
    strip.setPixelColor(CENTER, c);
    strip.show();
}

void setRing1(uint32_t c) {
    for (uint8_t i = 0; i < RING1; i++) {
        strip.setPixelColor(ring1[i], c);
    }
    strip.show();
}

void setRing2(uint32_t c) {
    for (uint8_t i = 0; i < RING2; i++) {
        strip.setPixelColor(ring2[i], c);
    }
    strip.show();
}

void setAll(uint32_t c) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
    }
    strip.show();
}

void setAll(uint32_t c, uint32_t b) {
    strip.setBrightness(b);
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
    }
    strip.show();
}

void clearPixel(uint8_t i) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
}

void clearPixels() {
    setAll(strip.Color(0, 0, 0));
}

/*void blinkInOrder(int timedelay) {
    clearPixels();
    for (uint8_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(cs(i), 255, 255, 255);
        strip.show();
        delay(timedelay);
        clearPixel(cs(i));
    }
}*/

void fillRings() {
    uint32_t c = strip.Color(255, 255, 255);

    setCenter(c);
    delay(1000);
    setRing1(c);
    delay(1000);
    setRing2(c);
    delay(1000);
    clearPixels();
}

void bubblePop(uint32_t c) {
    setCenter(c);
    delay(500);
    clearPixels();
    setRing1(c);
    delay(500);
    clearPixels();
    setRing2(c);
    delay(500);
    clearPixels();
}

void fillColumns(uint32_t c) {
    // todo: shorthand this like rows?
    drawShape(c, leftCol, 3);
    delay(500);
    drawShape(c, leftMidCol, 4);
    delay(500);
    drawShape(c, centerCol, 5);
    delay(500);
    drawShape(c, rightMidCol, 4);
    delay(500);
    drawShape(c, rightCol, 3);
    delay(500);
    clearPixels();
}

void fallingRows(uint32_t c) {
    for(uint8_t rowsDropped=0;rowsDropped<7;rowsDropped++){
        for(uint8_t rowsBlinked=0;rowsBlinked<7;rowsBlinked++){
            drawShape(c, rows[rowsBlinked], rowLengths[rowsBlinked]);
            delay(300);
            if(rowsDropped >= 6 - rowsBlinked){
                break;
            }
            clearShape(rows[rowsBlinked], rowLengths[rowsBlinked]);
        }
    }
}

/*void increasePixelBrightness(uint8_t i, uint8_t bdelta){
  uint32_t c = strip.getPixelColor(i);
  uint8_t r = (uint8_t)(c >> 16);
  uint8_t g = (uint8_t)(c >> 8);
  uint8_t b = (uint8_t)c;

  uint8_t newr, newg, newb;

  newr = addWithoutOverflow(r, bdelta);
  newg = addWithoutOverflow(g, bdelta);
  newb = addWithoutOverflow(b, bdelta);

  strip.setPixelColor(i, newr, newg, newb);
  strip.show();
  }

  void decreasePixelBrightness(uint8_t i, uint8_t bdelta){
  uint32_t c = strip.getPixelColor(i);
  uint8_t r = (uint8_t)(c >> 16);
  uint8_t g = (uint8_t)(c >> 8);
  uint8_t b = (uint8_t)c;

  uint8_t newr, newg, newb;

  newr = subWithoutUnderflow(r, bdelta);
  newg = subWithoutUnderflow(g, bdelta);
  newb = subWithoutUnderflow(b, bdelta);

  strip.setPixelColor(i, newr, newg, newb);
  strip.show();
  }

  uint8_t addWithoutOverflow(int a, int b){
  if((255 - a) < b){ return 255; }
  else{ return a + b; }
  }

  uint8_t subWithoutUnderflow(int a, int b){
  if((255 - a) < b || a < b){ return 0; }
  else{ return a - b; }
  }*/

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(cs(i), c);
        strip.show();
        delay(wait);
    }
}

/*// Slightly different, this makes the rainbow equally distributed throughout
  void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
  for (i = 0; i < strip.numPixels(); i++) {
  strip.setPixelColor(cs(i), Wheel(((i * 256 / strip.numPixels()) + j) & 255));
  }
  strip.show();
  delay(wait);
  }
  }*/

void rotatePendant() {
    uint32_t prev1, prev2, temp;
    for (uint8_t x = 0; x < RING2; x++) {
        if (x == 0) {
            prev2 = strip.getPixelColor(ring2[RING2 - 2]);
            prev1 = strip.getPixelColor(ring2[RING2 - 1]);
        }
        temp = strip.getPixelColor(ring2[x]);
        strip.setPixelColor(ring2[x], prev2);
        prev2 = prev1;
        prev1 = temp;
    }
    for (uint8_t x = 0; x < RING1; x++) {
        if (x == 0) {
            prev1 = strip.getPixelColor(ring1[RING1 - 1]);
        }
        temp = strip.getPixelColor(ring1[x]);
        strip.setPixelColor(ring1[x], prev1);
        prev1 = temp;
    }
    strip.show();
}

void spinOneCircle(int timeDelay) {
    for (int a = 0; a < 6; a++) {
        rotatePendant();
        delay(timeDelay);
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
/*uint32_t Wheel(byte WheelPos) {
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
  }*/

void rainbowLoop() {
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
            drawShape(c, peaceSign, PEACE_LEN);
            delay(50);
        }
    }
}
