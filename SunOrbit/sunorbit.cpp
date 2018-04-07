#include "../psm.h"
#include <iostream>

#define WINDOW_X 640
#define WINDOW_Y 640

#define TO_RAD(x) x *PI /180

// input constants
const float dt = 0.01;

// non-constants
vec2 pos = {};

// executes every dt
void render(psm_window* w){
	w->draw_circle(vec2{0, 0}, 50);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	psm::init("Incline Roll", WINDOW_X, WINDOW_Y, dt, vec2{WINDOW_X/2, WINDOW_Y/2});
	return 0;
}
