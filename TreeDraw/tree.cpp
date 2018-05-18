#include <iostream>
#include <queue>

#include "../psm.h"
#include "brush.h"
#include "cmd.h"

#define WINDOW 640

#define DIST_MOVE 50
#define DIST_TURN 30

#define CHECK_CLASS(var,cls) cls* cls_instance = dynamic_cast<cls*>(var)

const double dt = 0.05;

std::queue<const cmd::root*> commands;
std::vector<std::pair<vec2, vec2>> graph;
brush b(WINDOW/2, WINDOW/2);

const cmd::root* forward = new cmd::move(DIST_MOVE);
const cmd::root* back = new cmd::move(-DIST_MOVE);
const cmd::root* left = new cmd::turn(DIST_TURN);
const cmd::root* right = new cmd::turn(-DIST_TURN);
const cmd::root* save = new cmd::save(0);
const cmd::root* load = new cmd::load(0);

// handle controls
void key_press(unsigned char key){
	switch(key){
		case 'w':
			commands.push(forward);
			break;

		case 'a':
			commands.push(left);
			break;

		case 's':
			commands.push(back);
			break;

		case 'd':
			commands.push(right);
			break;

		case 'q':
			commands.push(save);
			break;

		case 'e':
			commands.push(load);
			break;
	}
}

// executes every dt
void render(psm_window* w){
	// draw brush
	w->draw_circle(b.get_pos(), b.size);
	w->draw_vector(b.get_pos(), b.get_dir(true));

	w->draw_graph(graph);

	if(commands.size() <= 0)
		return;

	// execute and pop command
	const cmd::root* command = commands.front();
	command->exec(b);
	commands.pop();

	// draw line if the command was move
	if(CHECK_CLASS(command, const cmd::move))
		graph.push_back(std::pair<vec2, vec2>(b.get_pos(), b.get_last_pos()));

}

void make_tree(){
	// add initial brush position
	graph.push_back(std::pair<vec2, vec2>(b.get_pos(), b.get_last_pos()));

	for(int i = 0; i < 12; i++){
		commands.push(forward);
		commands.push(left);
		commands.push(left);
		commands.push(left);
		commands.push(forward);
		commands.push(left);
		commands.push(left);
		commands.push(left);
		commands.push(forward);
		commands.push(left);
		commands.push(left);
		commands.push(left);
		commands.push(forward);
		commands.push(left);
		commands.push(left);
	}
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	make_tree();
	psm::init("Tree Draw", WINDOW, WINDOW, dt);
	return 0;
}
