#include <array>

#ifndef GRID_H
#define GRID_H


template <int S>
class grid{

public:
	std::array<double, S*S> arr;
	double& at(int x, int y){
		return arr[x*S +y];
	}

	inline double& operator()(int x, int y){
		return at(x, y);
	}

	inline void operator()(int x, int y, double set){
		at(x, y) = set;
	}

private:
	inline bool in_bounds(int x){
		return x >= 0 && x < S;
	}
	inline int wrap_clamp(int val){
		return (val >= S) ? 0 : (val < 0) ? S-1 : val;
	}

};


#endif
