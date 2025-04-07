#ifndef _IHM_LIB
#define _IHM_LIB

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
// #include <U8g2lib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SDA_OLED_PIN 21 //Data
#define SCL_OLED_PIN 22 //Clock

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define OLED_PIN_RESET 23

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO


void initIHM();
void printMidOLED(String text, int textSize, int y);
void printMidOLED(String text);
void displayLogo();

#endif // _IHM_LIB