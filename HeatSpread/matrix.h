#include <vector>
#include <ostream>

#ifndef MATRIX_H
#define MATRIX_H


class matrix{
public:
	const size_t size;
	std::vector<double> vec;
	std::vector<double> sol;
	matrix(size_t size);
	matrix(size_t size, const std::vector<double>& input);

	double& at(int x, int y);
	const double& at(int x, int y) const;

	bool is_valid(size_t x, size_t y);

	double& operator()(int x, int y);
	const double& operator()(int x, int y) const;
	void operator()(int x, int y, double set);

	matrix operator*(double) const;
	matrix operator/(double) const;

	void swap_row(int row1, int row2);
	void mul_row(int row, double mul);
	void add_row(int to, int row, double mul);
	void flip();

	double det() const;
	double qdet() const;
	matrix sub(size_t skip_row, size_t skip_col) const;
	matrix adj() const;

	void transpose();
	void decompose();

private:
	inline int offset(int x, int y) const;

public:
	static double det(const matrix& m);
	static double qdet(const matrix& m);
	static matrix sub(const matrix& m, size_t row, size_t col);
	static matrix adj(const matrix& m);

	static void transpose(matrix& m);
	static void decompose(matrix& m);

	friend std::ostream& operator<<(std::ostream&, const matrix&);

};


#endif
