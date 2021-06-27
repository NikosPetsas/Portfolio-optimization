#ifndef operations_h
#define operations_h
#include "Matrix.h"
#include "FillMatrices.h"
#include <vector>
#include "Equation.h"

vector<vector<double> > matrix_multiplication(vector<vector<double> > Mat1, vector<vector<double> > Mat2 );
vector<vector<double> > matrix_adder(vector<vector<double> > Mat1, vector<vector<double> > Mat2);
Matrix<vector<vector<double> > > matrix_of_matrix_multiplication(Matrix<vector<vector<double> > > Mat1, Matrix<vector<vector<double> > > Mat2);
Matrix<vector<vector<double> > > matrix_of_matrix_adder(Matrix<vector<vector<double> > > Mat1, Matrix<vector<vector<double> > > Mat2);
vector<vector<double> > matrix_scalar_multiplication(vector<vector<double> > Mat1, double x);
Matrix<vector<vector<double> > > matrix_of_matrix_scalar_multiplication(Matrix<vector<vector<double> > > Mat1, double x);
vector<vector<double> > transpose(vector<vector<double> > Mat1);




#endif