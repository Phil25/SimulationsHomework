#include <ctime>
#include <iostream>

#include "brush.h"

#define TO_RAD(x) x *PI /180

double rand(double min, double max){
	static int seed = std::time(NULL);
	std::srand(++seed);
	double r = (double)std::rand() /RAND_MAX;
	return min + r *(max -min);
}

brush::brush(double x, double y):
	s({
		vec2{x,y},	// position
		vec2{1,0},	// direction
		0			// rotation
	}),
	last_pos(vec2{x, y}),
	size(10)
{}

vec2 brush::get_pos(){
	return this->pos;
}

vec2 brush::get_last_pos(){
	return this->last_pos;
}

vec2 brush::get_dir(bool scaled){
	return scaled ? vec2{dir.x *size, dir.y *size} : this->dir;
}

int brush::get_stack_size(){
	return states.size();
}

void brush::move(double distance){
	distance += distance *rand(-1, 1);

	last_pos = pos;
	pos.x += distance *dir.x;
	pos.y += distance *dir.y;
}

void brush::turn(double distance){
	distance += distance/10 *rand(-1, 1);

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
