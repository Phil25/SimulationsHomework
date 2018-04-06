#include <string>
#include <GL/glut.h>
#include "psm_window.h"

void render(psm_window*);

namespace psm{
	psm_window* w = nullptr;
	const float line_diff = 24;
	float line_offset;
	int X, Y;

	void game_loop(int dt){
		glutPostRedisplay();
		glutTimerFunc(dt, game_loop, dt);
	}

	void display(void){
		glClear(GL_COLOR_BUFFER_BIT);
		render(w);
		line_offset = Y; // reset printing offset
		glFlush();
	}

	void print(std::string text){
		line_offset -= line_diff;
		vec2 pos = {0, line_offset};
		w->draw_text(pos, text);
	}

	psm_window* init(std::string name, int X, int Y, float dt){
		dt *= 1000;
		psm::X = X;
		psm::Y = Y;
		line_offset = Y;

		glutTimerFunc(dt, game_loop, dt);
		w = new psm_window(name.c_str(), X, Y, display);
		return w;
	}
}
