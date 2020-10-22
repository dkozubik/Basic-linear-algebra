# Basic-linear-algebra

This class <linalg> is implemented on top of the <number> class. (Arbitrary-precision-number-class repository).
There are two other data types <vector> and <matrix>. (Note <vector> is not <std::vector>)

Methods in this class are

 • vector addition and subtraction (operators ‹+› and ‹-›),
 
 • multiplication of a vector by a scalar (from both sides, ‹*›),
 
 • dot product of two vectors (operator ‹*›),
 
 • matrix addition (operator ‹+›),
 
 • multiplication of a vector by a matrix (again ‹*›, both sides),
 
 • equality on both vectors and matrices.
 
 
 Operations for matrix (m is type of matrix):
 
 • ‹m.gauss()› performs in-place Gaussian elimination: after the
   call, ‹m› should be in a reduced row echelon form
  
 • ‹m.rank()› returns the rank of the matrix (as ‹int›)
 
 • ‹m.det()› returns the determinant of the matrix
 
 • ‹m.inv()› returns the inverse of the matrix
 
 • ‹m.row( int n )› returns the ‹n›-th row as a ‹vector›
 
 • ‹m.col( int n )› returns the ‹n›-th column as a ‹vector› 
