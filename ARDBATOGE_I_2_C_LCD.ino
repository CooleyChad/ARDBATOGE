//Alex Cooley
//12/02/2023
//Arduino Nano R3                            
//Mark 1 Arduino Based Tone Generator
//ARDBATOGE Mark 1

#include <Wire.h> //I2C Library
#include <LiquidCrystal_I2C.h> //LCD I2C Library

LiquidCrystal_I2C lcd (0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display


const int FreqIN = A1; //Frequency Control

const int Output= 11; //Test Output Pin
const int LED = 9; //LED Debug

int MaxFreq=5000;

int ToneOut;
int analogOut;
int AmpOut;

float ADCVal=00.00;
float LEDVal=00.00;

#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {

  pinMode(FreqIN, INPUT); //Frequency Control Input

  pinMode(Output, OUTPUT); //Tone Output
  pinMode(LED, OUTPUT); //Debugging LED

  lcd.init();
  lcd.init();                   
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(6,1);
  lcd.print("Welcome");
  delay(2500);

  lcd.clear();
  lcd.backlight();
  lcd.setCursor(5,1);
  lcd.print("ARDBATOGE");
  lcd.setCursor(4,2);
  lcd.print("Version 1.0");
  delay(2500);

  lcd.clear();
  lcd.backlight();
  lcd.setCursor(6,0);
  lcd.print("Designed");
  lcd.setCursor(9,1);
  lcd.print("By");
  lcd.setCursor(6,2);
  lcd.print("Alexander");
  lcd.setCursor(7,3);
  lcd.print("Cooley");
  delay(2500);

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(Output, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(Output);
  }
}

void loop() {
  // no need to repeat the melody.
  float ADC1 = 0000.0; //Frequency Control Input
  ADC1=analogRead(FreqIN);

  ToneOut=map(ADC1, 0, 1023, 0, MaxFreq);

  analogOut=map(ADC1, 0, 1023, 0, 255);

  AmpOut=map(ADC1, 0, 1023, 0, 5000);

  LEDVal=map(ADC1, 0, 1023, 0, 5.00);

  ADCVal=map(ADC1, 0, 1023, 0, 100);




  tone(Output, ToneOut);

  analogWrite(LED, analogOut);
  delay(100);

  static unsigned long Stat = millis();{

  if (millis() - Stat > 1000){

   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("FREQ:");
   lcd.setCursor(6,0);
   lcd.print(ToneOut);
   lcd.setCursor(13,0);
   lcd.print("Hz");
   lcd.setCursor(0,1);
   lcd.print("ADC:");
   lcd.setCursor(6,1);
   lcd.print(AmpOut);
   lcd.setCursor(13,1);
   lcd.print("mV");
   lcd.setCursor(0,2);
   lcd.print("LED:");
   lcd.setCursor(6,2);
   lcd.print(LEDVal);
   lcd.setCursor(13,2);
   lcd.print("V");
   lcd.setCursor(0,3);
   lcd.print("IN:");
   lcd.setCursor(6,3);
   lcd.print(ADCVal);
   lcd.setCursor(13,3);
   lcd.print("%");


   Stat = millis();


}
  }
    }
