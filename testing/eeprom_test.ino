#include <EEPROM.h>

#define EEPROM_SIZE sizeof(int)*2
#define DELAY 1000*20 //20s

void setup() {
  // put your setup code here, to run once:
  EEPROM.begin(EEPROM_SIZE);
}

int iter=0;

void loop() {
  if(iter==0){
    EEPROM.write(0, 1); //(indirizzo, valore)
    EEPROM.commit();
    EEPROM.write(4, 2); //4 byte ognuno ???
    EEPROM.commit();
  }else if(iter==1){
    EEPROM.write(0, 8); //(indirizzo, valore)
    EEPROM.commit();
    EEPROM.write(4, 9); //4 byte ognuno ???
    EEPROM.commit();
  }else if (iter==2){
    EEPROM.write(0, 10); //(indirizzo, valore)
    EEPROM.commit();
    EEPROM.write(4, 11); //4 byte ognuno ???
    EEPROM.commit();
  }else{
    exit(0);
  }

  int state_up = EEPROM.read(0);
  int state_down = EEPROM.read(4);
  Serial.println("iter: "); Serial.println(iter); 
  Serial.print("state_up: "); Serial.println(state_up); 
  Serial.print("state_down: "); Serial.println(state_down); 
  
  delay(DELAY);
}
