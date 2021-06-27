#ifndef Matrix_h
#define Matrix_h

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

template<typename Type> class Matrix      //basic data structure that I use in the code
{
   private:
	  int rows;
	  int columns;
      vector< vector<Type> > myMatrix;

   public:
      void SetMatrix(int rows_,int columns_)
      {
         rows=rows_;
		 columns=columns_;
         myMatrix.resize(rows);
         for(int n=0; n<rows; n++) myMatrix[n].resize(columns);
      }
      void SetElement(int n, int i, Type x)
         {myMatrix[n][i]=x;}
      Type GetElement(int n, int i)
         {return myMatrix[n][i];}
	  void Set_all_Elements(vector<vector<Type> > myMatrix_)
	  {
		  myMatrix=myMatrix_;
	  }
	  vector<vector<Type> > GetMatrix()
	     {return myMatrix;}
	  /*
      void Display()
      {
         cout << setiosflags(ios::fixed)
              << setprecision(3);
         for(int n=0; n<rows; n++)
         {
            //for(int i=0; i<=n; i++)
            cout << setw(7) << GetElement(n,0);
            cout << endl;
         }
         cout << endl;
      }
	  */
};

#endif
