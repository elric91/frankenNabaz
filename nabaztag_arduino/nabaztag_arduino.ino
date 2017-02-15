#include "LedControlMS.h"
#include "earz.cpp"

// LED MATRIX
#define LMATRIX_DIN 12
#define LMATRIX_CLK 11
#define LMATRIX_CS 10
#define LMATRIX_NBR 1
#define LMATRIX_DELAY 10
// EARS MOVEMENT
#define REAR_PINA 9
#define REAR_PINB 8
#define LEAR_PINA 7
#define LEAR_PINB 6
// EARS POSITION
#define REAR_POS A0
#define LEAR_POS A1
// PHYSICAL COMMANDS
#define HEAD_BTN A2
#define SCROLL_BTN A3



LedControl lc = LedControl(LMATRIX_DIN,LMATRIX_CLK,LMATRIX_CS, LMATRIX_NBR);
earz rear(REAR_PINA, REAR_PINB, REAR_POS)

void setup(){
  Serial.begin(57600);
  // init cled matrix
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  // init ears
  pinMode(REAR_PINA, OUTPUT);
  pinMode(REAR_PINB, OUTPUT);
  pinMode(LEAR_PINA, OUTPUT);
  pinMode(LEAR_PINB, OUTPUT);
  pinMode(REAR_POS, INPUT);
  pinMode(LEAR_POS, INPUT);
  pinMode(HEAD_BTN, INPUT);
  pinMode(SCROLL_BTN, INPUT);
  initEars();
}

void loop(){
/*  forward();
  delay(1000);
  reverse();
  delay(1000);
  softStop();
  delay(1000);*/
}


  
//  lc.clearDisplay(0);
//  lc.displayChar(0,1);
//  lc.clearDisplay(0);
//  lc.setColumn(0,3,0xff);


