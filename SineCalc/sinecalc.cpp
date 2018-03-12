#include <iostream>

#define PI 3.14159265359

const double twoPi = 2*PI;
const double halfPi = PI/2;
const double quarterPi = halfPi/2;

double floor(double x){
	return (int)(x > 0 ? x : x -0.99999);
}

double mod(double x, double div){
	return (x -div *floor(x/div));
}

void optimizeArg(double& arg){
	arg = mod(arg, PI);
}

double sin(double arg, int precision){
	optimizeArg(arg);
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

	return result;
}

int main(){
	double argument;
	int precision;

	std::cout << "Enter X and precison value:" << std::endl;
	std::cin >> argument >> precision;
	std::cout << "sin(" << argument << ") = " << sin(argument, precision) << std::endl;

	return 0;
}

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
