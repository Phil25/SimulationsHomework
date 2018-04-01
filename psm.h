#include <string>
#include <GL/glut.h>
#include "psm_window.h"

void render(psm_window*);

namespace psm{
	psm_window* window;

	void game_loop(int dt){
		glutPostRedisplay();
		glutTimerFunc(dt, game_loop, dt);
	}

	void display(void){
		glClear(GL_COLOR_BUFFER_BIT);
		render(window);
		glFlush();
	}

	psm_window* init(std::string name, int X, int Y, float dt){
		dt *= 1000;
		glutTimerFunc(dt, game_loop, dt);
		window = new psm_window(name.c_str(), X, Y, display);
		return window;
	}
}
