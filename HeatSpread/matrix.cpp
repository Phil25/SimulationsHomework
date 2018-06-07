#include "matrix.h"
#include <iostream>

void swap(double& x, double& y){
	double temp = x;
	x = y;
	y = temp;
}

matrix::matrix(size_t size):
	size(size),
	vec(size*size),
	sol(size)
{}

matrix::matrix(size_t size, const std::vector<double>& input):
	size(size),
	vec(input),
	sol(size)
{}

bool matrix::is_valid(size_t x, size_t y){
	return 0 <= x && x < size && 0 <= y && y < size;
}

double& matrix::at(int x, int y){
	return vec[offset(x, y)];
}

const double& matrix::at(int x, int y) const{
	return vec[offset(x, y)];
}

double& matrix::operator()(int x, int y){
	return at(x, y);
}

const double& matrix::operator()(int x, int y) const{
	return at(x, y);
}

void matrix::operator()(int x, int y, double set){
	at(x, y) = set;
}

matrix matrix::operator*(double val) const{
	matrix result(size);
	for(size_t row = 0; row < size; row++)
		for(size_t col = 0; col < size; col++)
			result(row, col) = at(row, col) *val;
	return result;
}

matrix matrix::operator/(double val) const{
	return operator*(1 /val);
}

void matrix::swap_row(int row1, int row2){
	for(size_t i = 0; i < size; i++)
		swap(at(row1, i), at(row2, i));
	swap(sol[row1], sol[row2]);
}

void matrix::mul_row(int row, double mul){
	for(size_t i = 0; i < size; i++)
		at(row, i) *= mul;
	sol[row] *= mul;
}

void matrix::add_row(int to, int row, double mul){
	for(size_t i = 0; i < size; i++)
		at(to, i) += at(row, i) *mul;
	sol[to] += sol[row] *mul;
}

void matrix::flip(){
	size_t half = size /2;
	for(size_t row = 0; row < half; row++)
		swap_row(row, size -row -1);
}

double matrix::det() const{
	return det(*this);
}

double matrix::qdet() const{
	return qdet(*this);
}

matrix matrix::sub(size_t skip_row, size_t skip_col) const{
	return sub(*this, skip_row, skip_col);
}

matrix matrix::adj() const{
	return adj(*this);
}

void matrix::transpose(){
	transpose(*this);
}

void matrix::decompose(){
	decompose(*this);
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

double matrix::qdet(const matrix& m){
	matrix simm(m);
	double result = 1.0;

	for(size_t row = 0; row < m.size; row++){

		for(size_t next = row +1; next < m.size; next++){
			double val = -simm(next, row) /simm(row, row);
			simm.add_row(next, row, val);
		}

		result *= simm(row, row);
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

void matrix::transpose(matrix& m){
	// TODO: quickfix - fix the quickfix
	matrix transposed(m);
	for(size_t row = 0; row < m.size; row++)
		for(size_t col = 0; col < m.size; col++)
			transposed(col, row) = m(row, col);

	for(size_t row = 0; row < m.size; row++)
		for(size_t col = 0; col < m.size; col++)
			m(row, col) = transposed(row, col);
}

void matrix::decompose(matrix& m){
	size_t row = 0;

	// find upper triangular matrix
	for(; row < m.size; ++row)
		for(size_t next = row +1; next < m.size; next++){
			double val = -m(next, row) /m(row, row);
			m.add_row(next, row, val);
		}

	// eliminate upper triangular matrix
	for(--row; row > 0; --row){
		for(size_t next = row -1; next < m.size; next--){
			double val = -m(next, row) /m(row, row);
			m.add_row(next, row, val);
		}
	}

	// divide by diagonal
	for(; row < m.size; ++row)
		m.mul_row(row, 1/m.at(row, row));
}

std::ostream& operator<<(std::ostream& os, const matrix& m){
	for(size_t row = 0; row < m.size; row++){
		os << "| ";
		for(size_t col = 0; col < m.size; col++)
			os << m(row, col) << ' ';
		os << "| " << m.sol[row] << std::endl;
	}
	return os;
}
