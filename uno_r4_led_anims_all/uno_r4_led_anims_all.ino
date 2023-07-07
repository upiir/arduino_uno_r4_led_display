// simple project using Arduino UNO R4 WIFI to display animations on the built-in LED matrix display 
// created by upir, 2023
// youtube channel: https://www.youtube.com/upir_upir

// YOUTUBE VIDEO: https://youtu.be/Qpi0Y5bcvlQ

// links from the video:
// Arduino UNO R4 WIFI: https://store.arduino.cc/products/uno-r4-wifi
// LED Badges video: https://youtu.be/MRTxTx8bgYg
// Piskel Application: https://www.piskelapp.com/p/create/sprite


// Related videos:
// Arduino OLED Clock Project - https://youtu.be/srgsBWHSNSQ
// Arduino Parking Sensor - https://youtu.be/sEWw087KOj0
// Turbo pressure gauge with Arduino and OLED display - https://youtu.be/JXmw1xOlBdk
// Arduino Car Cluster with OLED Display - https://youtu.be/El5SJelwV_0
// Knob over OLED Display - https://youtu.be/SmbcNx7tbX8
// Arduino + OLED = 3D ? - https://youtu.be/kBAcaA7NAlA
// Arduino OLED Gauge - https://youtu.be/xI6dXTA02UQ
// Smaller & Faster Arduino - https://youtu.be/4GfPQoIRqW8


#include "Arduino_LED_Matrix.h" // needed to access the LED matrix display

#include "r4_anim_arduino_logo.h"
#include "r4_anim_arrows.h"
#include "r4_anim_battery.h"
#include "r4_anim_checkbox.h"
#include "r4_anim_error2.h"
#include "r4_anim_load.h"
#include "r4_anim_lock.h"
#include "r4_anim_signal.h"
#include "r4_anim_sound.h"
#include "r4_anim_talk.h"

ArduinoLEDMatrix matrix;

byte frame[8][12] = { // this variable will be reused to show the content on the display
  { 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};


int frame_current = 0; // current frame to be displayed
int frame_max = 27; // maximum number of frames
int frame_fps = 20; // delay for each individual animation frame (same for all the frames inside one animation)
int animation_current = 0; // currently played animation
int animation_counter = 0; // counter to switch between animation after some time 

void setup() {
  // put your setup code here, to run once:
  matrix.begin(); // initialize the LED array display
}

void loop() {

  // switch between animations
  animation_counter++;
  if (animation_counter > (7 * frame_fps)) {
    animation_counter = 0;
    animation_current++;
    if (animation_current >= 10) {
      animation_current = 0;
    }

    // set the FPS value and maximum number of frames based on the active animation
    switch (animation_current) {
    case 0: // r4_anim_arduino_logo.h
      frame_fps = 15;
      frame_max = R4_ANIM_ARDUINO_LOGO_FRAME_COUNT;
      break;
    case 1: // r4_anim_arrows.h
      frame_fps = 12;
      frame_max = R4_ANIM_ARROWS_FRAME_COUNT;
      break;
    case 2: // r4_anim_load.h
      frame_fps = 12;
      frame_max = R4_ANIM_LOAD_FRAME_COUNT;
      break;      
    case 3: // r4_anim_battery.h
      frame_fps = 5;
      frame_max = R4_ANIM_BATTERY_FRAME_COUNT;
      break;      
    case 4: // r4_anim_signal.h
      frame_fps = 4;
      frame_max = R4_ANIM_SIGNAL_FRAME_COUNT;
      break;      
    case 5: // r4_anim_sound.h
      frame_fps = 2;
      frame_max = R4_ANIM_SOUND_FRAME_COUNT;
      break;      
    case 6: // r4_anim_error2.h
      frame_fps = 15;
      frame_max = R4_ANIM_ERROR2_FRAME_COUNT;
      break;      
    case 7: // r4_anim_lock.h
      frame_fps = 1;
      frame_max = R4_ANIM_LOCK_FRAME_COUNT;
      break;      
    case 8: // r4_anim_checkbox.h
      frame_fps = 12;
      frame_max = R4_ANIM_CHECKBOX_FRAME_COUNT;
      break;      
    case 9: // r4_anim_talk.h
      frame_fps = 12;
      frame_max = R4_ANIM_TALK_FRAME_COUNT;
      break;                                                
    default:
      break;
    }
  }


  frame_current++; // increase the current frame
  if (frame_current >= frame_max) { // if the current frame is bigger than the max frame
    frame_current = 0; // reset the current frame back to 0
  }

  // populate pixels with values from the piskel animation
  for (int x=0; x<12; x++) {
    for (int y=0; y<8; y++) {
      int index = (y * 12) + x;
      
      
      // populate pixels in the "frame" variable based on the active animation
      switch (animation_current) {
      case 0: // r4_anim_arduino_logo.h
        frame[y][x] = r4_anim_arduino_logo_data[frame_current][index];
        break;
      case 1: // r4_anim_arrows.h
        frame[y][x] = r4_anim_arrows_data[frame_current][index];
        break;
      case 2: // r4_anim_load.h
        frame[y][x] = r4_anim_load_data[frame_current][index];
        break;      
      case 3: // r4_anim_battery.h
        frame[y][x] = r4_anim_battery_data[frame_current][index];
        break;      
      case 4: // r4_anim_signal.h
        frame[y][x] = r4_anim_signal_data[frame_current][index];
        break;      
      case 5: // r4_anim_sound.h
        frame[y][x] = r4_anim_sound_data[frame_current][index];
        break;      
      case 6: // r4_anim_error2.h
        frame[y][x] = r4_anim_error2_data[frame_current][index];
        break;      
      case 7: // r4_anim_lock.h
        frame[y][x] = r4_anim_lock_data[frame_current][index];
        break;      
      case 8: // r4_anim_checkbox.h
        frame[y][x] = r4_anim_checkbox_data[frame_current][index];
        break;      
      case 9: // r4_anim_talk.h
        frame[y][x] = r4_anim_talk_data[frame_current][index];
        break;                                                
      default:
        break;
      }

    } 
  }
  
  matrix.renderBitmap(frame, 8, 12); // show the content of the array "frame" on the LED array display
  delay(1000 / frame_fps); // X FPS
}



