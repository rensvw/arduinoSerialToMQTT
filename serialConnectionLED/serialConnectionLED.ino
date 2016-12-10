// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
    // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() {
  
    String message = Serial.readStringUntil('#');
  

   if(message == "aan"){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    Serial.println("{'lamp':'aan','verwarming':'UNDEFINED','bewegingssensor':'UNDEFINED','tempsensor':'UNDEFINED'}");
    delay(1000); 
  }
   if(message == "uit"){  
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    Serial.println("{'lamp':'uit','verwarming':'UNDEFINED','bewegingssensor':'UNDEFINED','tempsensor':'UNDEFINED'}");
    delay(1000); 
  }

  }

 