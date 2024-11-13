/**
 * Project      graduation-cap-leds
 * @file        micro_LED.ino
 * @author      Sean Duffie
 * @link        https://github.com/SeanDuffie/graduation-cap-leds
 * 
 * The purpose of this project is to create a 
 */

#include "FastLED.h"
#include "Sequence.h"
#include "led.h"
#include "16.h"
// TODO: Add a conditional include for pixel array file

#define DEBUG false

// Which pin on the Arduino is connected to the LEDs?
#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4
#define BUTTON4 5
#define LED_DATA_PIN 6
#define COLOR_ORDER GRB
#define CHIPSET WS2812B

// LED brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50

// Amount of time for each half-blink, in milliseconds
#define BLINK_TIME 25
uint8_t MULTIPLIER = 5;

// How many LEDs are attached to the Arduino?
#define WIDTH 16
#define LENGTH 16
#define NUM_LEDS (WIDTH * LENGTH)
// const uint8_t LAST_VISIBLE_LED = NUM_LEDS-1;
#include "WIDTH.h"

CRGB leds_plus_safety_pixel[NUM_LEDS];
CRGB* const leds( leds_plus_safety_pixel );

long bird[][NUM_LEDS] = {Bird0, Bird1, Bird2, Bird3, Bird4};
long pingu[] = {Pingu0, Pingu1, Pingu2, Pingu1, Pingu2, Pingu1, Pingu3, Pingu4};
const long pop_cat[] = {Pop0, Pop1};
const long rroll[] = {rr0, rr1};

int num_sets = 4;
int num_img[] = {5, 8, 2, 2};
int state = 0;

bool Paused = false;

void setup() {
    /** Start Serial Terminal for debugging */
    #ifdef DEBUG
    Serial.begin(9600);
    #endif
    
    /** Set up the LED Matrix */
    FastLED.addLeds<CHIPSET, LED_DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();

    /** Set up the button inputs */
    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);
    pinMode(BUTTON3, INPUT);
    pinMode(BUTTON4, INPUT);

    /** Flash RGB to debug LEDs */
    #ifdef DEBUG
    StartFlash();
    #endif
}

void loop() {
    #ifdef DEBUG
    Serial.println("Loop started!");
    #endif
    int c = 0;

    while (c < num_img[state]) {
        /** Draw the current frame
         *   
         *  state - determines the image set
         *  c - determines the frame in the current set 
         */
        switch(state) {
            case 0:
                DrawOneFrame(bird[c]);
                break;
            case 1:
                DrawOneFrame(pingu[c]);
                break;
            case 2:
                DrawOneFrame(pop_cat[c]);
                break;
            case 3:
                DrawOneFrame(rroll[c]);
                break;
        }
        
        /** Split the delay into batches to reduce button lag */
        for (int i=0; i < MULTIPLIER; i++) {
            /** Button 1 is pressed
             *  
             *  If Not Paused, this will SPEED up the framerate
             *  If Paused, this will move FORWARD one frame
             */
            if (digitalRead(BUTTON1)) {
                if (Paused) {
                    c++;
                    delay(BLINK_TIME*10);
                    break;
                } else {
                    if (MULTIPLIER > 1) { MULTIPLIER -= 1; }
                }
            }
            /** Button 2 is pressed
             *  
             *  If Not Paused, this will SLOW down the framerate
             *  If Paused, this will move BACKWARD one frame
             */
            if (digitalRead(BUTTON2)) {
                if (Paused) {
                    if (c <= 0) {
                        c = num_img[state]-1;
                    } else {
                        c--;
                    }
                    delay(BLINK_TIME*10);
                    break;
                } else {
                    if (MULTIPLIER < 255) { MULTIPLIER += 1; }
                }
            }
            /** Toggle Pause/play if Button 3 is pressed */
            if (digitalRead(BUTTON3)) {
                Paused = !Paused;
                delay(BLINK_TIME*10);
            }
            /** Cycle State if Button 4 is pressed */
            if (digitalRead(BUTTON4)) {
                if (state >= num_sets-1) {
                    state = 0;
                } else {
                    state++;
                }
                c = 0;
                delay(BLINK_TIME*10);
                break;
            }
            /** Delay only BLINK_TIME per MULTIPLIER cycle */
            delay(BLINK_TIME);
            /** Add some extra delay for specific frames */
            if (state == 1) {
                if (c >= 6) { delay(BLINK_TIME*10); }
                if (c >= 7) { delay(BLINK_TIME*10); }
            } else if (state == 3) {
                delay(BLINK_TIME);
            }
        }
        
        /** Paused - a boolean that decided whether or not to move to the next frame */
        if (!Paused) { c++; }
    }
}

void StartFlash() {
   for (int i=0; i<NUM_LEDS; i++) {
       leds[i] = 0xff0000;
   }
   FastLED.show();
   delay(BLINK_TIME*20);

   for (int i=0; i<NUM_LEDS; i++) {
       leds[i] = 0x00ff00;
   }
   FastLED.show();
   delay(BLINK_TIME*20);

   for (int i=0; i<NUM_LEDS; i++) {
       leds[i] = 0x0000ff;
   }
   FastLED.show();
   delay(BLINK_TIME*20);

   for (int i=0; i<NUM_LEDS; i++) {
       leds[i] = 0x000000;
   }
   FastLED.show();
}

void DrawOneFrame(long pixel_arr[])
{
    for(byte y=0; y<LENGTH; y++) {
        for(byte x=0; x<WIDTH; x++) {
            leds[XY(x,y)] = pixel_arr[(y * WIDTH) + x];
        }
    }
    FastLED.show();
}
