#include "brush.h"

#define TO_RAD(x) x *PI /180

brush::brush(double x, double y):
	pos(vec2{x,y}),
	dir(vec2{1,0}),
	rot(0),
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
	positions.push(pos);
	directions.push(dir);
}

void brush::load(){
	if(positions.size() <= 0)
		return;
	pos = positions.top();
	dir = directions.top();
	positions.pop();
	directions.pop();
}
