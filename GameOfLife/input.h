#include <iostream>

#include "../psm_window.h"
#include "grid.h"


#ifndef INPUT_H
#define INPUT_H

template <int S>
class input{

	grid<S>& thisGen;
	grid<S>& nextGen;

	int sx = 0,
		sy = 0;

	const double cell_size;

public:
	bool is_playing = false;
	bool draw_mode = false;

public:
	input(const double cell_size, grid<S>& thisGen, grid<S>& nextGen):
		cell_size(cell_size),
		thisGen(thisGen),
		nextGen(nextGen){}

	void on_key(unsigned char key){
		switch(key){
			case 'q': // exit application
				std::exit(0);
				break;
			case ' ': // resume/pause
				is_playing = !is_playing;
				break;
			case 'w': // move up
			case 'k':
				sy++;
				if(sy >= S)
					sy = 0;
				break;
			case 's': // move down
			case 'j':
				sy--;
				if(sy < 0)
					sy = S-1;
				break;
			case 'd': // move right
			case 'l':
				sx++;
				if(sx >= S)
					sx = 0;
				break;
			case 'a': // move left
			case 'h':
				sx--;
				if(sx < 0)
					sx = S-1;
				break;
			case 'e': // toggle selected cell
				thisGen(sx, sy) = !thisGen(sx, sy);
				break;
			case 'g': // spawn a glider
				thisGen(sx, sy) = true;
				thisGen(sx+1, sy+1) = true;
				thisGen(sx+1, sy+2) = true;
				thisGen(sx, sy+2) = true;
				thisGen(sx-1, sy+2) = true;
				break;
			case 'r': // toggle draw mode
				draw_mode = !draw_mode;
				break;
		}
	}

	void draw(psm_window* w){
		// draw the selection circle
		const double half_size = cell_size/2;
		vec2 pos{sx *cell_size +half_size, sy *cell_size +half_size};
		w->draw_circle(pos, cell_size);

		// continuously draw selected cell when in draw mode
		if(draw_mode)
			thisGen(sx, sy) = true;
	}

};


#endif
