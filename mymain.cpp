#include "FillMatrices.h"
#include "Matrix.h"
#include "Equation.h"
#include "operations.h"
#include "Conjugate.h"
#include <vector>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "csv.h"
#include <iostream>
using namespace std;




int main()
{
    int numberAssets=83;
    int numberReturns=700;
	Matrix<double> myData;
	myData.SetMatrix(numberAssets,numberReturns);	
    //read the data from the file and store it into the matrix(vector of vectors) of double
    string fileName="asset_returns.csv";
	readData(myData,fileName);	
	
	//now we will initialize all the matrices,vectors that we will use inside the loops
	//begin with the matrices that are in the Q
	Matrix<double> average_returns;    //matrix for taking in-sample returns
	average_returns.SetMatrix(numberAssets,1);
	
	Matrix<double> covariance;       //matrix for taking in-sample covariances
	covariance.SetMatrix(numberAssets,numberAssets);
	
	Matrix<double> e;    //Matrix e with 1. it is the (1,3) and (3,1) elements of Q
	e.SetMatrix(numberAssets,1);
	calculateMatrix(e,numberAssets,1.0);
	
	Matrix<double> zero;    //even the scalars are in matrices form. this is the elements (2,2) (2,3) (3,2) (3,3)
	zero.SetMatrix(1,1);
	calculateMatrix(zero,1,0.0);
	
	Matrix<vector<vector<double> > > myQ;    //we will calculate Q inside the loops
	myQ.SetMatrix(3,3);
		
	Matrix<double> ones;     //scalar with -1. this is the (3,1) element of b
	ones.SetMatrix(1,1);
	calculateMatrix(ones,1,-1.0);
	
	Matrix<double> zeros;     //matrix with zeros. (1,1) element of b
	zeros.SetMatrix(numberAssets,1);
	calculateMatrix(zeros,numberAssets,0.0);
		
	Matrix<double> targets;   //scalar with the target returns. (1,2) element of b
	targets.SetMatrix(1,1);
	
	Matrix<vector<vector<double> > > myb;   //this is b Matrix
	myb.SetMatrix(3,1);
		
	Matrix<vector<vector<double> > > guess; //matrix with initial guess
	guess.SetMatrix(3,1);
		
	Matrix<vector<vector<double> > > eq1;  //b-Qxo Matrix will be stored in this variable
	eq1.SetMatrix(3,1);
	
	Eq1 myEq;        //class that inherits Equation class. I will use it to get the b-Qxo expression
	Conjugate my_Conj;   //class that implements the conjugate gradient method algorithm
	
	
	//the following matrices and vectors are useful for backtesting
	vector<vector<double> > out_of_sample_cum_returns;         //Here I will store the cumulative returns in the out-of-sample period
	out_of_sample_cum_returns.resize(1);
    for(int n=0; n<1; n++) out_of_sample_cum_returns[n].resize(numberAssets);
	
	Matrix<double> out_of_sample_average_returns;        //Matrix for average returns of all assets in the out-of-sample period. Needed for the calculation of covariance
	out_of_sample_average_returns.SetMatrix(numberAssets,1);	
	
	Matrix<double> out_of_sample_covariance;           //Matrix for storing the covariance of all assets in the out-of-sample period
	out_of_sample_covariance.SetMatrix(numberAssets,numberAssets);
	
	vector<vector<double> > final_returns_vector;       //the two final vectors of total returns and covariances of all portfolios
	vector<vector<double> > final_cov_vector;
	
	int start_date=0;
	int in_sample_days=100;	
	int out_of_sample_days=12;	
	
	double portfolio_return;       //total return of portfolio in each period
	double portfolio_std;	       //total std of portfolio in each period
	
	for (double i=0.0; i<=0.1; i+=0.005)   //20 portfolios with target returns from 0.0 to 10%(not included). 
	{
		vector<double> ret;      //storing the total returns of portfolio in each period    !Generally initializing inside a loop is dangerous
		vector<double> cov;      //storing the total std of portfolio in each period
		for (int j=start_date; j<numberReturns-in_sample_days; j=j+out_of_sample_days)
		{
			calculateReturns(average_returns,myData,numberAssets,j,j+in_sample_days);	
            calculateCovariance(covariance,myData,average_returns,numberAssets,j,j+in_sample_days);			
			myQ=myEq.GetQ(covariance, average_returns, e, zero);      //I get the Q
			
			guess.SetElement(0,0,e.GetMatrix());      //in each loop i set again the guess. It has a vector of one in the first element and a scalar of -1 in the other two
	        guess.SetElement(1,0,ones.GetMatrix());
	        guess.SetElement(2,0,ones.GetMatrix());		
		
			calculateMatrix(targets,1,i);
			myb=myEq.Getb(zeros,targets,ones);    //I get the b
			
			eq1=myEq.equation(myQ,myb,guess);    //I get the b-Qxo
			
			my_Conj.algorithm(eq1,myQ,guess);    //solve the optimization
			
			//following lines in comments print out the weights of first,second and third asset. Only for asset_returns_small file
			//cout<<guess.GetMatrix()[0][0][0][0]<<endl;
			//cout<<guess.GetMatrix()[0][0][1][0]<<endl;
			//cout<<guess.GetMatrix()[0][0][2][0]<<endl;
			
			
			calc_cum_returns(out_of_sample_cum_returns,myData,numberAssets,j+in_sample_days,j+in_sample_days+out_of_sample_days);  //out-of-sample backtesting
			portfolio_return=matrix_multiplication(out_of_sample_cum_returns,guess.GetMatrix()[0][0])[0][0];  //r*w
			ret.push_back(portfolio_return);
			
			calculateReturns(out_of_sample_average_returns,myData,numberAssets,j+in_sample_days,j+in_sample_days+out_of_sample_days);
			calculateCovariance(out_of_sample_covariance,myData,out_of_sample_average_returns,numberAssets,j+in_sample_days,j+in_sample_days+out_of_sample_days);
			portfolio_std=matrix_multiplication(transpose(guess.GetMatrix()[0][0]),matrix_multiplication(out_of_sample_covariance.GetMatrix(),guess.GetMatrix()[0][0]))[0][0]; //w^T*sigma*w
			cov.push_back(portfolio_std);
			
		}
		final_returns_vector.push_back(ret);
		final_cov_vector.push_back(cov);
		
	}	
	
	std::ofstream myfile;
	myfile.open ("returns.csv");
	double k=0.0;
	for (int i=0; i<final_returns_vector.size(); i++) //20
	{
		myfile<< "Portfolio "<<i+1<<",";
		myfile<< "Target "<< k<<"%,";
		for (int j=0; j<final_returns_vector[0].size(); j++) //50
		{
			myfile<<final_returns_vector[i][j]<<",";
		}
		myfile<<"\n";
		k+=0.5;
	}
    myfile.close();
	
	std::ofstream myfile2;
	myfile2.open ("cov.csv");
	double l=0.0;
	for (int i=0; i<final_cov_vector.size(); i++) //20
	{
		myfile2<< "Portfolio "<<i+1<<",";
		myfile2<< "Target "<< l<<"%,";
		for (int j=0; j<final_cov_vector[0].size(); j++) //50
		{
			myfile2<<final_cov_vector[i][j]<<",";
		}
		myfile2<<"\n";
		l+=0.5;
	}
    myfile2.close();
	
	
	
	
	return 0;
}




