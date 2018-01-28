// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

//#include <DigiCDC.h>
#include <TinyWireM.h>
#include "TinyRTClib.h"
#include "FastLED.h"

// RTC Setup
RTC_DS1307 RTC;

// Setup Variables for time
int currentHoursTens = 0;
int currentHoursUnits = 0;
int currentMinutesTens = 0;
int currentMinutesUnits = 0;
int currentSecondsTens = 0;
int currentSecondsUnits = 0;

// FastLED setup
#define NUM_LEDS 9
#define DATA_PIN 4
CRGB leds[NUM_LEDS];

// Setup variables for LED drive in the HSV space
int currentH = 0;
int currentS = 255;
int currentV = 127;

// Debug LED on board
int LED_BUILTIN = 1;

void setup () {
  
  // LED_BUILTIN setup
  pinMode(LED_BUILTIN, OUTPUT);
  // SerialUSB Start
  // SerialUSB.begin();
  // Wire Start
  TinyWireM.begin();

  // RTC Start
  RTC.begin();
  // RTC run check
  if (! RTC.isrunning()) {
    // SerialUSB.println("RTC is NOT running!");
    digitalWrite(LED_BUILTIN, HIGH);
    }
  // Included for future use
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  // FastLED Setup 
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

}

void loop () {
  DateTime now = RTC.now();

  // Seperate time out into seperate Tens and Units for each
  currentHoursTens = (now.hour() / 10);
  currentHoursUnits = (now.hour() % 10);
  currentMinutesTens = (now.minute() / 10);
  currentMinutesUnits = (now.minute() % 10); 
  currentSecondsTens = (now.second() / 10);
  currentSecondsUnits = (now.second() % 10);
/*
  // Light all LED's
  displayNumber(9);
  delay(1000);
  displayBlank();
  delay(500);
*/
  // Display Hours
  displayNumber(currentHoursTens);
  delay(1000);
  displayBlank();
  delay(100);
  displayNumber(currentHoursUnits);
  delay(1000);
  displayBlank();
  delay(200);
  currentH = (currentH + 50);

  // Display Minutes
  displayNumber(currentMinutesTens);
  delay(1000);
  displayBlank();  
  delay(100);
  displayNumber(currentMinutesUnits);
  delay(1000);
  displayBlank();
  delay(200);
  currentH = (currentH + 50);
  
  // Display Seconds
  displayNumber(currentSecondsTens);
  delay(400);
  displayBlank();
  delay(100);
  displayNumber(currentSecondsUnits);
  delay(400);
  displayBlank();
  currentH = (currentH + 50);

  // Delay before redisplay
  digitalWrite(LED_BUILTIN, HIGH);
  delay(4000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
/*
  SerialUSB.print("Time from RTC:");
  SerialUSB.println();
  SerialUSB.print(now.year(), DEC);
  SerialUSB.print('/');
  SerialUSB.print(now.month(), DEC);
  SerialUSB.print('/');
  SerialUSB.print(now.day(), DEC);
  SerialUSB.print(' ');
  SerialUSB.print(now.hour(), DEC);
  SerialUSB.print(':');
  SerialUSB.print(now.minute(), DEC);
  SerialUSB.print(':');
  SerialUSB.print(now.second(), DEC);
  SerialUSB.println();
  
     // Dumb Serial Print- Time extracted from RTC seperate pieces- used for Debug
  SerialUSB.print("Extracted Time:");
  SerialUSB.println();
  SerialUSB.print(currentHoursTens, DEC);
  SerialUSB.print("_");
  SerialUSB.print(currentHoursUnits, DEC);
  SerialUSB.print(":");
  SerialUSB.print(currentMinutesTens, DEC);
  SerialUSB.print("_");
  SerialUSB.print(currentMinutesUnits, DEC);
  SerialUSB.print(":");
  SerialUSB.print(currentSecondsTens, DEC);
  SerialUSB.print("_");
  SerialUSB.print(currentSecondsUnits, DEC);
  SerialUSB.println();
  SerialUSB.println();
  SerialUSB.println();
  
  SerialUSB.delay(3000);
  */
  
}
  // Function that takes a number and lights that number of LED's, starting with 0
  // Improvements- Show at the exit of the loop, Variable for corner or zero LED
void displayNumber(int number){
  // Flashing LED in centre for zero
  
  if(number == 0) {
    leds[4] = CRGB::White;
    leds[4].fadeLightBy(250);
    FastLED.show();
  }

  // Displaying digit in LED's
  for(int thisLED = number; thisLED != 0; thisLED = thisLED - 1) {
    leds[thisLED - 1] = CHSV((currentH % 256), currentS, currentV);
    currentH++;
    FastLED.show();
    //delay(10);
  }
}

  // Function that clears down each LED sequentially to black
  // Improvements- show LEDs at the end of the loop
void displayBlank(){
  for(int thisLED = 0; thisLED < NUM_LEDS; thisLED = thisLED + 1) {
    leds[thisLED] = CRGB::Black;
    FastLED.show();
    //delay(100);    
  }
}
