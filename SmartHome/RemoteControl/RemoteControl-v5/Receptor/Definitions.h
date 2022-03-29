#include <Arduino.h>

const int switchRightPin = 2;
const int switchLeftPin = 3;
const int outputPin = 4;
const int pilotPin = 5;

boolean canChange = true;

int toggle = 1;

const uint64_t pipe = 0xE8E8F0F0E1LL;

//const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL }; 
