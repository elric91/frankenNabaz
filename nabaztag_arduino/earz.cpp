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
  int target_angle;
  int mvt;
  unsigned long timestamp;
  
  public:
  Earz(int pina, int pinb, int pinp){

    motor_pina = pina;
    motor_pinb = pinb;
    pos_pin = pinp;
    current_angle = 0;
    target_angle = 0;
    
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
        unsigned long duration = millis() - timestamp;
        state = LOWVAL;
        timestamp = millis();
        if (duration > 400){
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
  
  void forwardTo(int angle){
    target_angle = angle;
    forward();
  }
    
  void reverse(){
    softStop();
    digitalWrite( motor_pina, HIGH);
    digitalWrite( motor_pinb, LOW);
    mvt = MVT_REVERSE;
  }

  void reverseTo(int angle){
    target_angle = angle;
    reverse();
  }


  void followPos(){
    if (mvt != MVT_STOP) {
      static int state = HIGHVAL;
      int readMe = analogRead(pos_pin);
    
      if ((HIGHVAL == state) && (readMe < 500)) {
        state = LOWVAL;
        if (mvt == MVT_FORWARD) current_angle = (current_angle + 1) % 18;
        if (mvt == MVT_REVERSE)  current_angle = (current_angle + 17) % 18;
       }
      if ((LOWVAL == state) && (readMe > 500)) {
        state = HIGHVAL;
      }
 
      Serial.print("angle : ");
      Serial.println(current_angle);
  
      if (current_angle == target_angle) softStop();
    }
  }
  
  
};


