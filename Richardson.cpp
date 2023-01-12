#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;

double* matrixProduct(double **a, double *x, int n)
{
    double *y = new double[n];
    for(int i = 0; i < n; ++i) y[i] = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; ++j)
        {
            y[i] += a[i][j] * x[j];
        }
    }
    return y;
}

double scalProduct(double *x, double *y, int n)
{
    double result = 0;
    for(int i = 0; i < n; ++i) result += x[i] * y[i];
    return result;
}

int main()
{
    double alpha, beta, inaccuracy, norma;
    int n;
    cin >> inaccuracy >> alpha >> beta;
    cin >> n;
    double t1 = (-beta-alpha)/(beta-alpha);
    double omega0 = (-beta+alpha)/(beta+alpha);
    double** A = new double*[n], *b = new double[n];
    double d = 2/(alpha+beta);
    for(int i = 0; i < n; ++i)
    {
        A[i] = new double[n];
        for(int j = 0; j < n; ++j)
        {
            cin >> A[i][j];
        }
        cin >> b[i];
    }
    double* x0 = new double[n];
    double* x2 = new double[n];
    for(int i = 0; i < n; ++i) x0[i] = 0;

    double *x1 = new double[n];
    double* ax = new double[n];
    for(int i = 0; i < n; ++i) {ax[i] = 0; x1[i] = x0[i] + d*b[i];}

    int countOfIter = 0;
    do
    {
        countOfIter++;
        double omega1 = 1/(2*t1-omega0);
        for(int i = 0; i < n; ++i) x2[i] = 0;
        ax = matrixProduct(A, x1, n);
        for(int i = 0; i < n; ++i)
        {
            x2[i] = x1[i] + omega0*omega1*(x1[i]-x0[i]) - d*(1+omega0*omega1)*(ax[i]-b[i]);
        }


        norma = abs(x2[0]-x1[0]);
        for(int i = 0; i < n; ++i)
        {
            if(norma < abs(x2[i] - x1[i])) norma = abs(x2[i] - x1[i]);
            x0[i] = x1[i];
            x1[i] = x2[i];
        }
        omega0 = omega1;
        delete[] ax;
    }while(norma > inaccuracy);


    cout << "Iterations: " << countOfIter << endl;
    for(int i = 0; i < n; ++i) printf("%.8lf ", x2[i]);

    for(int i = 0; i < n; ++i) delete[] A[i];
    delete[] b, A, x2, x1, x0;
}

