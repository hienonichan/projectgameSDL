#include"PlayState.h"
#include<iostream>
void PlayState::update() {

}

void PlayState::render() {

}


bool PlayState::loadState() {
	std::cout << "loading playState\n";
	return true;
}

bool PlayState::exitState() {
	std::cout << "exting playState\n";
	return true;
}