#include "buzzer.h"
#include "configuration_GPIO.h"
#include <wiringPi.h>

void buzzerPastille(int gpio) {
  pinMode(gpio, OUTPUT);
  digitalWrite(gpio, HIGH);
  delay(250);
  digitalWrite(gpio, LOW);
}
