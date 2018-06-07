#include <vector>
#include <ostream>

#ifndef MATRIX_H
#define MATRIX_H


class matrix{
	const size_t size;
	std::vector<double> grid;
	std::vector<double> sols;

public:
	matrix(size_t size);
	matrix(size_t size, const std::vector<double>& input);

	double& at(int x, int y);
	const double& at(int x, int y) const;

	double& sol(int i);
	const double& sol(int i) const;
	const std::vector<double>& get_sols() const;

	bool is_valid(size_t x, size_t y) const;

	double& operator()(int x, int y);
	const double& operator()(int x, int y) const;
	void operator()(int x, int y, double set);

	matrix operator*(double) const;
	matrix operator/(double) const;

	void swap_row(int row1, int row2);
	void mul_row(int row, double mul);
	void add_row(int to, int row, double mul);

	void flip();
	void transpose();
	void decompose();

private:
	inline int offset(int x, int y) const;

public:
	static void flip(matrix& m);
	static void transpose(matrix& m);
	static void decompose(matrix& m);

	friend std::ostream& operator<<(std::ostream&, const matrix&);

};


#endif
