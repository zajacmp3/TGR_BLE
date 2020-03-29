// BLE Board controls
const int ledBLE = 13;

// Auxillary equipment setup
const int stepPin = 3;
const int dirPin = 4;
const int buttonPin1 = 2;
const int buttonPin2 = A1;
const int enablePin = 5;
int buttonState1, buttonState2;

void setup() {
  Serial.begin(115200);  //initial the Serial
  start();
  pinMode(ledBLE, OUTPUT);
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
}

void loop() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  
  if (Serial.available())  {
    String command = Serial.readStringUntil('\n');
    if (command.indexOf("rotate") == 0) {
      digitalWrite(enablePin,LOW);
      delayMicroseconds(500);
      digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction

      // Makes 200 pulses for making one full cycle rotation
      for(int x = 0; x < 200; x++) {
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(10000);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(10000);
      }
      Serial.println("Rotated");//send what has been received
      digitalWrite(enablePin,HIGH);
    } else if (command.indexOf("status") == 0) {
      if(buttonState1 == HIGH) {
        Serial.println("1");
      }
      else if(buttonState2 == HIGH) {
        Serial.println("2");
      }
      else {
        Serial.println("0");
      }
    }
    else {
      Serial.println("X");
    }
  }
}

void start() {
  delay(10);
  digitalWrite(enablePin,HIGH);
  Serial.write("Initiated");
  Serial.println();
}
