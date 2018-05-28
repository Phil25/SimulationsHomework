#include <iostream>

#include "grid.h"
#include "../psm.h"

#define WINDOW 640
#define SIZE 52

#define HEAT_LEFT 0.8
#define HEAT_TOP 0.5
#define HEAT_RIGHT 0.4
#define HEAT_BOTTOM 0.2

#define loop_grid(i,j) \
	for(int i = 0; i < SIZE; i++)\
	for(int j = 0; j < SIZE; j++)

grid<SIZE> plate;

const double dt = 0.01;
const double cell_size = (double)WINDOW /(double)SIZE;

// handle controls
void key_press(unsigned char /*key*/){
}

// executes every dt
void render(psm_window* w){
	loop_grid(x, y)
		w->draw_square(vec2{x *cell_size, y *cell_size}, cell_size, plate(x, y));
}

void initial_state(){
	const int sizemin1 = SIZE -1;
	for(int i = 1; i < sizemin1; i++){
		plate(0, i) = HEAT_LEFT;
		plate(i, sizemin1) = HEAT_TOP;
		plate(sizemin1, i) = HEAT_RIGHT;
		plate(i, 0) = HEAT_BOTTOM;
	}
	plate(0, 0) = (HEAT_LEFT +HEAT_BOTTOM) /2;
	plate(sizemin1, 0) = (HEAT_RIGHT +HEAT_BOTTOM) /2;
	plate(0, sizemin1) = (HEAT_LEFT +HEAT_TOP) /2;
	plate(sizemin1, sizemin1) = (HEAT_RIGHT +HEAT_TOP) /2;
}

void last_state(){
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	initial_state();
	last_state();
	psm::init("Heat Spread", WINDOW, WINDOW, dt);
	return 0;
}
