#include "psm_window.h"

psm_window::psm_window(const char* name, const unsigned int x, const unsigned int y, void (*display)(void)):
X(x),
Y(y)
{
	glutInitWindowSize(X, Y);
	glutCreateWindow(name);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

void psm_window::init() const{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, X, 0, Y);
}

void psm_window::draw(const vec2& p1, const vec2& p2) const{
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
}

void psm_window::draw_line(const vec2& p1, const vec2& p2) const{
	glBegin(GL_LINES);
	draw(p1, p2);
	glEnd();
}

void psm_window::draw_square(const vec2& a, GLint len) const{
	vec2	b = {a.x +len, a.y},
			c = {b.x, b.y +len},
			d = {c.x -len, c.y};
	glBegin(GL_LINES);
	draw(a, b);
	draw(b, c);
	draw(c, d);
	draw(d, a);
	glEnd();
}

void psm_window::draw_circle(const vec2& o, GLint r, int q) const{
	this->draw_circle(o, r, 0.0f, q);
}

void psm_window::draw_circle(const vec2& o, GLint r, float roll, int q) const{
	glBegin(GL_LINES);
	const float step = PI2 /q;
	float ang = roll;
	vec2 last = get_circle_vec2(o, r, ang);
	for(int i = 0; i <= q; i++){
		vec2 p = get_circle_vec2(o, r, ang);
		draw(last, p);

		last = p;
		ang += step;
	}
	glEnd();
}

vec2 psm_window::get_circle_vec2(const vec2& o, float r, float ang) const{
	return vec2{o.x + r *cos(ang), o.y + r *sin(ang)};
}
