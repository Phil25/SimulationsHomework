#include <iostream>

#include "grid.h"
#include "../psm.h"

#define WINDOW 640
#define SIZE 52

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

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	psm::init("Heat Spread", WINDOW, WINDOW, dt);
	return 0;
}
