#include <OneWire.h> // Include Onewire for the digital Temperature Sensor

// Define variables for the constant OUTPUT PINS on the Arduino
// See documentation for detailed description of sensors

//---------------Sensors------------//
//const int motionSensor = 2;    // Motion sensor
const int delayTime = 300;
const int lightSensor = A0; // Light Sensor
OneWire ds(2); // Temparature Sensors
const int proxSensor = 3; // Proximity Sensor
const int doorSensor = 4; // Door contact
const int windowSensor = 7; // Window contact

// Motion is being measured with a Distance sensor, so that when the Lego House is being moved(while there is no motion inside, the alarm won't go off)
const int trigPin = 9;
const int echoPin = 8;

//---------------Actuators----------//
const int buzzer = 88; // Buzzer that is activated when the timeOut phase is activated

const int lightsLivingRoom = 11; // Lights for the livingroom
const int heating = 12; // A heating device simulated by a Red Light

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // Set PINMODE for sensors
  pinMode(lightSensor,INPUT);
  pinMode(tempSensor,INPUT);
  pinMode(proxSensor,INPUT);
  pinMode(doorSensor,INPUT_PULLUP);
  pinMode(windowSensor,INPUT_PULLUP);

  // Set PINMODE for Distance sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set PINMODE for Actuators
  pinMode(buzzer, OUTPUT);
  pinMode(siren,OUTPUT); 
  pinMode(lightsLivingRoom, OUTPUT);
  pinMode(heating, OUTPUT);

  // Initialize low status for Buzzer
  digitalWrite(buzzer,LOW);
}

void loop() {
    // Read States of Sensors
    int lightSensorState = analogRead(lightSensor);            
    int doorSensorState = digitalRead(doorSensor);
    int windowSensorState = digitalRead(windowSensor);

    // Read States of Actuators
    int buzzerState = digitalRead(buzzer);
    int sirenState = digitalRead(siren);
    int lightsLivingRoomState = digitalRead(lightsLivingRoom);
    int heatingState = digitalRead(heating);
    
    //Run Code for distance sensor that detects motion
    long duration, distance;
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    
    //Run code for temperature sensor
    byte data[2];
    ds.reset(); 
    ds.write(0xCC);
    ds.write(0x44);
    delay(750);
    ds.reset();
    ds.write(0xCC);
    ds.write(0xBE);
    data[0] = ds.read(); 
    data[1] = ds.read();
    int Temp = (data[1]<<8)+data[0];
    Temp = Temp>>4;
    
    
    // Define message
    String message = Serial.readStringUntil('#');  
    if(message == "lightOn"){
      digitalWrite(lightsLivingRoom, HIGH);   // Turn the LED on 
      Serial.println("{'lamp':'"+ String(digitalRead(lightsLivingRoom)) + "','heating':'"+ String(heatingState) + "','movingSensor':'"+ String(distance) + "','doorSensor':'"+ String(doorSensorState) + "','windowSensor':'" + String(windowSensorState) + "','tempSensor':'" + String(Temp) + "','lightSensor':'" + String(lightSensorState) + "'}");
      delay(delayTime); 
    }
    if(message == "lightOff"){  
      digitalWrite(lightsLivingRoom, LOW);    // Turn the LED off
      Serial.println("{'lamp':'"+ String(digitalRead(lightsLivingRoom)) + "','heating':'"+ String(heatingState) + "','movingSensor':'"+ String(distance) + "','doorSensor':'"+ String(doorSensorState) + "','windowSensor':'" + String(windowSensorState) + "','tempSensor':'" + String(Temp) + "','lightSensor':'" + String(lightSensorState) + "'}");
      delay(delayTime); 
    }

    if(message == "heatingOn"){
      digitalWrite(heating, HIGH); // Simulate the heating by turning the red light on
      Serial.println("{'lamp':'"+ String(lightsLivingRoomState) + "','heating':'"+ String(digitalRead(heating)) + "','movingSensor':'"+ String(distance) + "','doorSensor':'"+ String(doorSensorState) + "','windowSensor':'" + String(windowSensorState) + "','tempSensor':'" + String(Temp) + "','lightSensor':'" + String(lightSensorState) + "'}");
      delay(delayTime); 
    }

    if(message == "heatingOff"){
      digitalWrite(heating, LOW); // Simulate the heating by turning the red light on
      Serial.println("{'lamp':'"+ String(lightsLivingRoomState) + "','heating':'"+ String(digitalRead(heating)) + "','movingSensor':'"+ String(distance) + "','doorSensor':'"+ String(doorSensorState) + "','windowSensor':'" + String(windowSensorState) + "','tempSensor':'" + String(Temp) + "','lightSensor':'" + String(lightSensorState) + "'}");
      delay(delayTime); 
    }

     Serial.println("{'lamp':'"+ String(digitalRead(lightsLivingRoom)) + "','heating':'"+ String(digitalRead(heating)) + "','movingSensor':'"+ String(distance) + "','doorSensor':'"+ String(doorSensorState) + "','windowSensor':'" + String(windowSensorState) + "','tempSensor':'" + String(Temp) + "','lightSensor':'" + String(lightSensorState) + "'}");

     delay(delayTime);
    
} 
