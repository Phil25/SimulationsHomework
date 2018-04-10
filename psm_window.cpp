#include "psm_window.h"

psm_window::psm_window(const char* name, const unsigned int x, const unsigned int y):
X(x),
Y(y),
line_offset(Y)
{
	glutInitWindowSize(X, Y);
	glutCreateWindow(name);
	init();
}

void psm_window::loop(void (*display)(void)) const{
	glutDisplayFunc(display);
	glutMainLoop();
}

// private

void psm_window::init() const{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, X, 0, Y);
}

void psm_window::draw(const vec2& p1, const vec2& p2) const{
	glVertex2f(offset.x +p1.x, offset.y +p1.y);
	glVertex2f(offset.x +p2.x, offset.y +p2.y);
}

vec2 psm_window::get_circle_vec2(const vec2& o, float r, float ang) const{
	return vec2{o.x + r *cos(ang), o.y + r *sin(ang)};
}

// public

void psm_window::draw_line(const vec2& p1, const vec2& p2) const{
	glBegin(GL_LINES);
	draw(p1, p2);
	glEnd();
}

void psm_window::draw_vector(const vec2& o, const vec2& dir){
	vec2 o2{o.x +dir.x, o.y +dir.y};
	this->draw_line(o, o2);
	this->draw_square(vec2{o2.x -4, o2.y -4}, 8);
}

void psm_window::draw_square(const vec2& a, float len) const{
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

void psm_window::draw_circle(const vec2& o, float r, int q) const{
	this->draw_circle(o, r, 0.0f, q);
}

void psm_window::draw_circle(const vec2& o, float r, float roll, int q) const{
	glBegin(GL_LINES);
	q = q < 50 ? 32 : q;
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

void psm_window::println(const std::string text){
	line_offset -= line_diff;
	vec2 pos = {0, line_offset};
	this->draw_text(pos, text);
}

void psm_window::draw_text(const vec2& pos, const char* text) const{
	glRasterPos2f(pos.x, pos.y);
	int len = std::strlen(text);
	for(int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}

void psm_window::draw_text(const vec2& pos, const std::string& text) const{
	this->draw_text(pos, text.c_str());
}

void psm_window::draw_text_offset(const vec2& pos, const std::string& text) const{
	this->draw_text(vec2{pos.x +offset.x, pos.y +offset.y}, text.c_str());
}

void psm_window::reload_print(){
	line_offset = Y;
}

void psm_window::draw_graph(const std::vector<vec2>& vecs) const{
	int len = vecs.size();
	if(len < 1) return;
	for(int i = 1; i < len; i++)
		this->draw_line(vecs[i], vecs[i-1]);
}

void psm_window::draw_path(const std::vector<vec2>& vecs) const{
	int len = vecs.size();
	if(len < 1) return;
	for(int i = 1; i < len; i++)
		this->draw_circle(vecs[i], 2, 4);
}

// static

float psm_window::get_vector_length(const vec2& v){
	return std::sqrt(v.x*v.x + v.y*v.y);
}

float psm_window::get_vector_distance(const vec2& v1, const vec2& v2, bool squared){
	float dx = v2.x -v1.x;
	float dy = v2.y -v1.y;
	float result = dx*dx + dy*dy;
	return squared ? result : std::sqrt(result);
}

vec2 psm_window::normalize_vector(const vec2& v){
	float len = psm_window::get_vector_length(v);
	return vec2{v.x/len, v.y/len};
}

vec2 psm_window::get_direction(const vec2& p1, const vec2& p2, bool normalized){
	vec2 dir = {p2.x -p1.x, p2.y -p1.y};
	return normalized ? psm_window::normalize_vector(dir) : dir;
}
