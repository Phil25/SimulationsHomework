#include <string>
#include <GL/glut.h>
#include "psm_window.h"
#include <iostream>

void render(psm_window*);
void key_press(unsigned char key);

namespace psm{
	psm_window* w = nullptr;

	void key_event(unsigned char key, int x, int y){
		(void)x;
		(void)y;
		key_press(key);
	}

	void game_loop(int dt){
		glutPostRedisplay();
		glutTimerFunc(dt, game_loop, dt);
	}

	void display(void){
		glClear(GL_COLOR_BUFFER_BIT);
		render(w);
		w->reload_print();
		glFlush();
	}

	psm_window* init(std::string name, int X, int Y, float dt, const vec2& offset, const double scale){
		dt *= 1000;
		glutTimerFunc(dt, game_loop, dt);
		w = new psm_window(name.c_str(), X, Y, scale);
		w->offset = offset;
		w->input(key_event);
		w->loop(display);
		return w;
	}

	psm_window* init(std::string name, int X, int Y, float dt){
		return init(name, X, Y, dt, vec2{}, 1.0);
	}
}
