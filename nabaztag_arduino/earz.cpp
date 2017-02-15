#include <Arduino.h>

// EARZ class
#define LOWVAL 1
#define HIGHVAL 2
#define EAR_DELAY 200
#define EAR_POS_TOTAL 18
#define EAR_POS_OFFSET 13 // 3 if init reverse
#define MVT_REVERSE -1
#define MVT_STOP 0
#define MVT_FORWARD 1


class Earz {
  
  int motor_pina;
  int motor_pinb;
  int pos_pin;
  int current_angle;
  int mvt;
  unsigned long timestamp;
  
  public:
  Earz(int pina, int pinb, int pinp){

    motor_pina = pina;
    motor_pinb = pinb;
    pos_pin = pinp;
    current_angle = 0;
    mvt = MVT_STOP; 

    pinMode(motor_pina, OUTPUT);
    pinMode(motor_pinb, OUTPUT);
    pinMode(pos_pin, INPUT);
    
  }
  
  void clearPos(){
  
   
    forward();
    
    int temp_pos = 0;
    while (temp_pos < EAR_POS_TOTAL) { 
      static int lastRead = 0;
      static int state = HIGHVAL;
      int readMe = analogRead(pos_pin);
  
      if ((HIGHVAL == state) && (readMe < 500)) {
        temp_pos ++;
        Serial.print ("pos : ");
        Serial.println (temp_pos);
        unsigned long duration = millis() - timestamp;
        Serial.print ("step : ");
        Serial.print (duration);
        Serial.print (" value : ");
        Serial.println (temp_pos);
        state = LOWVAL;
        timestamp = millis();
        if (duration > 400){
          Serial.print("-- lock @ ");
          Serial.println (temp_pos);
          temp_pos = EAR_POS_TOTAL - EAR_POS_OFFSET;
        }
      }
      if ((LOWVAL == state) && (readMe > 500)) {
        state = HIGHVAL;
      }
      lastRead = readMe;
    }
    // set ear to pos 0
    softStop();
    current_angle = 0;  
  }
  
  
  void softStop(){
    digitalWrite(motor_pina, LOW);
    digitalWrite(motor_pinb, LOW);
    mvt = MVT_STOP;
    delay(EAR_DELAY);
  }
  
  void forward(){
    softStop();
    digitalWrite( motor_pina, LOW);
    digitalWrite( motor_pinb, HIGH);
    mvt = MVT_FORWARD;
  }
  
  void reverse(){
    softStop();
    digitalWrite( motor_pina, HIGH);
    digitalWrite( motor_pinb, LOW);
    mvt = MVT_REVERSE;
  }
  
  
};


