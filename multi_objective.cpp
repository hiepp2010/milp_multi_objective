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
  2DNumVarArray levelTruck(myenv,N);
  3DNumVarArray levelDrone(myenv,)
  

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
  for (int i = 0; i < K;i++)
  {
    VisTruck[i] = IloNumVarArray(myenv, N, 0, IloInfinity, ILOFLOAT);
  }

  //7
  for (int i = 0; i < D;i++)
  {
    VisDrone[i]=2dNumVarArray(myenv,R);
    for(int j=0;j<R;j++)
    {
        VisDrone[i][j] = IloNumVarArray(myenv, N, 0, IloInfinity, ILOFLOAT);
    }
  }

  

  //8
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

  //9
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

  //10
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

  //11
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

  //12
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

  //13
  for (int i = 0; i < D;i++)
  {
      for (int j = 0; j < R;j++)
      {
          IloExpr leftExpr(myenv);
          for (int k = 0; k < N;k++)
          {
              leftExpr += y[i][j][0][k];
          }
      }
      mymodel.add(IloRange(myenv,0,leftExpr,1));
  }

  //14
  for(int i=0;i<K;i++)
  {
      levelTruck[i] = IloNumVarArray(myenv, N, 0, IloInfinity, ILOINT);
      IloExpr leftExpr(myenv);
      leftExpr += levelTruck[i][0];
      mymodel.add(IloRange(myenv,0,leftExpr,0));
  }

  //15

  for (int i = 0; i < K;i++)
  {
       
       for (int j = 0; j < N;j++)
       {
           for (int k = 0; k <= N;k++)
           {
             IloExpr ifExpr(myenv);
             IloExpr thenExpr(myenv);
             thenExpr += x[i][t][j][k];
             mymodel.add(IloIfThen(myenv, ifExpr==1, thenExpr==1));
           }
       }
  }

  //16
  for(int i=0;i<K;i++)
  {
      levelTruck[i] = IloNumVarArray(myenv, N, 0, IloInfinity, ILOINT);
      IloExpr leftExpr(myenv);
      leftExpr += levelTruck[i][0];
      mymodel.add(IloRange(myenv,0,leftExpr,0));
  }

  //17

  for (int i = 0; i < K;i++)
  {
       
       for (int j = 0; j < N;j++)
       {
           for (int k = 0; k <= N;k++)
           {
             IloExpr ifExpr(myenv);
             IloExpr thenExpr(myenv);
             thenExpr += x[i][t][j][k];
             mymodel.add(IloIfThen(myenv, ifExpr==1, thenExpr==1));
           }
       }
  }

  //18
  for (int i = 0; i < D;i++)
  {
    VisDrone[i]=2dNumVarArray(myenv,R);
    for(int j=0;j<R;j++)
    {
        VisDrone[i][j] = IloNumVarArray(myenv, N, 0, IloInfinity, ILOFLOAT);
    }
  }

  

  //19
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

  //20
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

  //21
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

  //22
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

  //23
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
      mymodel.add(IloRange(myenv,0,leftExpr,1));
  }

  //24
  for (int k = 0; i < K;k++)
  {
      for (int j = 0; j < N;j++)
      {
          IloExpr ifExpr(myenv);
          for (int i = 1; i <= N;i++)
          {
              for (int t = 0; t <= T;t++)
              {
                  ifExpr += x[i][j][k][t];
              }
          }
          IloExpr thenExpr(myenv);
          mymodel.add(IloIfThen(myenv, ifExpr==0, thenExpr==0));
      }
  }

  //25

  //26
  for (int k = 0; k < K;k++)
  {
      for (int i = 0; i < N; i++)
      {
          for (int j = 0; j < N; j++)
          {
              for (int t = 0; t < T;t++)
              {
                IloExpr leftExpr(myenv);
                IloExpr rightExpr(myenv);
                leftExpr += Vis[k][j] - Vis[k][i] - B1 * x[k][t][i][j];
                rightExpr += gamma[t][i][j] + Serving[j] - B1;
                mymodel.add(IloRange(myenv,rightExpr,leftExpr,IloInfinity));
              }
          }
      }
  }

  //27
  for (int k = 0; k < K;k++)
  {
      for (int i = 0; i < N; i++)
      {
          for (int j = 0; j < N; j++)
          {
              for (int t = 0; t < T;t++)
              {
                IloExpr leftExpr(myenv);
                IloExpr rightExpr(myenv);
                leftExpr += Vis[k][j] + B2 * x[k][t][i][j];
                rightExpr += Time[t][i][j] + B2;
                mymodel.add(IloRange(myenv, leftExpr, rightExpr, IloInfinity));
              }
          }
      }
  }

  //28
  for (int k = 0; k < K;k++)
  {
      for (int i = 0; i < N; i++)
      {
          for (int j = 0; j < N; j++)
          {
              for (int t = 0; t < T;t++)
              {
                IloExpr leftExpr(myenv);
                leftExpr += Vis[k][i] -Time[t-1][i][j] * x[k][t][i][j];
                mymodel.add(IloRange(myenv, 0, leftExpr, IloInfinity));
              }
          }
      }
  }

  //29
  for (int k = 0; k < K;k++)
  {
      IloExpr leftExpr(myenv);
      IloExpr rightExpr(myenv);
      leftExpr += timeFinish[k];
      rightExpr += timeVisit[k][c + 1];
      mymodel.add(IloRange(myenv, rightExpr, leftExpr, rightExpr));
  }

  //30
  for (int k = 0; k < K;k++)
  {
      IloExpr leftExpr(myenv);
      IloExpr rightExpr(myenv);
      for (int i = 0; i < N;i++)
      {
          rightExpr += (timeFinish[k] - timeVisit[k][i]) * mark[k][i];
      }
      leftExpr += timeWait[k];
      mymodel.add(IloRange(myenv, rightExpr, leftExpr, rightExpr));
  }

  //31
  for (int d = 0; d <= D;d++)
  {
      for (int r = 0; r <= R;r++)
      {
          IloExpr expr(myenv);
          expr += Energyp[d][r][0];
          mymodel.add(IloRange(myenv, EnergyFull, expr, EnergyFull));
      }
  }

  //32
  for (int d = 0; d <= D;d++)
  {
      for (int r = 0; r <= R;r++)
      {
          for (int i = 0; i < N;i++)
          {
             IloExpr expr(myenv);
             expr += Energyp[d][r][i];
             mymodel.add(IloRange(myenv, 0, expr, 0));
          }
          
      }
  }

  //33
  for (int d = 0; d <= D;d++)
  {
      for (int r = 0; r <= R;r++)
      {
          for (int i = 0; i < N;i++)
          {
             IloExpr expr(myenv);
             expr += W[d][r][i];
             mymodel.add(IloRange(myenv, 0, expr, Cap));
          }
          
      }
  }

  //34
  for (int d = 0; d <= D;d++)
  {
      for (int r = 0; r <= R;r++)
      {
          for (int j = 0; j < N;j++)
          {
             IloExpr leftExpr(myenv);
             IloExpr rightExpr(myenv);
             leftExpr += timeVis[d][r][j];
             for (int i = 0; i <= N;i++)
             {
                 rightExpr += (timeVis[d][r][i]+gamma[i][j])*y[d][r][i][j]
             }
             rightExpr += Serving[j];
             mymodel.add(IloRange(myenv, rightExpr, leftExpr, rightExpr));
                 
          }
          
      }
  }

  //35
  for (int d = 0; d <= D;d++)
  {
      for (int r = 0; r <= R;r++)
      {
          for (int j = 0; j < N;j++)
          {
             IloExpr leftExpr(myenv);
             IloExpr rightExpr(myenv);
             leftExpr += w[d][r][j];
             for (int i = 0; i <= N;i++)
             {
                 rightExpr += (w[d][r][i]-weight[j])*y[d][r][i][j]
             }
             rightExpr += Serving[j];
             mymodel.add(IloRange(myenv, rightExpr, leftExpr, rightExpr));
                 
          }
          
      }
  }

  //36
  for (int d = 0; d <= D;d++)
  {
      for (int r = 0; r <= R;r++)
      {
          for (int j = 0; j < N;j++)
          {
             IloExpr leftExpr(myenv);
             IloExpr rightExpr(myenv);
             leftExpr += Energy[d][r][j];
             for (int i = 0; i <= N;i++)
             {
                 rightExpr += (Energy[d][r][i] - B[j]) * y[d][r][i][j] * gamma[i][j];
             }
             rightExpr += Serving[j];
             mymodel.add(IloRange(myenv, rightExpr, leftExpr, rightExpr));
                 
          }
          
      }
  }

  //37
  for (int d = 0; d < D;d++)
  {
      IloExpr leftExpr(myenv);
      IloExpr rightExpr(myenv);
      leftExpr += timeFinish[d];
      for (int r = 0; r < R;r++)
      {  
       rightExpr += timeVisit[k][c + 1];
      }
      mymodel.add(IloRange(myenv, rightExpr, leftExpr, rightExpr));
          
  }

  //38
  for (int k = 0; k < K;k++)
  {
      IloExpr leftExpr(myenv);
      IloExpr rightExpr(myenv);
      for (int i = 0; i < N;i++)
      {
          rightExpr += (timeFinish[k] - timeVisit[k][i]) * mark[k][i];
      }
      leftExpr += timeWait[k];
      mymodel.add(IloRange(myenv, rightExpr, leftExpr, rightExpr));
  }
}



