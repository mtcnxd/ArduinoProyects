#include <TimerOne.h>

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

void setup() {
  pinMode(AC_pin, OUTPUT);
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);

  attachInterrupt(1, zero_cross_detect, FALLING);
  Timer1.initialize(freqStep);
  Timer1.attachInterrupt(dim_check, freqStep);
  Serial.begin(9600);
}

void zero_cross_detect() {    
  zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
  i = 0;
  digitalWrite(AC_pin, LOW);       // turn off TRIAC (and AC)
}                                 

void dim_check() {                   
  if(zero_cross == true) {              
    if(i >= dim) {
      digitalWrite(AC_pin, HIGH); // turn on light       
      i=0;  // reset time step counter                         
      zero_cross = false; //reset zero cross detection
    } 
    else {
      i++;
    }                                
  }                                  
}                                   

void loop() {
  if (Serial.available()){
    char value = Serial.read();

    switch(value){
    case '0':
      dim = 128;
      break;
      
    case '1':
      dim = 45;
      break;

    case '2':
      dim = 36;
      break;

    case '3':
      dim = 27;
      break;

    case '4':
      dim = 18;
      break;

    case '5':
      dim = 9;
      break;

    case '6':
      dim = 0;
      break;
    }
  }
  delay(50);
  Serial.println(dim);
}
