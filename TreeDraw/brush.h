#include <stack>

#include "../psm_window.h"

#ifndef BRUSH_H
#define BRUSH_H

struct state{
	vec2 pos;
	vec2 dir;
	double rot;
};

class brush{
	state s;
	vec2 last_pos;

	vec2& pos = s.pos;

	vec2& dir = s.dir;
	double& rot = s.rot;

	std::stack<state> states;

public:
	double size;

public:
	brush(double, double);

	vec2 get_pos();
	vec2 get_last_pos();
	vec2 get_dir(bool=false);
	int get_stack_size();

	void move(double);
	void turn(double);

	void save();
	void load();

};


#endif
