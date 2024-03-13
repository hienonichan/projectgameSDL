#include<SDL.h>
#include"Camera.h"

Camera* Camera::instance = 0;

Camera::Camera() :position(0, 0) {
	viewbox = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
}

void Camera::Update() {
	if (target != nullptr) {
		viewbox.x = target->x - SCREEN_WIDTH / 2;
		viewbox.y = target->y - SCREEN_HEIGHT / 2;
		if (viewbox.x < 0) {
			viewbox.x = 0;
		}
		if (viewbox.y < 0) {
			viewbox.y = 0;
		}

		if (viewbox.x > (2 * SCREEN_WIDTH - viewbox.w)) {
			viewbox.x = 2 * SCREEN_WIDTH - viewbox.w;
		}
		if (viewbox.y > (2 * SCREEN_HEIGHT - viewbox.h)) {
			viewbox.y = 2 * SCREEN_HEIGHT - viewbox.h;
		}
		position = Vector(viewbox.x, viewbox.y);
	}
}


