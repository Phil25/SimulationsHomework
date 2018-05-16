#include <stack>

#include "../psm_window.h"

#ifndef BRUSH_H
#define BRUSH_H


class brush{
	vec2 pos;
	vec2 dir;

	std::stack<vec2> positions;
	std::stack<vec2> directions;

public:
	double rot;
	double size;
	
public:
	brush(double, double);

	vec2 get_pos();
	vec2 get_dir(bool=false);

	void move(double);
	void turn(double);

	void save();
	void load();

};


#endif
