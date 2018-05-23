#include <vector>

#include "../psm.h"

#define WINDOW 640
#define QUALITY 100

#define FUNC(x) std::sin(x) *100

const double dt = 0.05;
bool paused = false;

std::vector<vec2> joints(QUALITY);

// handle controls
void key_press(unsigned char key){
	if(key == ' ')
		paused = !paused;
}

void setup();
// executes every dt
void render(psm_window* w){
	w->draw_graph(joints);
	for(auto p : joints)
		w->draw_circle(p, 2);

	if(paused) return;

	// TODO: update joints here

}

void setup(){
	double delim = (double)WINDOW /(double)QUALITY;
	double offset = (double)WINDOW /2;
	for(int i = 0; i < QUALITY; i++){
		double x = i *delim;
		joints.push_back(vec2{x, FUNC(x) +offset});
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	setup();
	psm::init("String Vibration", WINDOW, WINDOW, dt);
	return 0;
}
