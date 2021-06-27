#include "FillMatrices.h"
#include "Matrix.h"
#include "csv.h"
#include <vector>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <iostream>
 



double string_to_double( const std::string& s )
{
	std::istringstream i(s);
	double x;
	if (!(i >> x))
		return 0;
	return x;
} 

void readData(Matrix<double>& data,string fileName)
{
	char tmp[20];
	ifstream file (strcpy(tmp, fileName.c_str()));
	Csv csv(file);
	string line;
	if (file.is_open())
	{
		int i=0;
		while (csv.getline(line) != 0) {
         	for (int j = 0; j < csv.getnfield(); j++)
            {
               double temp=string_to_double(csv.getfield(j));
               //cout << "Asset " << j << ", Return "<<i<<"="<< temp<<"\n";
               data.SetElement(j,i,temp);
            }
            i++;
		}		
		file.close();
	}
	else {cout <<fileName <<" missing\n";exit(0);}
                                                                 }

void calculateReturns(Matrix<double>& average_returns, Matrix<double> data, int numberAssets, int start_date, int end_date)
{
	for (int i=0; i<numberAssets; i++)
	{
		double mean=0.0;
		for (int n=start_date; n<end_date; n++)
		{
			mean+=data.GetElement(i,n)/(end_date-start_date);
		}
		average_returns.SetElement(i,0,mean);
	}
}

void calculateCovariance(Matrix<double>& covariance, Matrix<double> data, Matrix<double> average_returns, int numberAssets, int start_date, int end_date)
{
	for (int i=0; i<numberAssets; i++)
	{
		for (int j=0; j<=i; j++)
		{
			double cov=0.0;
			for (int n=start_date; n<end_date; n++)
			{
				cov+=(data.GetElement(i,n)-average_returns.GetElement(i,0))*(data.GetElement(j,n)-average_returns.GetElement(j,0))/(end_date-start_date-1);
			}
			covariance.SetElement(i,j,cov);
			covariance.SetElement(j,i,cov);
		}
	}
	
}

void calculateMatrix(Matrix<double>& matrix, int rows, double value)     //general function that fills a matrix with the same value
{
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<1; j++)
		{
			matrix.SetElement(i,j,value);
		}
	}
}

void calc_cum_returns(vector<vector<double> >& out_of_sample_returns,Matrix<double> data, int numberAssets, int start_date, int end_date)
{
	for (int i=0; i<numberAssets; i++)
	{
		double product=1.0;
		for (int n=start_date; n<end_date; n++)
		{
			product*=(1+data.GetElement(i,n));
		}
		out_of_sample_returns[0][i]=product-1;      //cumulative return (1+r1)(1+r2)-1
	}
}

