#ifndef __StateManager__
#define __StateManager__

#include"State.h"
#include"GameObject.h"
#include<vector>
class StateManager {
public:
    void addState(State* pState);
    void deleteState();

    void update();
    void render();

    std::vector<State*> getVectorState() { return gameStates; }
private:
    std::vector<State*>gameStates;
};

#endif