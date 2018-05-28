#include <array>

#ifndef GRID_H
#define GRID_H


template <int S>
class grid{
	std::array<std::array<double, S>, S> arr;

public:
	double& operator()(int x, int y){
		x = wrap_clamp(x);
		y = wrap_clamp(y);
		return arr[x][y];
	}

	void operator()(int x, int y, double set){
		this->operator()(x, y) = set;
	}

private:
	inline int wrap_clamp(int val){
		return (val >= S) ? 0 : (val < 0) ? S-1 : val;
	}

};


#endif
