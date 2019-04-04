/**
 *
 *****************************************************************
 * IOT Challenges - https://instagram.com/iotchallenges          *
 *****************************************************************
 * Evandro Fruhauf                                               *
 *  GitHub - https://github.com/evandrodp                        *
 *  LinkedIn - http://linkedin.com/in/evandrofruhauf             *
 *****************************************************************
 * This code can contain parts from other open-sources projects, *
 * whenever possible it will be quoted.                          *
 *****************************************************************
 *
 * Led Matrix 8x8
 *
 * Challenge: Write IOT CHALLENGES and show emojis
 *
 * Source base: Nerd First https://www.youtube.com/watch?v=NM7wXta8crM
 * Matrix Generator: https://xantorohara.github.io/led-matrix-editor
 *
 * This Letters:
 * https://xantorohara.github.io/led-matrix-editor/#3c18181818183c00|3c66666666663c00|18181818185a7e00|3c66060606663c00|6666667e66666600|6666667e66663c00|7e06060606060600|7e06060606060600|7e06063e06067e00|c6c6e6f6decec600|3c66760606663c00|7e06063e06067e00|3c66603c06663c00|0000000000000000|3c4299a581a5423c|0000000000000000|003c428100666600|0000000000000000|0018240272645800
 *
**/
#include <Arduino.h>

// Define the Registers codes
#define DATA 2
#define SHIFT 3
#define STORE 4

// Functions will be used on the Matrix
void store();
void displayImage(const byte* image);

// Variables to define the images and the time
byte image[8];
int imageIdx = 0;
long lastTime = 0;
long timeDelay = 500;

// Collection of images
const byte IMAGES[][8] PROGMEM = {
  {B00000000, B00111100, B00011000, B00011000, B00011000, B00011000, B00011000, B00111100}, // I
  {B00000000, B00111100, B01100110, B01100110, B01100110, B01100110, B01100110, B00111100}, // O
  {B00000000, B01111110, B01011010, B00011000, B00011000, B00011000, B00011000, B00011000}, // T
  {B00000000, B00111100, B01100110, B01100000, B01100000, B01100000, B01100110, B00111100}, // C
  {B00000000, B01100110, B01100110, B01100110, B01111110, B01100110, B01100110, B01100110}, // H
  {B00000000, B00111100, B01100110, B01100110, B01111110, B01100110, B01100110, B01100110}, // A
  {B00000000, B01100000, B01100000, B01100000, B01100000, B01100000, B01100000, B01111110}, // L
  {B00000000, B01100000, B01100000, B01100000, B01100000, B01100000, B01100000, B01111110}, // L
  {B00000000, B01111110, B01100000, B01100000, B01111100, B01100000, B01100000, B01111110}, // E
  {B00000000, B01100011, B01110011, B01111011, B01101111, B01100111, B01100011, B01100011}, // N
  {B00000000, B00111100, B01100110, B01100000, B01100000, B01101110, B01100110, B00111100}, // G
  {B00000000, B01111110, B01100000, B01100000, B01111100, B01100000, B01100000, B01111110}, // E
  {B00000000, B00111100, B01100110, B01100000, B00111100, B00000110, B01100110, B00111100}, // S
  {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, //
  {B00111100, B01000010, B10100101, B10000001, B10100101, B10011001, B01000010, B00111100}, // :)
  {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, //
  {B00000000, B01100110, B01100110, B00000000, B10000001, B01000010, B00111100, B00000000}, // :)
  {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, //
  {B00000000, B00011010, B00100110, B01001110, B01000000, B00100100, B00011000, B00000000}, // >
  {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}  //
};
const int IMAGES_LEN = sizeof(IMAGES)/8;


void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(SHIFT, OUTPUT);
  pinMode(STORE, OUTPUT);
  memcpy_P(image, &IMAGES[imageIdx], 8);
}

void loop() {
  displayImage(image);
  if ( (millis() - lastTime) > timeDelay) {
    if (++imageIdx >= IMAGES_LEN ) {
      imageIdx = 0;
    }
    memcpy_P(image, &IMAGES[imageIdx], 8);
    lastTime = millis();
  }
}

void store() {
  digitalWrite(STORE, HIGH);
  delayMicroseconds(10);
  digitalWrite(STORE, LOW);
  delayMicroseconds(10);
}

void displayImage(const byte* image) {
  for (int i = 0; i < 8; i++) {
    shiftOut(DATA, SHIFT, LSBFIRST, ~image[i]);
    shiftOut(DATA, SHIFT, LSBFIRST, 128 >> i);
    store();
  }
}