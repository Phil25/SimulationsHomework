#include "../psm.h"
#include <iostream>

#define WINDOW 640

#define SIZE 100
#define ITERATE(i,j) \
	for(int i = 0; i < SIZE; i++)\
	for(int j = 0; j < SIZE; j++)

const double dt = 0.05;
const vec2 size{(double)WINDOW/SIZE, (double)WINDOW/SIZE};

bool thisGen[SIZE][SIZE]{{false}};
bool nextGen[SIZE][SIZE]{{false}};

void key_press(unsigned char key){
	switch(key){
		case 'q':
			std::exit(0);
			break;
		case 'w':
			thisGen[0][0] = !thisGen[0][0];
			break;
		case 'e':
			thisGen[1][0] = !thisGen[1][0];
			break;
	}
}

void draw_cell(psm_window* w, int x, int y){
	// return if cell is dead
	if(!thisGen[x][y])
		return;

	// draw square relative to cell's position
	vec2 pos{x*size.x, y*size.y};
	w->draw_square(pos, size.x);
}

int wrap_clamp(int val){
	return (val >= SIZE) ? 0 : (val < 0) ? SIZE-1 : val;
}

int get_neighbours(int x, int y){
	int count = 0;

	for(int i = -1; i <= 1; i++)
		for(int j = -1; j <= 1; j++){

			// skip the cell itself
			if(i == 0 && j == 0)
				continue;

			// wrap indexes extending beyond SIZE
			int x_check = wrap_clamp(x+i);
			int y_check = wrap_clamp(y+j);

			// increment if true
			count += thisGen[x_check][y_check];
		}

	return count;
}

// rules are applied here
void evolve(bool& thisGenCell, bool& nextGenCell, int neighbours){
	if(thisGenCell)
		nextGenCell = neighbours == 2 || neighbours == 3;
	else
		nextGenCell = neighbours == 3;
}

void nextIteration(){
	// calculate next gen
	ITERATE(x, y)
		evolve(thisGen[x][y], nextGen[x][y], get_neighbours(x, y));

	// copy nextGen over to thisGen
	ITERATE(x, y)
		thisGen[x][y] = nextGen[x][y];
}

// executes every dt
void render(psm_window* w){

	// iterate every cell
	ITERATE(x, y)
		draw_cell(w, x, y);

	nextIteration();
}

int main(int argc, char** argv){
	for(int i = 30; i < 80; i++)
		for(int j = 20; j < 80; j++)
			thisGen[i][j] = true;
	thisGen[1][1] = true;
	thisGen[2][1] = true;
	thisGen[2][3] = true;
	thisGen[3][1] = true;
	thisGen[3][2] = true;
	glutInit(&argc, argv);
	psm::init("Game of Life", WINDOW, WINDOW, dt);
	return 0;
}
