#include"GameObject.h"
#include"DelayState.h"
#include<iostream>
#include"GameControl.h"
#include"HomeState.h"
#include"ObjectTextureManager.h"

void DelayState::update() {

}

void DelayState::render() {

}

bool DelayState::loadState() {

	std::cout << "loading delaySTate\n";
	return true;
}

bool DelayState::exitState() {

	std::cout << "exiting delayState\n";
	return true;
}



void DelayState::turnToHome() {
	GameControl::getInstance()->getStateManager()->addState(new HomeState);
}

void DelayState::turnToPlay() {
	GameControl::getInstance()->getStateManager()->deleteState();
}

