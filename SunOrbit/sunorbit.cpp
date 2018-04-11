#include "../psm.h"
#include <iostream>

#define WINDOW_X 640
#define WINDOW_Y 640

#define TO_RAD(x) x *PI /180

#define SUN_FIXED true
#define CONFINE_POSITIONS
//#define DRAW_TRAJECTORY
//#define DRAW_VELOCITY

#define SCALE 10000000

// input constants
const float dt = 0.01;
const float G = 6.6742e-11 *SCALE;

// non-constants
struct body{
	std::string name;
	float r;
	float m;
	vec2 force;
	vec2 acc;
	vec2 vel;
	vec2 pos;
};
const float sun_mass = 10000000;
const float orbital_velocity = 75;//std::sqrt(G *sun_mass /200);
std::vector<body> b = {
	{ // sun
		"s",
		50, // radius
		sun_mass, // mass
		{0, 0}, // force
		{0, 0}, // acceleration
		{0, 0}, // velocity
		{0, 0} // position
	},
	{ // earth
		"e",
		20, // radius
		sun_mass, // mass
		{0, 0}, // force
		{0, 0}, // acceleration
		{0, orbital_velocity}, // velocity
		{200, 0} // position
	},
	{ // moon
		"m",
		5, // radius
		10000, // mass
		{0, 0}, // force
		{0, 0}, // acceleration
		{0, orbital_velocity*2}, // velocity
		{230, 0} // position
	}
};
int count = b.size();
float dist2 = 0;
int frame = 0;

#ifdef DRAW_TRAJECTORY
std::vector<std::vector<vec2>> trajectories(count);
#endif

#ifdef CONFINE_POSITIONS
void confine_positions(){
	const float dampening = 0.25;
	for(int i = 0; i < count; i++){
		const float bound_x = WINDOW_X/2 -b[i].r;
		const float bound_y = WINDOW_Y/2 -b[i].r;
		if(b[i].pos.y > bound_y){
			b[i].pos.y = bound_y;
			b[i].vel.y *= -dampening;
		}
		if(b[i].pos.x > bound_x){
			b[i].pos.x = bound_x;
			b[i].vel.x *= -dampening;
		}
		if(b[i].pos.y < -bound_y){
			b[i].pos.y = -bound_y;
			b[i].vel.y *= -dampening;
		}
		if(b[i].pos.x < -bound_x){
			b[i].pos.x = -bound_x;
			b[i].vel.x *= -dampening;
		}
	}
}
#endif

void key_press(unsigned char key){
#ifdef DRAW_TRAJECTORY
	trajectories.push_back(std::vector<vec2>());
#endif
	b.push_back({
		std::string(1, key),
		20, // radius
		1000000, // mass
		{0, 0}, // force
		{0, 0}, // acceleration
		{0, 200}, // velocity
		{(-300 +(float)key), -200} // position
	});
	count++;
}

// executes every dt
void render(psm_window* w){
	frame++;

	w->println(std::to_string(count));

	// draw bodies
	for(int i = 0; i < count; i++)
		w->draw_circle(b[i].pos, b[i].r);

	// iterate through every body
	for(int i = 0; i < count; i++){
		// iterate through every other body
		for(int j = 0; j < count; j++){
			if(i == j) continue;
			const float dist2 = psm_window::get_vector_distance(b[i].pos, b[j].pos, true);

			// calculate force
			float magnitude = -G *b[i].m *b[j].m /dist2;
			b[i].force.x = magnitude *(b[i].pos.x -b[j].pos.x);
			b[i].force.y = magnitude *(b[i].pos.y -b[j].pos.y);

			// calculate acceleration
			b[i].acc.x = b[i].force.x /b[i].m;
			b[i].acc.y = b[i].force.y /b[i].m;

			// increment velocity
			b[i].vel.x += b[i].acc.x *dt;
			b[i].vel.y += b[i].acc.y *dt;
		}
	}

	for(int i = SUN_FIXED; i < count; i++){
		// calculate new position
		b[i].pos.x += b[i].vel.x *dt;
		b[i].pos.y += b[i].vel.y *dt;
		w->draw_text_offset(b[i].pos, b[i].name);

#ifdef DRAW_TRAJECTORY
		// cache position and draw trajectory
		if(frame %5 == 0)
			trajectories[i].push_back(b[i].pos);
		w->draw_graph(trajectories[i]);
#endif
	}


#ifdef CONFINE_POSITIONS
	confine_positions();
#endif

#ifdef DRAW_VELOCITY
	for(int i = 0; i < count; i++)
		w->draw_vector(b[i].pos, b[i].vel);
#endif

}

int main(int argc, char** argv){
	std::cout << "orbital_velocity: " << orbital_velocity << std::endl;
	glutInit(&argc, argv);
	psm::init("Sun Orbit", WINDOW_X, WINDOW_Y, dt, vec2{WINDOW_X/2, WINDOW_Y/2});
	return 0;
}


/* calculations for only two bodies - e and s

dist2 = psm_window::get_vector_distance(b[0].pos, b[1].pos, true);

// calculate force: -G *m1 *m2 /dist2 *(pos1 -pos2)
e.force.x = -G *e.m *s.m *(e.pos.x -s.pos.x) /dist2;
e.force.y = -G *e.m *s.m *(e.pos.y -s.pos.y) /dist2;

s.force.x = -G *e.m *s.m *(s.pos.x -e.pos.x) /dist2;
s.force.y = -G *e.m *s.m *(s.pos.y -e.pos.y) /dist2;

// calculate acceleration
e.acc.x = e.force.x /e.m;
e.acc.y = e.force.y /e.m;

s.acc.x = s.force.x /s.m;
s.acc.y = s.force.y /s.m;

// calculate velocity
e.vel.x += e.acc.x *dt;
e.vel.y += e.acc.y *dt;

s.vel.x += s.acc.x *dt;
s.vel.y += s.acc.y *dt;

// calculate position
e.pos.x += e.vel.x *dt;
e.pos.y += e.vel.y *dt;

#ifndef SUN_FIXED
s.pos.x += s.vel.x *dt;
s.pos.y += s.vel.y *dt;
#endif

*/
