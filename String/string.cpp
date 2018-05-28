#include <vector>
#include <iostream>

#include "../psm.h"

#define WINDOW 640
#define QUALITY 100

#define FUNC(x) std::sin(x) *300
#define SPEED 10000

const double dt = 0.01;
const double delimiter = (double)WINDOW /(double)QUALITY;
const double delim2 = delimiter *delimiter;
bool paused = false;

std::vector<vec2> joints;
std::vector<double> velocities;
std::vector<double> accelerations;
std::vector<double> d_y;

// handle controls
void key_press(unsigned char /*key*/){
	paused = !paused;
}

void calc_change(int x){
	accelerations[x] = (joints[x-1].y -2* joints[x].y + joints[x+1].y) /delim2;
	accelerations[x] *= SPEED;
	velocities[x] += accelerations[x] *dt;
	d_y[x] = velocities[x] *dt;
}

// executes every dt
void render(psm_window* w){
	//w->draw_graph(joints);
	for(auto p : joints)
		w->draw_circle(p, 2);

	if(paused) return;

	for(int i = 1; i < QUALITY -1; i++)
		calc_change(i);

	for(int i = 1; i < QUALITY -1; i++)
		joints[i].y += d_y[i];

}

void setup(){
	double offset = (double)WINDOW /2;
	for(int i = 0; i < QUALITY; i++){
		double x = i *delimiter;
		joints.push_back(vec2{x, offset});
	}
	velocities.resize(QUALITY);
	accelerations.resize(QUALITY);
	d_y.resize(QUALITY);
	for(int i = 1; i < 27; i++){
		double x = i *delimiter;
		joints[i].y += FUNC(x);
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	setup();
	psm::init("String Vibration", WINDOW, WINDOW, dt);
	return 0;
}
