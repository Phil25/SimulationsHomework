#include "brush.h"

#define TO_RAD(x) x *PI /180

brush::brush(double x, double y):
	s({
		vec2{x,y},	// position
		vec2{1,0},	// direction
		0			// rotation
	}),
	size(10)
{}

vec2 brush::get_pos(){
	return this->pos;
}

vec2 brush::get_dir(bool scaled){
	return scaled ? vec2{dir.x *size, dir.y *size} : this->dir;
}

void brush::move(double distance){
	pos.x += distance *dir.x;
	pos.y += distance *dir.y;
}

void brush::turn(double distance){
	rot += TO_RAD(distance);
	dir.x = std::cos(rot);
	dir.y = std::sin(rot);
}

void brush::save(){
	states.push(s);
}

void brush::load(){
	if(states.size() <= 0)
		return;
	s = states.top();
	states.pop();
}
