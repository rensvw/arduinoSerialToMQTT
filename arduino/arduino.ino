// Define integers settings for Arduino

int calibrationTime = 5; //the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int armTimeOut = 3; // the time before the alarm is activated
int disableTimeOut = 5; // The time a user has to disable the alarm
int alarmState = 0; // alarmState 0 = Residents are present, alarmState 1 =  Residents are absent
boolean armed = false; // set default armed state

// Define variables for the constant DIGITAL OUTPUT PINS on the Arduino
// See documentation for detailed description of sensors

//---------------Sensors------------//
const int motionSensor = 2;    // Motion sensor
const int lightSensor = 2; // Light Sensor
const int tempSensor = 6; // Temparature Sensors
const int proxSensor = 9; // Proximity Sensor
const int doorSensor = 4; // Door contact
const int windowSensor = 5; // Window contact

const int activateButton = 10; // Alarm activation button
const int deactivateButton = 12; // Alarm deactivation button

//---------------Actuators----------//
const int buzzer = 6; // Buzzer that is activated when the timeOut phase is activated
const int siren = 7; // Siren when alarm is activated
const int lightsLivingRoom = 8; // Lights for the livingroom
const int heating = 9; // A heating device simulated by a Red Light

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // Set PINMODE for sensors
  pinMode(motionSensor, INPUT_PULLUP);
  pinMode(lightSensor,INPUT);
  pinMode(tempSensor,INPUT);
  pinMode(proxSensor,INPUT);
  pinMode(doorSensor,INPUT);
  pinMode(windowSensor,INPUT);

  pinMode(activateButton,INPUT);
  pinMode(deactivateButton,INPUT);  

  // Set PINMODE for Actuators
  pinMode(buzzer, OUTPUT);
  pinMode(siren,OUTPUT); 
  pinMode(lightsLivingRoom, OUTPUT);
  pinMode(heating, OUTPUT);

  // Initialize low status for all sensors
  digitalWrite(buzzer,LOW);
  digitalWrite(motionSensor, LOW);
  digitalWrite(siren, LOW);

  // Calibrate sensor so that it doesn't immediately activates itself
  calibrateSensor();
  }  
}

void loop() {
    // Read States of Sensors
    motionSensorState = digitalRead(motionSensor);
    //lightSensorState = digitalRead(lightSensor);
    // tempSensorState = digitalRead(tempSensor); // Code that reads Temperature sensor
    // proxSensorState = readIR(5);               // Code that reads Proximity sensor
    doorSensorState = digitalRead(doorSensor);
    windowSensorState = digitalRead(windowSensor);

    // Read States of Actuators
    buzzerState = digitalRead(buzzer);
    sirenState = digitalRead(siren);
    lightsLivingRoomState = digitalRead(lightsLivingRoom);
    heatingState = digitalRead(heating);
    
    // Define message
    String message = Serial.readStringUntil('#');  

   if(message == "lightOn"){
    digitalWrite(lightsLivingRoom, HIGH);   // Turn the LED on 
    Serial.println("{'lamp':'1','heating':'"+ String(heatingState) + "','movingSensor':'"+ String(motionSensorState) + "','doorSensor':'"+ String(doorSensorState) + "','windowSensor':'" + String(windowSensorState) + "','tempSensor':'" + String(tempSensorState) + "','lightSensor':'" + String(lightSensorState) + "'}");
    delay(1000); 
  }
   if(message == "lighOff"){  
    digitalWrite(lightsLivingRoom, LOW);    // Turn the LED off
    Serial.println("{'lamp':'0','heating':'"+ String(heatingState) + "','movingSensor':'"+ String(motionSensorState) + "','doorSensor':'"+ String(doorSensorState) + "','windowSensor':'" + String(windowSensorState) + "','tempSensor':'" + String(tempSensorState) + "','lightSensor':'" + String(lightSensorState) + "'}");
    delay(1000); 
  }

  if(message == "heatingOn"){
    digitalWrite(heating, HIGH); // Simulate the heating by turning the red light on
    Serial.println("{'lamp':'"+ String(lightsLivingRoomState) + "','heating':'"+ String(heatingState) + "','movingSensor':'"+ String(motionSensorState) + "','doorSensor':'"+ String(doorSensorState) + "','windowSensor':'" + String(windowSensorState) + "','tempSensor':'" + String(tempSensorState) + "','lightSensor':'" + String(lightSensorState) + "'}");
    delay(1000); 
  }

  if(message == "heatingOff"){
    digitalWrite(heating, LOW); // Simulate the heating by turning the red light on
    Serial.println("{'lamp':'"+ String(lightsLivingRoomState) + "','heating':'"+ String(heatingState) + "','movingSensor':'"+ String(motionSensorState) + "','doorSensor':'"+ String(doorSensorState) + "','windowSensor':'" + String(windowSensorState) + "','tempSensor':'" + String(tempSensorState) + "','lightSensor':'" + String(lightSensorState) + "'}");
    delay(1000); 
  }

  Serial.println("{'lamp':'"+ String(lightsLivingRoomState) + "','heating':'"+ String(heatingState) + "','movingSensor':'"+ String(motionSensorState) + "','doorSensor':'"+ String(doorSensorState) + "','windowSensor':'" + String(windowSensorState) + "','tempSensor':'" + String(tempSensorState) + "','lightSensor':'" + String(lightSensorState) + "'}");
  delay(1000);
} 