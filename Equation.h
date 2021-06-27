#ifndef Equation_h
#define Equation_h
#include "Matrix.h"
#include "operations.h"
#include "csv.h"

class Equation
{
   public:
	  virtual Matrix<vector<vector<double> > > equation(Matrix<vector<vector<double> > > Q, Matrix<vector<vector<double> > > b,Matrix<vector<vector<double> > > guess)=0;
};

class Eq1: public Equation
{
   private:
	  Matrix<vector<vector<double> > > Q;
	  Matrix<vector<vector<double> > > b;
   public:
      Matrix<vector<vector<double> > > GetQ(Matrix<double> covariance, Matrix<double> returns, Matrix<double> e, Matrix<double> zero );
	  
      Matrix<vector<vector<double> > > Getb(Matrix<double> zeros, Matrix<double> targets, Matrix<double> ones);
	  
	  Matrix<vector<vector<double> > > equation(Matrix<vector<vector<double> > > Q, Matrix<vector<vector<double> > > b,Matrix<vector<vector<double> > > guess);
	  
};





#endif