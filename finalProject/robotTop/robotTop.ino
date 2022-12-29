
// Receiver Code that controls the top part of the robot


const int CEPIN = 9;
const int CSNPIN = 10;

// Additional libraries for receiver
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
//#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(CEPIN, CSNPIN);  // CE, CSN
#include <printf.h>  // for debugging


const byte addr = 0x73;
const byte xmtrAddress[] = { addr, addr, 0xC7, 0xE6, 0xCC };
const byte rcvrAddress[] = { addr, addr, 0xC7, 0xE6, 0x66 };

//  Legitimate channels are 0-125
const int RF24_CHANNEL_NUMBER = 40;
const int RF24_POWER_LEVEL = RF24_PA_LOW;


// global variables
uint8_t pipeNum;
unsigned int totalTransmitFailures = 0;
struct DataStruct {
  uint8_t selectorBits;
};

DataStruct data;


void setupRF24Common() {
  // RF24 setup
  if (!radio.begin()) {
    Serial.println(F("radio  initialization failed"));
    while (1)
      ;
  } else {
    Serial.println(F("radio successfully initialized"));
  }
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(RF24_CHANNEL_NUMBER);
  radio.setPALevel(RF24_POWER_LEVEL);
}


void rf24SendData() {
  // The write() function will block
  // until the message is successfully acknowledged by the receiver
  // or the timeout/retransmit maxima are reached.
  int retval = radio.write(&data, sizeof(data));
  Serial.print(F("Sending data = "));
  Serial.print(data.selectorBits);
  Serial.print(F(" ... "));
  if (retval) {
    Serial.println(F("success"));
  } else {
    totalTransmitFailures++;
    Serial.print(F("failure, total failures = "));
    Serial.println(totalTransmitFailures);
  }
}


// Additional pin usage for receiver


// Servo motors
const int SERVO0PIN = A3;
const int SERVO1PIN = A4;


// Neopixel
#define NEOPIXELPIN A1
#define NUMPIXELS 256  // change to fit
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);


uint8_t starEyesDown[] = {15, 22, 23, 29, 30, 31, 38, 39, 47, 64, 72, 73, 80, 81, 82, 88, 89, 90, 91, 96, 97, 98, 104, 105, 112,
                          135, 142, 143, 149, 150, 151, 156, 157, 158, 159, 165, 166, 167, 174, 175, 183, 200, 208, 209,
                          216, 217, 218, 224, 225, 232
                         };

uint8_t starEyesUp[] = {67, 74, 75, 76, 81, 82, 83, 84, 85, 88, 89, 90, 91, 92, 93, 94, 97, 98, 99, 100, 101, 106, 107, 108, 115, 132, 139, 140, 141, 146, 147, 148, 149, 150,
                        153, 154, 155, 156, 157, 158, 159, 162, 163, 164, 165, 166, 171, 172, 173, 180, 188,

                       };


// <162 pixels being used

Servo servo0;  // left ear
Servo servo1;  // right ear


// change as per your robot
const int SERVO0NEUTRALPOSITION = 45;
const int SERVO1NEUTRALPOSITION = 90;
const int SERVO2NEUTRALPOSITION = 0;
const int SERVO3NEUTRALPOSITION = 180;
const int SERVO4NEUTRALPOSITION = 180;

void setup() {
  Serial.begin(9600);
  printf_begin();

  // Set up all the attached hardware
  setupServoMotors();
  setupNeoPixels();
  setupRF24();




}

void setupRF24() {
  setupRF24Common();

  // Set us as a receiver
  radio.openWritingPipe(rcvrAddress);
  radio.openReadingPipe(1, xmtrAddress);

  radio.printPrettyDetails();
  Serial.println(F("I am a receiver"));
}



void setupServoMotors() {
  servo0.attach(SERVO0PIN);
  servo1.attach(SERVO1PIN);

  servo0.write(SERVO0NEUTRALPOSITION);
  servo1.write(SERVO1NEUTRALPOSITION);

}



int pos = 0;

void loop() {
  // If there is data, read it,
  // and do the needfull
  // Become a receiver


  radio.startListening();
  if (radio.available(&pipeNum)) {
    radio.read(&data, sizeof(data));
    Serial.print(F("message received Data = "));
    Serial.println(data.selectorBits);

    switch (data.selectorBits) {
      case 0b00000000:
        break;
      case 0b00000001:

        break;
      case 0b00000010:

        break;


      case 0b00000110:
        break;
      case 0b00000111:
        break;
      case 0b00001000:
        break;
      case 0b00001001:


        //talking ear turn
        for (pos = 0; pos <= 180; pos += 1) {

          servo0.write(pos);
          servo1.write(pos);
          delay(10);

        }
        for (pos = 180; pos >= 60; pos -= 1) {
          servo0.write(pos);
          servo1.write(pos);
          delay(10);

        }

        for (int i : starEyesUp) { // For each pixel...

          pixels.setPixelColor(i, pixels.Color(random(50, 157), random(50, 60), random(50, 255)));

          pixels.show();
        }


        for (int i : starEyesUp) { // For each pixel...

          pixels.setPixelColor(i, pixels.Color(random(50, 255), random(50, 255), random(50, 255)));

          pixels.show();
        }

        break;
      case 0b00001010:
        break;
      case 0b00001011:
        break;
      case 0b00001100:
        break;
      case 0b00001101:

        //excited ear turn

        for (pos = 0; pos <= 180; pos += 1) {

          servo0.write(pos);
          servo1.write(pos);
          delay(5);

        }

        for (pos = 180; pos >= 60; pos -= 1) {
          servo0.write(pos);
          servo1.write(pos);
          delay(5);
        }


        pixels.clear();

        for (int i : starEyesDown) { // For each pixel...

          pixels.setPixelColor(i, pixels.Color(random(0, 255), random(0, 255), random(0, 255)));

          pixels.show();
          delay(10);
        }

        pixels.clear();

        for (int i : starEyesUp) { // For each pixel...

          pixels.setPixelColor(i, pixels.Color(random(20, 157), random(20, 200), random(20, 255)));
          // pixels.setPixelColor(i, pixels.Color(255, 0, 0));
          pixels.show();
          delay(10);
        }

        setupNeoPixels();
        break;
      case 0b00001110:

        break;
      case 0b00001111:

        // talking/excited eyes

        pixels.clear();

        for (int i : starEyesDown) { // For each pixel...

          pixels.setPixelColor(i, pixels.Color(random(20, 200), random(20, 255), random(20, 255)));

          pixels.show();
          delay(10);
        }

        pixels.clear();

        for (int i : starEyesUp) { // For each pixel...

          pixels.setPixelColor(i, pixels.Color(random(20, 157), random(20, 200), random(20, 255)));
          // pixels.setPixelColor(i, pixels.Color(255, 0, 0));
          pixels.show();
          delay(10);
        }

        setupNeoPixels();

        break;
      default:
        Serial.println(F("Invalid option"));
    } // end of switch
  } // end of if radio.available
}  // end of loop()

// end of receiver code
