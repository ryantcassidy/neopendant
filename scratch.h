// brightness stuff !! Maybe replace with a scaler?
void increasePixelBrightness(uint8_t i, uint8_t bdelta) {
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

void decreasePixelBrightness(uint8_t i, uint8_t bdelta) {
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

uint8_t addWithoutOverflow(int a, int b) {
    if ((255 - a) < b) {
        return 255;
    }
    else {
        return a + b;
    }
}

uint8_t subWithoutUnderflow(int a, int b) {
    if ((255 - a) < b || a < b) {
        return 0;
    }
    else {
        return a - b;
    }
}
