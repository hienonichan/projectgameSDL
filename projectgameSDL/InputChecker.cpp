#include"InputChecker.h"
#include"GameControl.h"
InputChecker* InputChecker::instance = 0;


InputChecker::InputChecker():mouse_position(new Vector(0,0)){
	for (int i = 0; i < 3; i++) {
		checkMouse[i] = false;
   }
}



void InputChecker::checkInput() {
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			GameControl::getInstance()->quit();
		}



		if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				checkMouse[LEFT] = true;
			}
			if (e.button.button == SDL_BUTTON_MIDDLE) {
				checkMouse[MIDDLE] = true;
			}
			if (e.button.button == SDL_BUTTON_RIGHT) {
				checkMouse[RIGHT] = true;
			}
		}


		if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				checkMouse[LEFT] = false;
			}
			if (e.button.button == SDL_BUTTON_MIDDLE) {
				checkMouse[MIDDLE] = false;
			}
			if (e.button.button == SDL_BUTTON_RIGHT) {
				checkMouse[RIGHT] = false;
			}

		}

		if (e.type == SDL_MOUSEMOTION) {
			mouse_position->setX(e.motion.x);
			mouse_position->setY(e.motion.y);
		}
	}
}



bool InputChecker::checkKeyboard(SDL_Scancode key) {
	if (keystates != 0) {
		return keystates[key];
	}
	else {
		return false;
	}
}