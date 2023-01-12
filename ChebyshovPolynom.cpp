#define _USE_MATH_DEFINES
#include<iostream>
#include<vector>
#include<iomanip>
#include<cmath>
using namespace std;

vector<double> formPart(vector<double> x, vector<double> y, int n, int index)
{
    vector<double> arr;
    int p = 0;
    if(index != 0) arr.push_back(-x[0]); else {arr.push_back(-x[1]); p = 1;}
    arr.push_back(1);
    double denom = 1;
    double a = x[index];
    for(int i = 0; i < n; ++i)
    {
        if(i != index) {
            denom *= (a-x[i]);
            if(i != p){
                for(int j = arr.size()-1; j > 0; --j){
                    double b;
                    b = arr[j] * (-x[i]) + arr[j-1];
                    arr[j] = b;
                }
                arr[0] = (-x[i]) * arr[0];
                arr.push_back(1);
            }
        }
    }
    for(int i = 0; i < n; ++i) arr[i] = arr[i] / denom;
    return arr;
}

void formPolynom(vector<double> x, vector<double> y, int n)
{
    vector<double> result;
    for(int i = 0; i < n; ++i) result.push_back(0);
    for(int i = 0; i < n; ++i)
    {
        vector<double> temp = formPart(x, y, n, i);
        for(int j = n-1; j > -1; --j)
        {
            //cout << temp[j] << " ";
            result[j] += y[i] * temp[j];
        }
        //cout << endl;
    }
    double res = 0;
    for(int i = 0; i < n; ++i) cout << x[i] << " ";
    cout << endl;
    for(int i = 0; i < n; ++i) cout << y[i] << " ";
    cout << endl;
    for(int i = n-1; i > -1; --i) { cout << setprecision(9) << result[i] << " "; }
}

// Chebyshev
void ch(int n)
{
    vector<double> x(n+1); vector<double> y(n+1);
    for(int i = 0; i < n; ++i)
    {
        x[i] = cos(((2*((double)i+1)-1)/(2*(double)n)) * M_PI);
        y[i] = exp(x[i]);
    }
    formPolynom(x, y, n);
}

// Lagrange
void la(int n)
{
    vector<double> x(n); vector<double> y(n);
    for(int i = 0; i < n; ++i)
    {
        cin >> x[i];
        y[i] = exp(x[i]);
    }
    formPolynom(x, y, n);
}

int main()
{
    int n;
    cin >> n;
    ch(n);
    //cout << endl << setprecision(9) << M_PI;
}
