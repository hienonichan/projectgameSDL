#include"StateManager.h"
#include"State.h"


void StateManager::addState(State*pState) {
	if (!gameStates.empty()) {
		if (gameStates.back()->getStateCode() == pState->getStateCode()) {
			return;
		}
		else {
			gameStates.push_back(pState);
		}
	}
	else {
		gameStates.push_back(pState);
	}
	gameStates.back()->loadState();
}


void StateManager::deleteState(State* pState) {
	if (!gameStates.empty()) {
		gameStates.back()->exitState();
		delete gameStates.back();
		gameStates.pop_back();
	}
}

void StateManager::update() {
	gameStates.back()->update();

}

void StateManager::render() {
	gameStates.back()->render();
}
