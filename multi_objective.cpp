#include<iostream>
#include "ilcplex\cplex.h"
#include "ilcplex\ilocplex.h"

using namespace std;

typedef IloArray<IloNumVarArray> 2dNumVarArray
typedef IloArray<2dNumVarArray>  3dNumVarArray
typedef IloArray<3dNumVarArray>  4dNumVarArray


int main()
{ 
  //input parameter  
  
  //Set environment and type
  IloEnv myenv;
  IloModel mymodel(myenv);
  4dNumVarArray x(myenv,n);
  for(int i=0;i<n;i++)
  {
    x[i]=3dNumVarArray(myenv,n);
    for(int j=0;j<n;j++)
    {
        x[i][j]=2dNumVarArray(myenv,k);
        for(int k=0;k<n;k++)
        {
            x[i][j][k]=IloNumVarArray()
            for(int t=0;t<T;t++)
            {
                x[i][j][k][t].setType(ILOINT);
                x[i][j][k][t].setBounds(0,1);

            }
        }
    }
  }

}



