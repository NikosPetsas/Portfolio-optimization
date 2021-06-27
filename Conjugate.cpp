#include <iostream>
#include "Matrix.h"
#include "operations.h"
#include "Conjugate.h"
#include <vector>
#include <cmath>
using namespace std;


void Conjugate::algorithm(Matrix<vector<vector<double> > > s,Matrix<vector<vector<double> > > Q,Matrix<vector<vector<double> > >& x)
{
	Matrix<vector<vector<double> > > s_hat;    //i choose arbitrary how to fill s_hat
	s_hat.SetMatrix(1,3);
	s_hat.SetElement(0,0,transpose(s.GetElement(0,0)));
	s_hat.SetElement(0,1,s.GetElement(1,0));
	s_hat.SetElement(0,2,s.GetElement(2,0));
	
	Set_p_Matrix(3,1);
	Setp(s);
	
	Matrix<vector<vector<double> > > p_hat;
	p_hat.SetMatrix(1,3);
	p_hat=s_hat;
	
	Matrix<vector<vector<double> > > s_hat_previous;
	s_hat_previous.SetMatrix(1,3);
	
	Matrix<vector<vector<double> > > s_previous;
	s_previous.SetMatrix(3,1);
	
	while (abs(matrix_of_matrix_multiplication(s_hat,s).GetElement(0,0)[0][0])>=0.00001)
	{
		Setalpha(matrix_of_matrix_multiplication(s_hat,s).GetElement(0,0)[0][0]/(matrix_of_matrix_multiplication(matrix_of_matrix_multiplication(p_hat,Q),Getp()).GetElement(0,0)[0][0]));
		
		x.Set_all_Elements(matrix_of_matrix_adder(x,matrix_of_matrix_scalar_multiplication(Getp(),Getalpha())).GetMatrix());
		
		s_previous=s;
		
		s.Set_all_Elements(matrix_of_matrix_adder(s,matrix_of_matrix_scalar_multiplication(matrix_of_matrix_multiplication(Q,Getp()),Getalpha()*(-1))).GetMatrix());
		
		s_hat_previous=s_hat;
		
		s_hat.Set_all_Elements(matrix_of_matrix_adder(s_hat,matrix_of_matrix_scalar_multiplication(matrix_of_matrix_multiplication(p_hat,Q),Getalpha()*(-1))).GetMatrix());
		
		Setbeta(matrix_of_matrix_multiplication(s_hat,s).GetElement(0,0)[0][0]/(matrix_of_matrix_multiplication(s_hat_previous,s_previous).GetElement(0,0)[0][0]));
		
		Setp(matrix_of_matrix_adder(s,matrix_of_matrix_scalar_multiplication(Getp(),Getbeta())));
		
		p_hat.Set_all_Elements(matrix_of_matrix_adder(s_hat,matrix_of_matrix_scalar_multiplication(p_hat,Getbeta())).GetMatrix());
	
		
		
	}
	//return x;
}

