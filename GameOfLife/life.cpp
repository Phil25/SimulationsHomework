#include <iostream>

#include "../psm.h"
#include "input.h"
#include "grid.h"
#include "rules.h"

#define WINDOW 640

// grid cell_size
#define SIZE 100
#define loop_grid(i,j) \
	for(int i = 0; i < SIZE; i++)\
	for(int j = 0; j < SIZE; j++)

// constants
const double dt = 0.01;
const double cell_size = (double)WINDOW/SIZE;

// buffers for storing states
grid<SIZE> this_gen;
grid<SIZE> next_gen;

// input class to handle controls
input<SIZE> i(cell_size, this_gen, next_gen);

// handle controls
void key_press(unsigned char key){
	i.on_key(key);
}

int get_neighbours(int x, int y){
	int count = 0;
	//grab offsets to all nearest cells
	for(int i = -1; i <= 1; i++)
		for(int j = -1; j <= 1; j++)
			// skip the cell itself
			if(!(i == 0 && j == 0))
				count += this_gen(x+i, y+j);

	return count;
}

// executes every dt
void render(psm_window* w){

	// draw every alive cell
	loop_grid(x, y)
		if(this_gen(x, y))
			w->draw_square(vec2{x *cell_size, y *cell_size}, cell_size);

	// draw input related shapes
	i.draw(w);

	// return if animation is paused
	if(i.is_paused)
		return;

	// get next gen from number of neighbours
	loop_grid(x, y){
		int count = get_neighbours(x, y);
		next_gen(x, y) = rules::get_next_gen(this_gen(x, y), count);
	}

	// copy next_gen over to this_gen
	loop_grid(x, y)
		this_gen(x, y) = next_gen(x, y);
}

int main(int argc, char** argv){
	rules::read();
	glutInit(&argc, argv);
	psm::init("Game of Life", WINDOW, WINDOW, dt);
	return 0;
}
