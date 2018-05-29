#include <vector>
#include <ostream>

#ifndef MATRIX_H
#define MATRIX_H


class matrix{
	const size_t size;

public:
	std::vector<double> vec;
	matrix(size_t size);

	double& operator()(int x, int y);
	const double& operator()(int x, int y) const;
	void operator()(int x, int y, double set);

	matrix operator*(double) const;
	matrix operator/(double) const;

	double det() const;
	matrix sub(size_t skip_row, size_t skip_col) const;
	matrix adj() const;
	matrix transpose() const;
	matrix inv() const;

private:
	inline int offset(int x, int y) const;

public:
	static double det(const matrix& m);
	static matrix sub(const matrix& m, size_t row, size_t col);
	static matrix adj(const matrix& m);
	static matrix transpose(const matrix& m);
	static matrix inv(const matrix& m);

	friend std::ostream& operator<<(std::ostream&, const matrix&);

};


#endif
