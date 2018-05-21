#include <iostream>
#include <sstream>

#include "../psm.h"
#include "brush.h"
#include "cmd.h"

#define WINDOW 640

#define CHECK_CLASS(var,cls) cls* cls_instance = dynamic_cast<cls*>(var)

const double dt = 0.01;
const int height = 8;

std::vector<std::pair<vec2, vec2>> graph;
std::vector<vec2> leaves;
brush b(WINDOW/2, WINDOW/4);

std::string next_iter(const std::string& s, const char from, const std::string& to){
	std::stringstream ss;
	int i = -1;
	while(++i, s[i] != '\0')
		ss << (s[i] == from ? to : std::string(1, s[i]));
	return ss.str();
}

// handle controls
void key_press(unsigned char key){
	cmd::parse(key);
}

// executes every dt
void render(psm_window* w){
	// draw brush
	w->draw_circle(b.get_pos(), b.size);
	w->draw_vector(b.get_pos(), b.get_dir(true));

	w->draw_graph(graph);
	w->draw_path(leaves);

	if(cmd::queue.size() <= 0)
		return;

	// execute and pop command
	const cmd::root* command = cmd::queue.front();
	command->exec(b);
	cmd::queue.pop();

	// draw line and a leaf if the command was leaf move
	if(CHECK_CLASS(command, const cmd::leaf)){
		leaves.push_back(b.get_pos());
		graph.push_back(std::pair<vec2, vec2>(b.get_pos(), b.get_last_pos()));
		return;
	}

	// draw line and a leaf if the command was a regular move
	if(CHECK_CLASS(command, const cmd::forward))
		graph.push_back(std::pair<vec2, vec2>(b.get_pos(), b.get_last_pos()));

}

void make_tree(){
	// add initial brush position
	cmd::init();
	graph.push_back(std::pair<vec2, vec2>(b.get_pos(), b.get_last_pos()));

	cmd::parse("---");

	/*
	for(int i = 0; i < 12; i++)
		cmd::parse("f[-f---fff-ff--ffff]+f");
	cmd::parse("------f---f---ff+++f+++f+++f++++++f+++f");
	cmd::parse("---f[---ff+++++ff-----ff");
	cmd::parse("]ff---f-f------f----f------f-f");
	cmd::parse("---f---ff+++f+++f+++f++++++f+++f");
	*/

	std::string test = "f";
	for(int i = 0; i < height; i++)
		test = next_iter(test, 'f', "FF[-f]+f");

	std::cout << test << std::endl;
	cmd::parse(test);

}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	make_tree();
	psm::init("Tree Draw", WINDOW, WINDOW, dt);
	return 0;
}
