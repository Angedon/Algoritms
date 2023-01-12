#include<iostream>
#include<cmath>
using namespace std;

double norm(double* a, int n)
{
	double result = 0;
	for (int i = 0; i < n; ++i) result += a[i] * a[i];
	return sqrt(result);
}

double* wGet(double* a, int n, int k)
{
	double* w = new double[n];
	double* b = new double[n];
	for (int i = 0; i < n; ++i) b[i] = a[i];
	double norma = norm(a, n);
	//cout << norma << endl;
	if (a[k] == 0)
	{
		b[k] -= norma;
		double normaB = norm(b, n);
		for (int i = 0; i < n; ++i)
		{
			w[i] = b[i] / normaB;
			//cout << w[i] << " ";
		}
		//cout << endl;
	}
	else
	{
		b[k] += (b[k] > 0 ? 1 : -1) * norma;
		double normaB = norm(b, n);
		for (int i = 0; i < n; ++i)
		{
			w[i] = b[i] / normaB;
			//cout << w[i] << " ";
		}
		//cout << endl;
	}
	return w;
}

int main()
{
	int n;
	cin >> n;
	double** A = new double* [n];
	double* c = new double[n];
	for (int i = 0; i < n; ++i)
	{
		A[i] = new double[n];
		for (int j = 0; j < n; ++j) {
			cin >> A[i][j];
		}
		cin >> c[i];
	}
	for (int i = 0; i < n; ++i)
	{
		double* b = new double[n];
		for (int j = 0; j < n; ++j) b[j] = A[j][i];
		double* w = wGet(b, n, i);
		//for (int l = 0; l < l; ++l) cout << w[l] << " ";
		//cout << w[0] << " ";
		//cout << endl;
		double** H = new double* [n];
		for (int l1 = 0; l1 < n; ++l1)
		{
			H[l1] = new double[n];
			for (int l2 = 0; l2 < n; ++l2)
			{
				H[l1][l2] = (l1 == l2 ? 1 : 0) - 2 * w[l1] * w[l2];
				//cout << H[l1][l2] << " ";
			}
			//cout << endl;
		}
		for (int l0 = 0; l0 < n; ++l0) {
			for (int l1 = 0; l1 < n; ++l1)
			{
				double res = 0;
				for (int l2 = 0; l2 < n; ++l2)
				{
					res += H[l0][l2] * A[l2][l1];
				}
				A[l0][l1] = res;
				//cout << A[l0][l1] << " ";
			}
			//cout << endl;
		}
		for (int l0 = 0; l0 < n; ++l0) {
			double res = 0;
			for (int l1 = 0; l1 < n; ++l1) {
				res += H[l0][l1] * c[l1];
			}
			c[l0] = res;
		}
		delete[] b, w;
	}
	for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; ++j)
        {
            cout << A[i][j] << " ";
        }
        cout << c[i] << endl;
    }
	delete[] c;
}
