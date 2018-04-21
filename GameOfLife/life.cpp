#include <iostream>

#include "../psm.h"
#include "input.h"
#include "grid.h"

#define WINDOW 640

// grid size
#define SIZE 100
#define ITERATE(i,j) \
	for(int i = 0; i < SIZE; i++)\
	for(int j = 0; j < SIZE; j++)

// constants
const double dt = 0.01;
const double size = (double)WINDOW/SIZE;

// buffers for storing states
grid<SIZE> thisGen;
grid<SIZE> nextGen;

// input class to handle controls
input<SIZE> i(size, thisGen, nextGen);

// handle controls
void key_press(unsigned char key){
	i.on_key(key);
}

void draw_cell(psm_window* w, int x, int y){
	// draw square relative to cell's position
	if(thisGen(x, y)){
		vec2 pos{x *size, y *size};
		w->draw_square(pos, size);
	}
}

int get_neighbours(int x, int y){
	int count = 0;
	//grab offsets to all nearest cells
	for(int i = -1; i <= 1; i++)
		for(int j = -1; j <= 1; j++)
			// skip the cell itself
			if(!(i == 0 && j == 0))
				count += thisGen(x+i, y+j);

	return count;
}

// apply game of life rules
void evolve(bool& thisGenCell, bool& nextGenCell, int neighbours){
	if(thisGenCell)
		nextGenCell = neighbours == 2 || neighbours == 3;
	else
		nextGenCell = neighbours == 3;
}

void nextIteration(){
	// calculate next gen
	ITERATE(x, y)
		evolve(thisGen(x, y), nextGen(x, y), get_neighbours(x, y));

	// copy nextGen over to thisGen
	ITERATE(x, y)
		thisGen(x, y) = nextGen(x, y);
}

// executes every dt
void render(psm_window* w){

	// iterate every cell
	ITERATE(x, y)
		draw_cell(w, x, y);

	// draw input related shapes
	i.draw(w);

	// calculate next iteration
	if(i.is_playing)
		nextIteration();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	psm::init("Game of Life", WINDOW, WINDOW, dt);
	return 0;
}
