#include "matrix.h"

void swap(double& x, double& y){
	double temp = x;
	x = y;
	y = temp;
}

matrix::matrix(size_t size):
	size(size),
	grid(size*size),
	sols(size)
{}

matrix::matrix(size_t size, const std::vector<double>& input):
	size(size),
	grid(input),
	sols(size)
{}

bool matrix::is_valid(size_t x, size_t y) const{
	return 0 <= x && x < size && 0 <= y && y < size;
}

double& matrix::at(int x, int y){
	return grid[offset(x, y)];
}

const double& matrix::at(int x, int y) const{
	return grid[offset(x, y)];
}

double& matrix::sol(int i){
	return sols[i];
}

const double& matrix::sol(int i) const{
	return sols[i];
}

const std::vector<double>& matrix::get_sols() const{
	return sols;
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
	swap(sol(row1), sol(row2));
}

void matrix::mul_row(int row, double mul){
	for(size_t i = 0; i < size; i++)
		at(row, i) *= mul;
	sol(row) *= mul;
}

void matrix::add_row(int to, int row, double mul){
	for(size_t i = 0; i < size; i++)
		at(to, i) += at(row, i) *mul;
	sol(to) += sol(row) *mul;
}

void matrix::flip(){
	flip(*this);
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

void matrix::flip(matrix& m){
	size_t half = m.size /2;
	for(size_t row = 0; row < half; row++)
		m.swap_row(row, m.size -row -1);
}

void matrix::transpose(matrix& m){
	for(size_t row = 0; row < m.size; row++)
		for(size_t col = row; col < m.size; col++)
			swap(m(row, col), m(col, row));
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
		os << "| " << m.sol(row) << std::endl;
	}
	return os;
}
