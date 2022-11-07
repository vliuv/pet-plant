#include "Servo.h" // include the servo library
Servo servoMotor; // creates an instance of the servo object to control a servo
int servoPin = 9; // control pin for servo motor

#include "pitches.h"

int melody[] = {
  NOTE_G4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_D4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4
};

// note durations: 2 = half note, 4 = quarter note, 8 = eighth note
int noteDurations[] = {4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 8, 8, 4, 4, 4, 8, 8, 8, 8, 8, 8, 2, 4, 4, 4, 4, 4, 4, 2};

int ledPin1 = 10;
int ledPin2 = 4;
int ledPin3 = 3;
int ledPin4 = 16;
int ledPin5 = 17;
int buttonPin = 2;
int photoPin = A7;
int forcePin = A6;
int button = 0;
int photo = 0;
int force = 0;

void setup() {
  // put your setup code here, to run once:
  servoMotor.attach(servoPin); // attaches the servo on pin 3 to the servo object
}

void loop() {
  // put your main code here, to run repeatedly:
  button = digitalRead(buttonPin);
  photo = analogRead(photoPin);
  force = analogRead(forcePin);

  int brightness = map(photo, 950, 470, 0, 255); //map value from the sensor to the value sent to the LED
  analogWrite(ledPin1, brightness); //send mapped value to LED
  analogWrite(ledPin2, brightness);
  analogWrite(ledPin3, brightness);
  analogWrite(ledPin4, brightness);
  analogWrite(ledPin5, brightness);

  if (force > 600) {
    servoMotor.write(120);
    delay(700);
    servoMotor.write(0);
    delay(700);
    servoMotor.write(90);
    delay(500);
    servoMotor.write(30);
    delay(500);
    servoMotor.write(90);
    delay(500);
    servoMotor.write(30);
    delay(500);
    servoMotor.write(120);
    delay(700);
    servoMotor.write(0);
    delay(700);
  } else {
    servoMotor.write(0);
  }

  // play the notes of the melody
  for (int thisNote = 0; thisNote < 32; thisNote++) {
    // to calculating the note duration, (1s/note type)
    int noteDuration = 1000 / noteDurations[thisNote];
    if (button == HIGH) {
      tone(8, melody[thisNote], noteDuration);

      //pause for the note's duration plus 30 ms
      delay(noteDuration + 30);
    }
  }

  Serial.print(button);
  Serial.print("\t");
  Serial.print(photo);
  Serial.print("\t");
  Serial.print(force);
  Serial.print("\t");
  Serial.print(brightness);
  Serial.println();
}
