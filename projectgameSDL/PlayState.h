#ifndef __PlayState__
#define __PlayState__
#include"State.h"
#include<vector>
#include"GameObject.h"
class PlayState :public State {
public:
    virtual void update();
    virtual void render();
    virtual bool loadState();
    virtual bool exitState();
   virtual int getStateCode() { return code; }
private:
    int code = 2;
    std::vector<GameObject*>gameObjects;
};

#endif