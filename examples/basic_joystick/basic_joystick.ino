#include "basic_joystick.h"
#include <Joystick.h>
Joystick joystick;

void setup(){
    Serial.begin(115200);
    joystick.calibrate();
}

void loop(){
    joystick.update();
    if(joystick.changed){
        Serial.print(joystick.position.x);
        Serial.print("\t");
        Serial.print(joystick.position.y);
        Serial.print("\t");
        Serial.println(joystick.btn);
    }
}