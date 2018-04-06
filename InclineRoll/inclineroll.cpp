#include "../psm.h"
#include <sstream>
#include <iostream>

#define WINDOW_X 640
#define WINDOW_Y 640

#define TO_RAD(x) x *PI /180

#define I_CYLINDER mass *radius *radius /2
#define I_BALL 2 *mass *radius *radius /5

// input constants
const float dt = 0.01;
const float g = -9.81;
const float radius = 10;
const float mass = 1;
const float ang_deg = 50;
const float beta_deg = 90;
const float I = I_CYLINDER;

// inclined surface angle in radians
const float ang = TO_RAD(ang_deg);
const float sina = sin(ang);
const float cosa = cos(ang);

// gravity vector
//const vec2 grav = {0, g *mass};

// acceleration
const float a = (g *sina) /(1 + I/(mass *radius *radius));
const vec2 av = {cosa *a, sina *a};
const float epsilon = a /radius;

// negative inclined surface vector
//const float sv_len = -mass *g *cosa;
//const vec2 sv = {cosa *sv_len, sina *sv_len};

vec2 pos = {500, 400};
vec2 vel = {0, 0};
float vel_len = 0;
float beta = TO_RAD(beta_deg);
float omega = 0;

std::string display_velocity(){
	std::ostringstream oss;
	oss.precision(4);
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

void render(psm_window* w){
	vel_len = psm_window::get_vector_length(vel);
	w->draw_circle(pos, radius);

	psm::print(display_velocity());
	psm::print(display_velocityv());
	psm::print(display_kenergy());
	psm::print(display_penergy());

	omega += epsilon *dt;
	beta -= omega *dt;
	vec2 r1pos = {pos.x +cos(beta) *radius, pos.y +sin(beta) *radius};
	vec2 r2pos = {pos.x -cos(beta) *radius, pos.y -sin(beta) *radius};
	w->draw_line(r1pos, r2pos);

	if(pos.y <= radius)
		return;

	// translate position
	pos.x += vel.x *dt;
	pos.y += vel.y *dt;

	// add all relevant forces
	vel.x += av.x *dt;
	vel.y += av.y *dt;

	// draw velocity vector
	w->draw_vector(pos, vel);
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	psm::init("Incline Roll", WINDOW_X, WINDOW_Y, dt);
	return 0;
}
