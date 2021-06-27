#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include "Matrix.h"
#include "csv.h"
using namespace std;

vector<vector<double> > matrix_multiplication(vector<vector<double> > Mat1, vector<vector<double> > Mat2 )
{
	
	vector<vector<double> > Mat3;
	Mat3.resize(Mat1.size());
	
    for(int n=0; n<Mat1.size(); n++) Mat3[n].resize(Mat2[0].size());
	for (int i = 0; i < Mat1.size(); i++)
    {		
		for (int j = 0; j < Mat2[0].size() ; j++)   
        {
			Mat3[i][j] = 0;
            for (int k = 0; k < Mat2.size(); k++)
		    {
				Mat3[i][j] += Mat1[i][k] * Mat2[k][j];
			}
        }
    }
	return Mat3;
}

vector<vector<double> > matrix_adder(vector<vector<double> > Mat1, vector<vector<double> > Mat2)
{   
    vector<vector<double> > Mat3;
	Mat3.resize(Mat1.size());
    for(int n=0; n<Mat1.size(); n++) Mat3[n].resize(Mat1[0].size());	
    
    for ( int i = 0 ; i < Mat1.size() ; i++ )
    {
     
		for (int j = 0 ; j < Mat1[i].size() ; j++ )
        {
            
			Mat3[i][j] = Mat1[i][j] + Mat2[i][j] ;
			
        }
    }

    return Mat3;
}

Matrix<vector<vector<double> > > matrix_of_matrix_multiplication(Matrix<vector<vector<double> > > Mat1, Matrix<vector<vector<double> > > Mat2)
{
	Matrix<vector<vector<double> > > Mat3;
	Mat3.SetMatrix(Mat1.GetMatrix().size(),Mat2.GetMatrix()[0].size());
	
	for (int i = 0; i < Mat1.GetMatrix().size(); i++)
    {
		for (int j = 0; j < Mat2.GetMatrix()[i].size(); j++)
        {
			
			Mat3.SetElement(i,j,matrix_multiplication(Mat1.GetElement(i,0), Mat2.GetElement(0,j)));
			
            for (int k = 1; k < Mat2.GetMatrix().size(); k++)
		    {
				
				Mat3.SetElement(i,j,matrix_adder(Mat3.GetElement(i,j) ,matrix_multiplication(Mat1.GetElement(i,k), Mat2.GetElement(k,j))));
				
			}
			
        }
    }
	return Mat3;
}

Matrix<vector<vector<double> > > matrix_of_matrix_adder(Matrix<vector<vector<double> > > Mat1, Matrix<vector<vector<double> > > Mat2)
{   
    Matrix<vector<vector<double> > > Mat3;
	Mat3.SetMatrix(Mat1.GetMatrix().size(),Mat1.GetMatrix()[0].size());
	
    
    for ( int i = 0 ; i < Mat1.GetMatrix().size() ; i++ )
    {
        
		
		for (int j = 0 ; j < Mat1.GetMatrix()[i].size() ; j++ )
        {
            Mat3.SetElement(i,j,matrix_adder(Mat1.GetElement(i,j), Mat2.GetElement(i,j))) ;
			
        }
    }

    return Mat3;
}


vector<vector<double> > matrix_scalar_multiplication(vector<vector<double> > Mat1, double x)
{
	vector<vector<double> > Mat2;
	Mat2.resize(Mat1.size());
    for(int n=0; n<Mat1.size(); n++) Mat2[n].resize(Mat1[0].size());
	for ( int i = 0 ; i < Mat1.size() ; i++ )
    {
        for (int j = 0 ; j < Mat1[i].size() ; j++ )
        {
            Mat2[ i ][ j ] = Mat1[ i ][ j ]*x; 
        }
    }
	return Mat2;
}

Matrix<vector<vector<double> > > matrix_of_matrix_scalar_multiplication(Matrix<vector<vector<double> > > Mat1, double x)
{
	Matrix<vector<vector<double> > > Mat2;
	Mat2.SetMatrix(Mat1.GetMatrix().size(),Mat1.GetMatrix()[0].size());
	for ( int i = 0 ; i < Mat1.GetMatrix().size() ; i++ )
    {
        for (int j = 0 ; j < Mat1.GetMatrix()[i].size() ; j++ )
        {
            
			Mat2.SetElement(i,j, matrix_scalar_multiplication(Mat1.GetElement(i,j),x)); 
			
        }
    }
	
	return Mat2;
}

vector<vector<double> > transpose(vector<vector<double> > Mat1)
{
	
	vector<vector<double> > Mat2;
	Mat2.resize(Mat1[0].size());
    for(int n=0; n<Mat2.size(); n++) Mat2[n].resize(Mat1.size());
	
	for (int i=0; i<Mat2.size(); i++)
	{
		
		for (int j=0; j<Mat2[i].size(); j++)
		{
			
			Mat2[i][j]=Mat1[j][i];
		}
	}
	
	return Mat2;
}
