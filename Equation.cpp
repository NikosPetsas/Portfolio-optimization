#include "Equation.h"
#include "Matrix.h"
#include "operations.h"
#include "FillMatrices.h"
#include <iostream>
#include <vector>
using namespace std;

Matrix<vector<vector<double> > > Eq1::GetQ(Matrix<double> covariance, Matrix<double> returns, Matrix<double> e, Matrix<double> zero )
	  {
		Matrix<vector<vector<double> > > my_Q;
		my_Q.SetMatrix(3,3);
		my_Q.SetElement(0,0,covariance.GetMatrix());
		my_Q.SetElement(1,0,matrix_scalar_multiplication(transpose(returns.GetMatrix()),-1.0));
		my_Q.SetElement(0,1,matrix_scalar_multiplication(returns.GetMatrix(),-1.0));
		my_Q.SetElement(2,0,matrix_scalar_multiplication(transpose(e.GetMatrix()),-1.0));
		my_Q.SetElement(0,2,matrix_scalar_multiplication(e.GetMatrix(),-1.0));
		my_Q.SetElement(1,1,zero.GetMatrix());
		my_Q.SetElement(1,2,zero.GetMatrix());
		my_Q.SetElement(2,1,zero.GetMatrix());
		my_Q.SetElement(2,2,zero.GetMatrix());
		return my_Q;
	  } 
Matrix<vector<vector<double> > > Eq1::Getb(Matrix<double> zeros, Matrix<double> targets, Matrix<double> ones)
	  {
		Matrix<vector<vector<double> > > my_b;
		my_b.SetMatrix(3,1);
		my_b.SetElement(0,0,zeros.GetMatrix());
		my_b.SetElement(1,0,matrix_scalar_multiplication(targets.GetMatrix(),-1.0));
		my_b.SetElement(2,0,ones.GetMatrix());
		return my_b;
	  }
Matrix<vector<vector<double> > > Eq1::equation(Matrix<vector<vector<double> > > Q, Matrix<vector<vector<double> > > b,Matrix<vector<vector<double> > > guess)
	  {
		  Matrix<vector<vector<double> > > my_Eq;
		  my_Eq.SetMatrix(3,1);
		  
		  my_Eq=matrix_of_matrix_adder(b,matrix_of_matrix_scalar_multiplication(matrix_of_matrix_multiplication(Q,guess),-1.0));
		  return my_Eq;
	  }
	  

