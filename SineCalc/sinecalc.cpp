#include <iostream>

#define PI 3.14159265359

const double conversion = PI/180;
const double twoPi = 2*PI;
const double halfPi = PI/2;

inline double floor(double x){
	return (int)(x > 0 ? x : x -0.99999);
}

inline double mod(double x, double div){
	return (x -div *floor(x/div));
}

// returns whether result should be inverted
int optimizeArg(double& arg){
	int flip = 1;

	// limit arg to range 0, 2PI
	arg = mod(arg, twoPi);

	// limit arg to range 0, PI
	// set the flip flag
	if(arg > PI){
		arg -= PI;
		flip *= -1;
	}

	// limit arg to range 0, PI/2
	if(arg > halfPi){
		arg -= 2*(arg -halfPi);
	}

	// return the flip flag
	return flip;
}

double sin(double arg, int precision){
	int flip = optimizeArg(arg);
	double result = 0.0;

	// starting values
	int add = 1;
	double power = arg;
	double factorial = 1;

	for(int i = 0; i < precision; i++){

		// add to result
		result += add*(power/factorial);

		// toggle between 1 and -1
		add *= -1;

		// next power = this * arg * arg
		power *= arg *arg;

		// get the next odd factorial		// as it apears in formula:
		int val = i*2;						// i*2 +1
		factorial *= (val +2) *(val +3);	// (val +1) *(val +2)
	}

	return result *flip;
}

int main(){

	int option = 1;
	int precision = 1;
	double argument = 1.0;

	// read radians/degrees option
	std::cout << "Use (1) radians or (2) degrees? [1/2] ";
	std::cin >> option;
	std::cout << "Chose " << (option == 1 ? "radians" : "degrees") << "." << std::endl;

	// read argument and precision
	std::cout << "Enter X and precison value:" << std::endl;
	std::cin >> argument >> precision;
	double radians = argument;

	// convert to radians
	if(option == 2)
		radians *= conversion;

	// calculate
	std::cout << "sin(" << argument << ") = " << sin(radians, precision) << std::endl;

	// stress test
	if(false){
		int i = -10;
		while(i < 10){
			std::cout << "sin(" << i << ") = " << sin(i, 6) << std::endl;
			i++;
		}
	}

	return 0;
}

// legacy testing code
/*double pow(double x, int exp){
	double result = 1;
	while(exp-- > 0)
		result *= x;
	return result;
}

int fact(int x){
	int result = 1;
	while(x > 0)
		result *= x--;
	return result;
}*/
