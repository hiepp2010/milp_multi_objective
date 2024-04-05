#include<iostream>
#include "ilcplex\cplex.h"
#include "ilcplex\ilocplex.h"

using namespace std;

typedef IloArray<IloNumVarArray> 2dNumVarArray
typedef IloArray<2dNumVarArray>  3dNumVarArray
typedef IloArray<3dNumVarArray>  4dNumVarArray


int main()
{ 
  //Set environment and type
  IloEnv myenv;
  IloModel mymodel(myenv);

  //input parameter  

  //variable
  4dNumVarArray x(myenv,N);
  4dNumVarArray y(myenv,N);
  IloNumVarArray A(myenv, K, 0, IloInfinity, ILOFLOAT);
  IloNumVarArray B(myenv, D, 0, IloInfinity, ILOFLOAT);
  3DNumVarArray VisTruck(myenv, D);
  3DNumVarArray VisDrone(myenv, D);
  

  // 2
  for (int i = 0; i < N; i++)
  {
    x[i]=3dNumVarArray(myenv,N);
    for(int j=0;j<N;j++)
    {
        x[i][j]=2dNumVarArray(myenv,K);
        for(int k=0;k<K;k++)
        {
            x[i][j][k] = IloNumVarArray(myenv, T, 0, 1, ILOINT);
        }
    }
  }

  //3
  for(int i=0;i<N;i++)
  {
    y[i]=3dNumVarArray(myenv,N);
    for(int j=0;j<N;j++)
    {
        y[i][j]=2dNumVarArray(myenv,K);
        for(int k=0;k<D;k++)
        {
            y[i][j][k] = IloNumVarArray(myenv, R, 0, 1, ILOINT);
        }
    }
  }

  //4
  for (int i = 0; i < K;i++)
  {
      A[i].setBounds(0, IloInfinity);
  }

  //5
  for (int i = 0; i < D;i++)
  {
      B[i].setBounds(0, IloInfinity);
  }

  //6
  for (int i = 0; i < D;i++)
  {
    VisDrone[i]=2dNumVarArray(myenv,R);
    for(int j=0;j<R;j++)
    {
        VisDrone[i][j] = IloNumVarArray(myenv, N, 0, IloInfinity, ILOFLOAT);
    }
  }

  for (int i = 0; i < K;i++)
  {
    VisTruck[i] = IloNumVarArray(myenv, N, 0, IloInfinity, ILOFLOAT);
  }

  //7
  for (int i = 0; i < K;i++)
  {
      IloExpr leftExpr(myenv);
      for (int j = 0; j < T;j++)
      {
          for (int k = 0; k < N;k++)
          {
              leftExpr += x[i][j][0][k];
          }
      }

      IloExpr rightExpr(myenv);
      for (int j = 0; j < T;j++)
      {
          for (int k = 0; k < N;k++)
          {
              rightExpr += x[i][j][k][N - 1];
          }
      }
      mymodel.add(IloRange(myenv, rightExpr, leftExpr, rightExpr));
  }

  //8
  for (int i = 0; i < K;i++)
  {
      IloExpr ifExpr(myenv);
      for (int j = 0; j < T;j++)
      {
          for (int k = 0; k < N;k++)
          {
              ifExpr += x[i][j][0][k];
              
          }
      }

      IloExpr thenExpr(myenv);
      for (int j = 0; j < T;j++)
      {
          for (int k = 0; k < N;k++)
          {
              for (int t = 0; t < N;t++)
                  thenExpr += x[i][j][k][t];
          }
      }
      mymodel.add(IloIfThen(myenv, ifExpr==0, thenExpr==0));
  }

  //9
  for (int i = 0; i < K;i++)
  {
      IloExpor leftExpr(myenv);
      for (int j = 0; j < T;j++)
      {
          for (int k = 0; k < N;k++)
          {
              leftExpr += x[i][j][0][k];
          }
      }
      mymodel.add(IloRange(myenv,0,leftExpr,1));
  }

  //10
  for (int i = 0; i < D;i++)
  {
      
      for (int j = 0; j < R;j++)
      {
       IloExpr leftExpr(myenv);
       for (int k = 0; k < N;k++)
       {
           leftExpr += y[i][j][0][k];
       }

       IloExpr rightExpr(myenv);
       for (int k = 0; k < N;k++)
       {
           rightExpr += y[i][j][k][N-1];
       }
       mymodel.add(IloRange(myenv, rightExpr, leftExpr, rightExpr));
      }
  }

  //11
  for (int i = 0; i < D;i++)
  {
      for (int j = 0; j < R;j++)
      {
         IloExpr ifExpr(myenv);
        for (int k = 0; k < N;k++)
        {
              ifExpr += y[i][j][0][k];
              
        }

         IloExpr thenExpr(myenv);
         for (int k = 0; k < N;k++)
          {
              for (int t = 0; t < N;t++)
                  thenExpr += y[i][j][k][t];
          }
        mymodel.add(IloIfThen(myenv, ifExpr==0, thenExpr==0));
      }
  }

  //12
  for (int i = 0; i < D;i++)
  {
      for (int j = 0; j < R;j++)
      {
          IloExpor leftExpr(myenv);
          for (int k = 0; k < N;k++)
          {
              leftExpr += y[i][j][0][k];
          }
      }
      mymodel.add(IloRange(myenv,0,leftExpr,1));
  }

}



