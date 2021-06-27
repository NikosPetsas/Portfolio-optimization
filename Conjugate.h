#ifndef Conjugate_h
#define Conjugate_h
#include "Matrix.h"
#include <vector>


class Conjugate
{
	private:
		Matrix<vector<vector<double> > > p;
		double alpha;
		double beta;
		
	public:
		void Set_p_Matrix(int rows_,int columns_)
		{
			p.SetMatrix(rows_,columns_);
		}
		void Setp(Matrix<vector<vector<double> > > p_)
		{
			p=p_;
		}
		void Setalpha(double alpha_)
		{
			alpha=alpha_;
		}
		void Setbeta(double beta_)
		{
			beta=beta_;
		}
		Matrix<vector<vector<double> > > Getp()
		{
			return p;
		}
		double Getalpha() 
		{
			return alpha;
		}
		double Getbeta() 
		{
			return beta;
		}
		
		void algorithm(Matrix<vector<vector<double> > > s,Matrix<vector<vector<double> > > Q,Matrix<vector<vector<double> > >& x);
};

#endif