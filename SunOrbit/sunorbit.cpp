#include "../psm.h"
#include <iostream>

#define WINDOW_X 640
#define WINDOW_Y 640

#define TO_RAD(x) x *PI /180

// input constants
const float dt = 0.01;
const float G = 6.6742e-11;

// non-constants
struct{ // Sun
	float r = 100;
	float m = 100000000000000;
	vec2 force{};
	vec2 acc{};
	vec2 vel = {0, 0};
	vec2 pos = {0, 0};
} s;
struct{ // Earth
	float r = 20;
	float m = 1000;
	vec2 force{};
	vec2 acc{};
	vec2 vel = {50, 30};
	vec2 pos = {50, 150};
} e;
float dist2 = 0;

// executes every dt
void render(psm_window* w){

	// draw sun and earth
	w->draw_circle(s.pos, s.r);
	w->draw_circle(e.pos, e.r);

	dist2 = psm_window::get_vector_distance(e.pos, s.pos, true);

	// calculate force: -G *m1 *m2 /dist2 *(pos1 -pos2)
	e.force.x = -G *e.m *s.m *(e.pos.x -s.pos.x) /dist2;
	e.force.y = -G *e.m *s.m *(e.pos.y -s.pos.y) /dist2;

	// calculate acceleration
	e.acc.x = e.force.x /e.m;
	e.acc.y = e.force.y /e.m;

	// calculate velocity
	e.vel.x += e.acc.x *dt;
	e.vel.y += e.acc.y *dt;

	// calculate position
	e.pos.x += e.vel.x *dt;
	e.pos.y += e.vel.y *dt;

	w->draw_vector(e.pos, e.vel);

}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	psm::init("Sun Orbit", WINDOW_X, WINDOW_Y, dt, vec2{WINDOW_X/2, WINDOW_Y/2});
	return 0;
}
