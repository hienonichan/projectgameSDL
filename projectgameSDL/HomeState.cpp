#include"HomeState.h"
#include<iostream>

void HomeState::update() {

}


void HomeState::render() {

}


bool HomeState::loadState() {
	std::cout << "loading HomeState\n";
	return true;
}


bool HomeState::exitState() {
	std::cout << "exiting HomeState\n";
	return true;
}