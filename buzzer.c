#include"buzzer.h"
void buzzerPastille(int gpio){
  pinMode(gpio, OUTPUT);
  digitalWrite(gpio, HIGH);
  delay(2000);
  digitalWrite(gpio, LOW)
}


