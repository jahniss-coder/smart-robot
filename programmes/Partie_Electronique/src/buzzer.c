#include "../include/buzzer.h"
#include "../include/configuration_GPIO.h"
#include <wiringPi.h>

void buzzerPastille(int gpio) {
  pinMode(gpio, OUTPUT);
  digitalWrite(gpio, HIGH);
  delay(300);
  digitalWrite(gpio, LOW);
}
