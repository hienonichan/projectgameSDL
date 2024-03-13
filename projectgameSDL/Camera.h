#ifndef __Camera__
#define __Camera__
#include<SDL.h>
#include"Vector.h"
#include"Point.h"
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT= 640;

class Camera {
public:

	static Camera* getInstance() {
		if (instance == 0) {
			instance = new Camera();
			return instance;
		}
		return instance;
	}

	void Update();
	SDL_Rect GetViewBox() { return viewbox; }
	Vector GetPosition() { return position; }

	void SetTarget(Point* set_target) { target = set_target; }

private:
	Camera();
	Point* target;
	Vector position;
	SDL_Rect viewbox;
	static Camera* instance;
};

#endif
