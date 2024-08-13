#include <Stepper.h>

const int STEPS_PER_REV = 200;

Stepper stepper_NEMA17(STEPS_PER_REV, 4, 5,6 ,7);


void setup() {
  stepper_NEMA17.setSpeed(60); 
   
}

void loop() {
  stepper_NEMA17.step(STEPS_PER_REV / 100);
  
}
