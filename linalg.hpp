/* the linear algebra classes (vector and matrix) */

#include "number.hpp"
#include <vector>
#include <cassert>

class matrix;

class vector {
    public:
	std::vector< number > v_vec;

	vector (int );
	vector (const std::vector<number> &);
	
	friend vector operator+(const vector &v1, const vector &v2);
	friend vector operator-(const vector &v1, const vector &v2);
	
	friend vector operator*(const vector &v, const number &n);
	friend vector operator*(const number &n, const vector &v);
	
	friend vector operator*(const vector &v, const matrix &m);
	friend vector operator*(const matrix &m, const vector &v);

	friend bool operator ==(const vector &v1, const vector &v2);
	friend bool operator !=(const vector &v1, const vector &v2);
	number operator*(const vector &v) const;	
};

class matrix {
    public: 
	std::vector<vector> m_vec;

	matrix (int a, int b);
	matrix (const std::vector<vector> &);
	
	friend matrix operator +(const matrix &m1, const matrix &m2);
	friend bool operator ==(const matrix &m1, const matrix &m2);
	friend bool operator !=(const matrix &m1, const matrix &m2);

	vector row ( int n ) const;
	vector col ( int n ) const;
	void gauss();
	number det() const;
	int rank() const;
	matrix inv() const;
};

void echelon(std::vector<vector> &v, unsigned r, unsigned c);
