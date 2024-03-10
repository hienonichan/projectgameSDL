#ifndef __DelayState__
#define __DelayState__
#include"State.h"
#include<vector>
#include"GameObject.h"
class DelayState:public State {
public:
    virtual void update();
    virtual void render();

    virtual bool loadState();
    virtual bool exitState();

    int getStateCode() { return code; }
private:
    int code = 3;
    std::vector<GameObject*>gameObjects;

    static void turnToHome();
    static void turnToPlay();
};
#endif