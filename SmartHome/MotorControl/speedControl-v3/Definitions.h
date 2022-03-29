#include <Arduino.h>

volatile int i=0;                // Variable to use as a counter
volatile boolean zero_cross = 1; // Boolean to store a "switch" to tell us if we have crossed zero

int AC_pin = 13;                 // Output to Opto Triac
int dim = 0;                     // Dimming level (0-128)  0 = on, 128 = 0ff
int inc = 1;                     // counting up or down, 1=up, -1=down
int segmentA = 4;
int segmentB = 5;
int segmentC = 6;
int segmentD = 7;

int freqStep = 60;
