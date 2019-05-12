#include "Arduino.h"
#include "Joystick.h"

//last status
Cardinal _last;

//constructor
Joystick::Joystick(){
    pinMode(Joystick_X, INPUT_PULLUP);
    pinMode(Joystick_Y, INPUT_PULLUP);
    pinMode(Joystick_btn, INPUT_PULLUP);
    
    calibrate(); //base
};


void Joystick::calibrate(){
    //get center position
    offset.x = analogRead(Joystick_X);
    offset.y = analogRead(Joystick_Y);

    //set fixed 
    offset_min.x=0; 
    offset_min.y=0;
    offset_max.x=1023; 
    offset_max.y=1023;

    //set initial position
    _last.x = offset.x;
    _last.y = offset.y;
};

void Joystick::update(){
    Cardinal _pos;
    
    //get current position
    _pos.x = analogRead(Joystick_X);
    _pos.y = analogRead(Joystick_Y);

    // filter 
    changed=false;
    if(_pos.x+Joystick_noise<_last.x || _pos.x-Joystick_noise>_last.x){
        _last.x=_pos.x; 
        changed=true;
    }else{
        _pos.x=_last.x;
    }
    if(_pos.y+Joystick_noise<_last.y || _pos.y-Joystick_noise>_last.y){
        _last.y=_pos.y; 
        changed=true;
    }else{
        _pos.y=_last.y;
    }

    // center fix
    if(_pos.x+Joystick_noise+1<offset.x && _pos.x-Joystick_noise-1>offset.x) _pos.x=offset.x;
    if(_pos.y+Joystick_noise+1<offset.y && _pos.y-Joystick_noise-1>offset.y) _pos.y=offset.y;

    // button state
    btn=digitalRead(Joystick_btn);
    if(_btn!=btn){
        _btn=btn;
        changed=true;
    }

    if(!changed) return;

    // adjust offset
    _pos.x = _pos.x-offset.x;
    _pos.y = _pos.y-offset.y;

    //calculate relative position
    if(_pos.x<0){
        _pos.x = (((float)_pos.x/(offset.x-offset_min.x))*joystick_scale); //relative to min x
    }else{
        _pos.x = (((float)_pos.x/(offset_max.x-offset.x))*joystick_scale); //relative to max x
    }
    if(_pos.y<0){
        _pos.y = (((float)_pos.y/(offset.y-offset_min.y))*joystick_scale); //relative to min y
    }else{
        _pos.y = (((float)_pos.y/(offset_max.y-offset.y))*joystick_scale); //relative to max y
    }

    //return new cardinal position
    position.x=_pos.x;
    position.y=_pos.y;
};