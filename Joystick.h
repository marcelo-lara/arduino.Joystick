#ifndef Joystick_h
#define Joystick_h

//variation fix
#ifndef Joystick_noise
#define Joystick_noise 3
#endif

// default X pin
#ifndef Joystick_X
#define Joystick_X A0
#endif

// default Y pin
#ifndef Joystick_Y
#define Joystick_Y A1
#endif

// default btn pin
#ifndef Joystick_btn
#define Joystick_btn A2
#endif

// default scale
#ifndef joystick_scale
#define joystick_scale  200
#endif


struct Cardinal{
    int x;
    int y;
};

class Joystick
{
  public:
    
    Joystick();
    void        calibrate();
    void        update();

    Cardinal    offset;
    Cardinal    noise;
    Cardinal    offset_max;
    Cardinal    offset_min;
    Cardinal    position;
    bool        changed;
    bool        btn;
  
  private:
    Cardinal    _last;
    bool        _btn;
};
#endif
