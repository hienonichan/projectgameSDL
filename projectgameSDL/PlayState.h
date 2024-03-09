#ifndef __PlayState__
#define __PlayState__
#include"State.h"

class PlayState :public State {
public:
    virtual void update();
    virtual void render();
    virtual bool loadState();
    virtual bool exitState();
};

#endif