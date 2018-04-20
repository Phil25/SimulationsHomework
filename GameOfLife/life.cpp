#include "../psm.h"
#include <iostream>

#define WINDOW 640

#define SIZE 100
#define ITERATE(i,j) \
	for(int i = 0; i < SIZE; i++)\
	for(int j = 0; j < SIZE; j++)

const double dt = 0.01;
const vec2 size{(double)WINDOW/SIZE, (double)WINDOW/SIZE};

bool thisGen[SIZE][SIZE]{{false}};
bool nextGen[SIZE][SIZE]{{false}};

bool is_playing = false;
int sel_x = 0;
int sel_y = 0;
bool draw_mode = false;

// handle controls
void key_press(unsigned char key){
	switch(key){
		case 'q': // exit application
			std::exit(0);
			break;
		case ' ': // resume/pause
			is_playing = !is_playing;
			break;
		case 'w': // move up
		case 'k':
			sel_y++;
			if(sel_y >= SIZE)
				sel_y = 0;
			break;
		case 's': // move down
		case 'j':
			sel_y--;
			if(sel_y < 0)
				sel_y = SIZE -1;
			break;
		case 'd': // move right
		case 'l':
			sel_x++;
			if(sel_x >= SIZE)
				sel_x = 0;
			break;
		case 'a': // move left
		case 'h':
			sel_x--;
			if(sel_x < 0)
				sel_x = SIZE -1;
			break;
		case 'e': // toggle selected cell
			thisGen[sel_x][sel_y] = !thisGen[sel_x][sel_y];
			break;
		case 'g': // spawn a glider
			thisGen[sel_x][sel_y] = true;
			thisGen[sel_x+1][sel_y+1] = true;
			thisGen[sel_x+1][sel_y+2] = true;
			thisGen[sel_x][sel_y+2] = true;
			thisGen[sel_x-1][sel_y+2] = true;
			break;
		case 'r': // toggle draw mode
			draw_mode = !draw_mode;
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

// wrap around the grid
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

	// draw the selection circle
	w->draw_circle(vec2{sel_x *size.x +size.x/2, sel_y *size.y +size.y/2}, size.x);

	// continuously draw selected cell when in draw mode
	if(draw_mode)
		thisGen[sel_x][sel_y] = true;

	// calculate next iteration if in play mode
	if(is_playing)
		nextIteration();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	psm::init("Game of Life", WINDOW, WINDOW, dt);
	return 0;
}
