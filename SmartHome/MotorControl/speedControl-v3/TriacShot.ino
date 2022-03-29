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

void changeSpeed(int Speed){
  switch(Speed){
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

