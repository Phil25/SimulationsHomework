#include <iostream>

#include "grid.h"
#include "matrix.h"
#include "../psm.h"

#define WINDOW 640
#define SIZE 20

#define HEAT_LEFT 0.8
#define HEAT_TOP 0.5
#define HEAT_RIGHT 0.4
#define HEAT_BOTTOM 0.2

#define loop_grid(i,j) \
	for(int i = 0; i < SIZE; i++) \
	for(int j = 0; j < SIZE; j++)

grid<SIZE> plate;

const double dt = 0.01;
const double cell_size = (double)WINDOW /(double)SIZE;

const int sizemin1 = SIZE -1;
const int sizemin2 = SIZE -2;
const int matrix_size = sizemin2 *sizemin2;

// handle controls
void key_press(unsigned char /*key*/){
}

// executes every dt
void render(psm_window* w){
	loop_grid(x, y){
		vec2 pos{x *cell_size, y *cell_size};
		w->draw_square(pos, cell_size, plate(x, y));
		//w->draw_text(pos, std::to_string(plate(x, y)));
	}
}

double avg(double x, double y){
	return (x +y) /2;
}

void initial_state(){
	for(int i = 1; i < sizemin1; i++){
		plate(0, i) = HEAT_LEFT;
		plate(i, sizemin1) = HEAT_TOP;
		plate(sizemin1, i) = HEAT_RIGHT;
		plate(i, 0) = HEAT_BOTTOM;
	}
	plate(0, 0) = avg(HEAT_LEFT, HEAT_BOTTOM);
	plate(sizemin1, 0) = avg(HEAT_RIGHT, HEAT_BOTTOM);
	plate(0, sizemin1) = avg(HEAT_LEFT, HEAT_TOP);
	plate(sizemin1, sizemin1) = avg(HEAT_RIGHT, HEAT_TOP);
}

void gen_matrix(matrix& m){
	int left = 0, right = 0;
	for(size_t row = 0; row < m.size; row++){
		m(row, row) = -4;

		// bottom neighbour
		if(m.is_valid(row, row -sizemin2))
			m(row, row -sizemin2) = 1;

		// top neighbour
		if(m.is_valid(row, row +sizemin2))
			m(row, row +sizemin2) = 1;

		// left neighbour if doesn't wrap around
		if(m.is_valid(row, row -1)&& ++left % sizemin2 != 0)
			m(row, row -1) = 1;

		// right neighbour if doesn't wrap around
		if(m.is_valid(row, row +1) && ++right % sizemin2 != 0)
			m(row, row +1) = 1;
	}
}

void gen_solutions(matrix& m){
	for(size_t i = 0; i < m.size; i += sizemin2)
		m.sol[i] -= HEAT_LEFT;

	for(size_t i = 0; i < sizemin2; i++)
		m.sol[i] -= HEAT_TOP;

	for(size_t i = sizemin2 -1; i < m.size; i += sizemin2)
		m.sol[i] -= HEAT_RIGHT;

	for(size_t i = m.size -sizemin2; i < m.size; i++)
		m.sol[i] -= HEAT_BOTTOM;
}

void last_state(){
	matrix m(matrix_size);
	gen_matrix(m);
	gen_solutions(m);
	m.decompose();

	matrix sols(sizemin2, m.sol);
	sols.flip();
	sols.transpose();

	for(int x = 1; x < sizemin1; x++)
		for(int y = 1; y < sizemin1; y++)
			plate(x, y) = sols(x -1, y -1);
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	initial_state();
	last_state();
	psm::init("Heat Spread", WINDOW, WINDOW, dt);
}
