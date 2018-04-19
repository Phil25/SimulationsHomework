#include "../psm.h"
#include <sstream>
#include <iostream>
#include <vector>

#define WINDOW_X 640
#define WINDOW_Y 640

#define TO_RAD(x) x *PI /180

#define PLANE_LENGTH 1000
#define BALL_START 500

#define I_CYLINDER mass *radius *radius /2
#define I_BALL 2 *mass *radius *radius /5

#define PPM 25 // pixels per metere

// input constants
const float dt = 0.01;
const float g = -9.81;
const float radius = 25;
const float mass = 1;
const float ang_deg = 15;
const float beta_deg = 90;
const float I = I_CYLINDER;

// inclined surface angle in radians
const float ang = TO_RAD(ang_deg);
const float sina = sin(ang);
const float cosa = cos(ang);

// acceleration
const float a = (g *sina) /(1 + I/(mass *radius *radius)) *PPM;
const vec2 av = {cosa *a, sina *a};
const float epsilon = a /radius;

// environment and placement (unrelated)
const vec2 plane_start = {100, 0};
const vec2 plane_end = {
	plane_start.x +PLANE_LENGTH *cosa,
	plane_start.y +PLANE_LENGTH *sina
};
const vec2 ball_plane_position = {
	plane_start.x +BALL_START *cosa,
	plane_start.y +BALL_START *sina
};
const vec2 ball_position = {
	ball_plane_position.x -radius *sina,
	ball_plane_position.y +radius *cosa
};

// non-constants
vec2 pos = ball_position;
vec2 vel = {0, 0};
float beta = TO_RAD(beta_deg);
float omega = 0;
int frame = 0;

// path-drawing
std::vector<vec2> positions;
std::vector<vec2> rpositions;

std::string display_velocity(){
	std::ostringstream oss;
	oss.precision(4);
	float vel_len = psm_window::get_vector_length(vel);
	oss << "Velocity: " << vel_len << "m/s^2";
	return oss.str();
}

std::string display_velocityv(){
	std::ostringstream oss;
	oss.precision(4);
	oss << "Velocity Vector: x(" << vel.x << "), y(" << vel.y << ")";
	return oss.str();
}

std::string display_kenergy(){
	std::ostringstream oss;
	float vel_len = psm_window::get_vector_length(vel);
	oss << "Kinetic Energy: " << mass *vel_len *vel_len /2 << 'J';
	return oss.str();
}

std::string display_penergy(){
	std::ostringstream oss;
	oss << "Potential Energy: " << mass *(-g) *(pos.y -radius) << 'J';
	return oss.str();
}

void key_press(unsigned char key){
	(void)key;
}

// executes every dt
void render(psm_window* w){

	// draw rotation graph
	w->draw_graph(rpositions);

	// draw path graph
	w->draw_path(positions);

	// draw the plane
	w->draw_line(plane_start, plane_end);

	// print information
	w->println(display_velocity());
	w->println(display_velocityv());
	w->println(display_kenergy());
	w->println(display_penergy());

	// end simulation when object beyond screen
	if(pos.y <= -radius || pos.x <= -radius)
		return;

	// draw the circle object
	w->draw_circle(pos, radius);
	w->draw_circle(pos, 5, 4);

	// calculate rotational angle
	omega += epsilon *dt;
	beta -= omega *dt;

	// draw diameter to simulate roll
	vec2 r1pos = {pos.x +cos(beta) *radius, pos.y +sin(beta) *radius};
	vec2 r2pos = {pos.x -cos(beta) *radius, pos.y -sin(beta) *radius};
	w->draw_line(r1pos, r2pos);

	// cache positions for the graph
	if(frame++ % 5 == 0){
		positions.push_back(pos);
		rpositions.push_back(r2pos);
	}

	// draw velocity vector
	w->draw_vector(pos, vel);

	// translate position
	pos.x += vel.x *dt;
	pos.y += vel.y *dt;

	// calculate velocity
	vel.x += av.x *dt;
	vel.y += av.y *dt;
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	psm::init("Incline Roll", WINDOW_X, WINDOW_Y, dt);
	return 0;
}
