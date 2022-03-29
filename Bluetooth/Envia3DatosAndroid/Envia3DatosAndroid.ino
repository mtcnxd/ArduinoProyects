int var1 = 10;
int var2 = 10;
int var3 = 10;

void setup () {
  Serial.begin(9600);
}

void loop () {

  if (var3 < 99) {
    var1 = var1 + 1 ;
    var2 = var2 + 2 ;
    var3 = var3 + 3 ;  
  } 
  else {
    var1 = 10;
    var2 = 10;
    var3 = 10;    
  }

  Serial.print(var1);
  Serial.println ("A");    
  Serial.print (var2);
  Serial.println ("B");  
  Serial.print (var3);
  Serial.println ("C");    
  delay(1000);
}


