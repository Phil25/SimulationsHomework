#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535f
#define PI2 6.28318530718f
#define PI05 1.57079632679f
#define sinf(x) (float)sin((double)(x))
#define cosf(x) (float)cos((double)(x))

struct vec2{
	float x, y;

	void add(const vec2& v){
		this->x += v.x;
		this->y += v.y;
	}
};

class psm_window{
private:
	const unsigned int X, Y;

public:
	psm_window(const char* name, const unsigned int x, const unsigned int y, void (*display)(void));

	void draw_line(const vec2&, const vec2&) const;
	void draw_vector(const vec2&, const vec2& direction);
	void draw_square(const vec2&, GLint len) const;
	void draw_circle(const vec2&, GLint rad, int quality=16) const;
	void draw_circle(const vec2&, GLint rad, float roll, int quality=16) const;

	static float get_vector_length(const vec2&);
	static vec2 normalize_vector(const vec2&);

private:
	void init() const;
	void draw(const vec2&, const vec2&) const;
	vec2 get_circle_vec2(const vec2&, float rad, float ang) const;

};
