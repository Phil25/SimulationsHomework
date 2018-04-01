#include "../psm.h"
#include <iostream>

#define WINDOW_X 640
#define WINDOW_Y 640

const float dt = 0.01;
const float radius = 50;
const float mass = 1;
const float grav = -10;

float roll = 0.0f;
vec2 pos = {100, 100};
vec2 vel = {200, 800};

void render(psm_window* w){
	w->draw_circle(pos, radius, roll);
	if(pos.y <= radius)
		return;

	vel.y += grav *mass;
	w->draw_vector(pos, vel);

	pos.x += (vel.x + (dt *grav /2)) *dt;
	pos.y += (vel.y + (dt *grav /2)) *dt;
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	psm::init("Incline Roll", WINDOW_X, WINDOW_Y, dt);
	return 0;
}
