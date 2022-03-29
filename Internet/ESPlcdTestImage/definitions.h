// Software SPI (slower updates, more flexible pin options):
// pin 14 - Serial clock out (SCLK)
// pin 13 - Serial data out (DIN)
// pin 12 - Data/Command select (D/C)
// pin 5 - LCD chip select (CS)
// pin 2 - LCD reset (RST)

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

int contador = 0;

const uint8_t termometer[] PROGMEM = {
  0x00, 0x60, 0xFE, 0xF9, 0xFE, 0x60, 0x00, 0x00
};

const uint8_t happy[] PROGMEM = {
  0x00, 0x20, 0x20, 0x2E, 0xE0, 0xAE, 0xE0, 0x00
};

const uint8_t bateria[] PROGMEM = {
  0x00, 0xFE, 0xF2, 0xF3, 0xF3, 0xF2, 0xFE, 0x00
};
