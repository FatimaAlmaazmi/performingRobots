/*
 *  In this code I have added how I want the neopixels and servos to work
 * 
 */



#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


#define NEOPIN        A1 
#define SERVOPIN      A3 
#define SERVO2PIN     A4 

#define NUMPIXELS 256 

// servo motor variables
Servo myservo;
Servo myservo2;

int pos = 0; 

//neopixels variables
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

// Servo declare

    myservo.attach(SERVOPIN);
    myservo2.attach(SERVO2PIN);

  
// Neopixel standard eye color
    pixels.begin();
    pixels.setBrightness(40);
    for(int i=0; i<NUMPIXELS; i++) { 

    pixels.setPixelColor(i, pixels.Color(random(0, 255), random(0, 255), random(0, 255)));

    pixels.show();
   }
}

void loop() {

// Servo code
  for (pos = 0; pos <= 180; pos += 1) { 
    
    myservo.write(pos);  
     myservo2.write(pos);  
    delay(15);                       
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);  
    myservo2.write(pos);
    delay(15);                       
  }
  

// Neopixels code (when button is pushed)
 for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(random(0, 157), random(0, 60), random(0, 255)));

    pixels.show(); 

  }

   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(random(0, 255), random(0, 255), random(0, 255)));
    
    pixels.show(); 


  }
}
