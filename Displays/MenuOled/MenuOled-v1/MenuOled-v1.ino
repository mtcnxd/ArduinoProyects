#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 

#define KEY_NONE 0
#define KEY_PREV 1
#define KEY_NEXT 2
#define KEY_SELECT 3
#define KEY_BACK 4

// DOGS102 shield configuration values
//uint8_t uiKeyPrev = 2;
//uint8_t uiKeyNext = 4;
//uint8_t uiKeySelect = 5;
//uint8_t uiKeyBack = 3;

// DOGM128-Shield	 configuration values
// DOGXL60-Shield configuration values
uint8_t uiKeyPrev = 7;
uint8_t uiKeyNext = 3;
uint8_t uiKeySelect = 2;
uint8_t uiKeyBack = 8;

uint8_t uiKeyCodeFirst = KEY_NONE;
uint8_t uiKeyCodeSecond = KEY_NONE;
uint8_t uiKeyCode = KEY_NONE;


void uiSetup(void) {
  // configure input keys 
  
  pinMode(uiKeyPrev, INPUT);           // set pin to input
  digitalWrite(uiKeyPrev, HIGH);       // turn on pullup resistors
  pinMode(uiKeyNext, INPUT);           // set pin to input
  digitalWrite(uiKeyNext, HIGH);       // turn on pullup resistors
  pinMode(uiKeySelect, INPUT);           // set pin to input
  digitalWrite(uiKeySelect, HIGH);       // turn on pullup resistors
  pinMode(uiKeyBack, INPUT);           // set pin to input
  digitalWrite(uiKeyBack, HIGH);       // turn on pullup resistors
}

void uiStep(void) {
  uiKeyCodeSecond = uiKeyCodeFirst;
  if ( digitalRead(uiKeyPrev) == LOW )
    uiKeyCodeFirst = KEY_PREV;
  else if ( digitalRead(uiKeyNext) == LOW )
    uiKeyCodeFirst = KEY_NEXT;
  else if ( digitalRead(uiKeySelect) == LOW )
    uiKeyCodeFirst = KEY_SELECT;
  else if ( digitalRead(uiKeyBack) == LOW )
    uiKeyCodeFirst = KEY_BACK;
  else 
    uiKeyCodeFirst = KEY_NONE;
  
  if ( uiKeyCodeSecond == uiKeyCodeFirst )
    uiKeyCode = uiKeyCodeFirst;
  else
    uiKeyCode = KEY_NONE;
}


#define MENU_ITEMS 4
char *menu_strings[MENU_ITEMS] = { "Marcos", "Cindy", "Indira", "Ricardo" };

uint8_t menu_current = 0;
uint8_t menu_redraw_required = 0;
uint8_t last_key_code = KEY_NONE;


void drawMenu(void) {
  uint8_t i, h;
  u8g_uint_t w, d;

  u8g.setFont(u8g_font_6x13);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  
  h = u8g.getFontAscent()-u8g.getFontDescent();
  w = u8g.getWidth();
  for( i = 0; i < MENU_ITEMS; i++ ) {
    d = (w-u8g.getStrWidth(menu_strings[i]))/2;
    u8g.setDefaultForegroundColor();
    if ( i == menu_current ) {
      u8g.drawBox(0, i*h+1, w, h);
      u8g.setDefaultBackgroundColor();
    }
    u8g.drawStr(d, i*h, menu_strings[i]);
  }
}

void updateMenu(void) {
  if ( uiKeyCode != KEY_NONE && last_key_code == uiKeyCode ) {
    return;
  }
  last_key_code = uiKeyCode;
  
  switch ( uiKeyCode ) {
    case KEY_NEXT:
      menu_current++;
      if ( menu_current >= MENU_ITEMS )
        menu_current = 0;
      menu_redraw_required = 1;
      break;
    case KEY_PREV:
      if ( menu_current == 0 )
        menu_current = MENU_ITEMS;
      menu_current--;
      menu_redraw_required = 1;
      break;
  }
}


void setup() {
  // rotate screen, if required
  // u8g.setRot180();
  
  uiSetup();                                // setup key detection and debounce algorithm
  menu_redraw_required = 1;     // force initial redraw
}

void loop() {  

  uiStep();                                     // check for key press
    
  if (  menu_redraw_required != 0 ) {
    u8g.firstPage();
    do  {
      drawMenu();
    } while( u8g.nextPage() );
    menu_redraw_required = 0;
  }

  updateMenu();                            // update menu bar
  
}
