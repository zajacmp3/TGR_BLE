// BLE Board controls
const int ledBLE = 13;

// Auxillary equipment setup
const int stepPin = 3;
const int dirPin = 4;
const int buttonPin = 2;
const int enablePin = 5;
int buttonState, timePressed, startTime = 0;

void setup() {
  Serial.begin(115200);  //initial the Serial
  start();
  pinMode(ledBLE, OUTPUT);
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    if(startTime == 0) {
      startTime = millis();  
    } else {
      timePressed = millis() - startTime;
    }
  } else {
    startTime = 0;
    timePressed = 0;
  }
  if(timePressed > 1000 && timePressed % 1000 == 0) {
    Serial.println(timePressed / 1000);
  }

  if (Serial.available())  {
    String command = Serial.readStringUntil('\n');
    if (command.indexOf("rotate") == 0) {
      digitalWrite(enablePin,LOW);
      delayMicroseconds(500);
      digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
     
      // Makes 200 pulses for making one full cycle rotation
      for(int x = 0; x < 200; x++) {
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(500);
      }
      Serial.println("Rotated");//send what has been received
      digitalWrite(enablePin,HIGH);
    } else {
      Serial.println("Command not recognized");
    }
    Serial.write(command.c_str());//send what has been received
    Serial.println();   //print line feed character
  }
}

void start() {
  delay(10);
  digitalWrite(enablePin,HIGH);
  Serial.write("Initiated");
  Serial.println();
}
