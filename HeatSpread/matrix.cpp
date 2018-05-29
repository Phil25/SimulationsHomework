#include "matrix.h"

matrix::matrix(size_t size):
	size(size),
	vec(size*size)
{}

double& matrix::operator()(int x, int y){
	return vec[offset(x, y)];
}

const double& matrix::operator()(int x, int y) const{
	return vec[offset(x, y)];
}

void matrix::operator()(int x, int y, double set){
	this->operator()(x, y) = set;
}

matrix matrix::operator*(double val) const{
	matrix result(size);
	for(size_t row = 0; row < size; row++)
		for(size_t col = 0; col < size; col++)
			result(row, col) = this->operator()(row, col) *val;
	return result;
}

matrix matrix::operator/(double val) const{
	return this->operator*(1 /val);
}

double matrix::det() const{
	return det(*this);
}

matrix matrix::sub(size_t skip_row, size_t skip_col) const{
	return sub(*this, skip_row, skip_col);
}

matrix matrix::adj() const{
	return adj(*this);
}

matrix matrix::transpose() const{
	return transpose(*this);
}

matrix matrix::inv() const{
	return inv(*this);
}

int matrix::offset(int x, int y) const{
	return x*size +y;
}

double matrix::det(const matrix& m){
	if(m.size == 1)
		return m(0, 0);

	double result = 0;
	int dir = 1;

	for(size_t i = 0; i < m.size; i++){
		result += m(0, i) *dir *det(sub(m, 0, i));
		dir = -dir;
	}

	return result;
}

matrix matrix::sub(const matrix& m, size_t skip_row, size_t skip_col){
	const size_t size = m.size -1;
	matrix subm(size);

	for(size_t row = 0; row < m.size; row++)
		if(row != skip_row)
		for(size_t col = 0; col < m.size; col++)
			if(col != skip_col)
			subm(row -(row > skip_row), col -(col > skip_col)) = m(row, col);

	return subm;
}

matrix matrix::adj(const matrix& m){
	matrix adjm(m.size);
	int posit = -1;
	for(size_t i = 0; i < m.size; i++)
		for(size_t j = 0; j < m.size; j++)
			adjm(i, j) = det(sub(m, i, j)) *(posit = -posit);
	return adjm;
}

matrix matrix::transpose(const matrix& m){
	matrix tm(m.size);
	for(size_t row = 0; row < m.size; row++)
		for(size_t col = 0; col < m.size; col++)
			tm(col, row) = m(row, col);
	return tm;
}

matrix matrix::inv(const matrix& m){
	return adj(m).transpose() /det(m);
}

std::ostream& operator<<(std::ostream& os, const matrix& m){
	for(size_t row = 0; row < m.size; row++){
		os << "| ";
		for(size_t col = 0; col < m.size; col++)
			os << m(row, col) << ' ';
		os << '|' << std::endl;
	}
	return os;
}
