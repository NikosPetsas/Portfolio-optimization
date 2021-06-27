#ifndef FillMatrices_h
#define FillMatrices_h
#include "Matrix.h"
#include <vector>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "csv.h"

double string_to_double( const std::string& s );
void readData(Matrix<double>& data,string fileName);
void calculateReturns(Matrix<double>& average_returns, Matrix<double> data, int numberAssets, int start_date,int end_date);
void calculateCovariance(Matrix<double>& covariance, Matrix<double> data, Matrix<double> average_returns, int numberAssets, int start_date, int end_date);
void calculateMatrix(Matrix<double>& matrix, int rows, double value);
void calc_cum_returns(vector<vector<double> >& out_of_sample_returns,Matrix<double> data, int numberAssets, int start_date, int end_date);


#endif