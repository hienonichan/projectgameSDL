#ifndef __StateManager__
#define __StateManager__

#include"State.h"
#include"GameObject.h"
#include<vector>
class StateManager {
public:
    void addState(State* pState);
    void deleteState(State* pState);

    void update();
    void render();

private:
    std::vector<State*>gameStates;
};

#endif