#include <TimerOne.h>

volatile int i=0;                // Variable to use as a counter
volatile boolean zero_cross = 1; // Boolean to store a "switch" to tell us if we have crossed zero
int AC_pin = 13;                 // Output to Opto Triac
int dim = 0;                     // Dimming level (0-128)  0 = on, 128 = 0ff
int inc = 1;                     // counting up or down, 1=up, -1=down

int freqStep = 60;    // This is the delay-per-brightness step in microseconds.
// It is calculated based on the frequency of your voltage supply (50Hz or 60Hz)
// and the number of brightness steps you want. 
// 
// The only tricky part is that the chopper circuit chops the AC wave twice per
// cycle, once on the positive half and once at the negative half. This meeans
// the chopping happens at 120Hz for a 60Hz supply or 100Hz for a 50Hz supply. 

// To calculate freqStep you divide the length of one full half-wave of the power
// cycle (in microseconds) by the number of brightness steps. 
//
// (1000000 uS / 120 Hz) / 128 brightness steps = 65 uS / brightness step
//
// 1000000 us / 120 Hz = 8333 uS, length of one half-wave.

void setup() {
  pinMode(AC_pin, OUTPUT);                          // Set the Triac pin as output
  attachInterrupt(1, zero_cross_detect, FALLING);    // Attach an Interupt to Pin 3 (interupt 0) for Zero Cross Detection
  Timer1.initialize(freqStep);                      // Initialize TimerOne library for the freq we need
  Timer1.attachInterrupt(dim_check, freqStep);
  Serial.begin(9600);
  // Use the TimerOne Library to attach an interrupt
  // to the function we use to check to see if it is 
  // the right time to fire the triac.  This function 
  // will now run every freqStep in microseconds.                                            
}

void zero_cross_detect() {    
  zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
  i = 0;
  digitalWrite(AC_pin, LOW);       // turn off TRIAC (and AC)
}                                 

// Turn on the TRIAC at the appropriate time
void dim_check() {                   
  if(zero_cross == true) {              
    if(i >= dim) {
      digitalWrite(AC_pin, HIGH); // turn on light       
      i=0;  // reset time step counter                         
      zero_cross = false; //reset zero cross detection
    } 
    else {
      i++; // increment time step counter
    }                                
  }                                  
}                                   

void loop() {
  if (Serial.available()){
  
  }
  
  dim += inc;
  if((dim >= 128) || (dim <= 0))
    inc*=-1;
  
  delay(50);
}
