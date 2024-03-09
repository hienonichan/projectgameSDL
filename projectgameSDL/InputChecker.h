#ifndef __InputChecker__
#define __InputChecker__

#include"Vector.h"
#include<SDL.h>
#include<SDL_image.h>

enum mouse {
	LEFT=0,
	MIDDLE=1,
	RIGHT=2
};

class InputChecker {
public:
	static InputChecker* getInstance() {
		if (instance == 0) {
			instance = new InputChecker();
			return instance;
		}
		return instance;
	}

	void checkInput();

	bool checkKeyboard(SDL_Scancode key);

	Vector* getMousePostion() { return mouse_position; }

private:
	InputChecker();

	bool checkMouse[3];
	Vector *mouse_position;
	static InputChecker* instance;

	const Uint8* keystates = SDL_GetKeyboardState(0);
};
#endif
