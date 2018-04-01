#include "../psm.h"
#include <iostream>

#define WINDOW_X 640
#define WINDOW_Y 640

// input constants
const float dt = 0.01;
const float g = -9.81;
const float radius = 50;
const float mass = 1;
const float ang_deg = 30;

// gravity vector
const vec2 grav = {0, g *mass};

// inclined surface angle in radians
const float ang = ang_deg *PI /180;
const float sina = sin(ang);
const float cosa = cos(ang);

// length of the negative inclined surface vector
const float sv_len = -mass *g *cosa;

// negative inclined surface vector
const vec2 sv = {cosa *sv_len, sina *sv_len};

float roll = 0.0f;
vec2 pos = {100, 400};
vec2 vel = {0, 0};

void render(psm_window* w){
	w->draw_circle(pos, radius, roll);
	if(pos.y <= radius)
		return;

	vel.add(grav);
	vel.add(sv);

	// draw velocity vector
	w->draw_vector(pos, vel);

	// apply velocity
	pos.x += (vel.x + (dt *g /2)) *dt;
	pos.y += (vel.y + (dt *g /2)) *dt;
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	psm::init("Incline Roll", WINDOW_X, WINDOW_Y, dt);
	return 0;
}
