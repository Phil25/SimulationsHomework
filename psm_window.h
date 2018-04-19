#include <GL/glut.h>
#include <math.h>
#include <cstring>
#include <vector>
#include <string>

#define PI 3.1415926535f
#define PI2 6.28318530718f
#define PI05 1.57079632679f
#define sinf(x) (double)sin((double)(x))
#define cosf(x) (double)cos((double)(x))

struct vec2{
	double x, y;
};

class psm_window{
private:
	const int X, Y;

	const double line_diff = 24;
	double line_offset;

	const double vector_arrow = 15;

	const double scale = 1;

public:
	vec2 offset = {0, 0};

public:
	psm_window(const char* name, const unsigned int x, const unsigned int y, const double scale);
	void input(void (*key_event)(unsigned char, int, int)) const;
	void loop(void (*display)(void)) const;

	void draw_line(const vec2&, const vec2&) const;

	void draw_vector(const vec2&, const vec2& direction);

	void draw_square(const vec2&, double len) const;

	void draw_circle(const vec2&, double rad, int quality=0) const;
	void draw_circle(const vec2&, double rad, double roll, int quality=0) const;

	void println(const std::string);
	void draw_text(const vec2&, const char*) const;
	void draw_text(const vec2&, const std::string&) const;
	void draw_text_offset(const vec2&, const std::string&) const;
	void reload_print();

	void draw_graph(const std::vector<vec2>& vecs) const;
	void draw_path(const std::vector<vec2>& vecs) const;

	static double get_vector_length(const vec2&);
	static double get_vector_distance(const vec2&, const vec2&, bool squared=false);
	static vec2 normalize_vector(const vec2&);
	static vec2 get_direction(const vec2&, const vec2&, bool normalized=true);

private:
	void init() const;
	void draw(const vec2&, const vec2&) const;
	vec2 get_circle_vec2(const vec2&, double rad, double ang) const;

};
