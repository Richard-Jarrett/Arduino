// Richard Jarrett 04/01/2018
// Initial Version 1.0

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
// Wire Library 1.0.0
#include <Wire.h>
// RCTLib Library 1.2.0
#include "RTClib.h"
// FastLED Library 3.1.6
#include "FastLED.h"

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

// FastLED setup
#define NUM_LEDS 16
#define DATA_PIN 3
CRGB leds[NUM_LEDS];

// Setup Variables for time
int currentHoursTens = 0;
int currentHoursUnits = 0;
int currentMinutesTens = 0;
int currentMinutesUnits = 0;
int currentSecondsTens = 0;
int currentSecondsUnits = 0;

// Setup variables for LED drive in the HSV space
int currentH = 0;
int currentS = 255;
int currentV = 127;

// RTC Setup
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {

  // FastLED Setup
  delay(2000);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  
  #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
  #endif

  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
  // Get time from RTC
  DateTime now = rtc.now();

  // Seperate time out into seperate Tens and Units for each
  currentHoursTens = (now.hour() / 10);
  currentHoursUnits = (now.hour() % 10);
  currentMinutesTens = (now.minute() / 10);
  currentMinutesUnits = (now.minute() % 10); 
  currentSecondsTens = (now.second() / 10);
  currentSecondsUnits = (now.second() % 10);

  // Dumb Serial Print- Time from RTC
  Serial.print("Clock Time:");
  Serial.println();
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.println();
  Serial.println();

  // Dumb Serial Print- Time extracted from RTC seperate pieces- used for Debug
  Serial.print("Extracted Time:");
  Serial.println();
  Serial.print(currentHoursTens, DEC);
  Serial.print("_");
  Serial.print(currentHoursUnits, DEC);
  Serial.print(":");
  Serial.print(currentMinutesTens, DEC);
  Serial.print("_");
  Serial.print(currentMinutesUnits, DEC);
  Serial.print(":");
  Serial.print(currentSecondsTens, DEC);
  Serial.print("_");
  Serial.print(currentSecondsUnits, DEC);
  Serial.println();
  Serial.println();
  Serial.println();

  // Light up all LED's. Previous version of indexing
  //displayNumber(24);
  //delay(500);
  //displayBlank();
  //delay(500);

  // Flash all the corners of the strip- indexing
  //leds[0] = CRGB::White;
  //leds[3] = CRGB::White;
  //leds[12] = CRGB::White;
  //leds[15] = CRGB::White;

  // Dim the LED's so they are less bright
  //leds[0].fadeLightBy(192);
  //leds[3].fadeLightBy(192);
  //leds[12].fadeLightBy(192);
  //leds[15].fadeLightBy(192);

  // Update the display
  FastLED.show();
  delay(500);

  // Clear the display
  displayBlank();
  delay(500);

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
  
  
  delay(4000);
  
  /*
  // Print some stuff on Serial- Date etc
  Serial.print(now.year(), DEC);
  Serial.print('/');  
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  // Print some more stuff on Serial- Unix time
  Serial.print(" since midnight 1/1/1970 = ");
  Serial.print(now.unixtime());
  Serial.print("s = ");
  Serial.print(now.unixtime() / 86400L);
  Serial.println("d");
  */
  
  /*
  // Future Date Calc
  // calculate a date which is 7 days and 30 seconds into the future
  DateTime future (now + TimeSpan(7,12,30,6));
  
  Serial.print(" now + 7d + 30s: ");
  Serial.print(future.year(), DEC);
  Serial.print('/');
  Serial.print(future.month(), DEC);
  Serial.print('/');
  Serial.print(future.day(), DEC);
  Serial.print(' ');
  Serial.print(future.hour(), DEC);
  Serial.print(':');
  Serial.print(future.minute(), DEC);
  Serial.print(':');
  Serial.print(future.second(), DEC);
  Serial.println();
  
  Serial.println();
  */
}

  // Function that takes a number and lights that number of LED's, starting with 0
  // Improvements- Show at the exit of the loop, Variable for corner or zero LED
void displayNumber(int number){
  // Flashing LED in corner at same time as any digit
  leds[12] = CRGB::White;
  leds[12].fadeLightBy(250);
  FastLED.show();
  for(int thisLED = number; thisLED != 0; thisLED = thisLED -1) {
    leds[thisLED - 1] = CHSV((currentH % 256), currentS, currentV);
    currentH++;
    FastLED.show();
    //delay(10);
  }
}

  // Function that clears down each LED sequentially to black
  // Improvements- show LEDs at the end of the loop
void displayBlank(){
  for(int thisLED = 0; thisLED < NUM_LEDS; thisLED = thisLED +1) {
    leds[thisLED] = CRGB::Black;
    FastLED.show();
    //delay(100);    
  }
}
