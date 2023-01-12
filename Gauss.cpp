#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int n;
    int sign = 1;
    cin >> n;
    double det = 1;
    double **a = new double*[n];
    for(int i = 0; i < n; ++i){
        a[i] = new double[n];
        for(int j = 0; j < n; ++j){
            cin >> a[i][j];
        }
    }
    double *b = new double[n];
    for(int i = 0; i < n; ++i)
        cin >> b[i];
    for(int i = 0,j = 0; i < n; ++i,++j){
        if(a[i][j] == 0){
            int l1 = i+1;
            while(l1 < n){
                if(a[l1][j] != 0){
                    int c = b[i];
                    b[i] = b[l1];
                    b[l1] = c;
                    sign *= -1;
                    for(int l2 = 0; l2 < n; ++l2){
                        int c = a[l1][l2];
                        a[l1][l2] = a[i][l2];
                        a[i][l2] = c;
                    }
                    break;
                }
                l1++;
            }
        }
        for(int l2 = i+1; l2 < n; ++l2){
            b[l2] += b[i]*(-a[l2][j])/a[i][j];
            for(int l1 = j+1; l1 < n; ++l1){
                if(a[l2][l1] != 0){
                    a[l2][l1] += a[i][l1]*(-a[l2][j])/a[i][j];
                }
            }
            a[l2][j] = 0;
        }
    }
    for(int i = 0; i < n; ++i){
        det *= a[i][i];
        for(int j = 0; j < n; ++j){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << sign*det << endl;
    vector<double> res(n);
    for(int i = n-1; i > -1; --i){
        for(int j = i; j < n; ++j){
            b[i] -= a[i][j]*res[j];
        }
        if(a[i][i] != 0)
        res[i] = b[i]/a[i][i];
    }
    for(int i = 0; i < n; ++i) if(res[i] != 0) cout << res[i] << " "; else cout << 0 << " ";
}

//2
//1 2
//1 2
//1 1

//3
//0 1 2
//1 2 3
//2 2 1
//-1 0 3

//3
//1 2 1
//2 3 1
//2 1 1
//1 2 2

//4
//2 2 -1 1
//4 3 -1 2
//8 5 -3 4
//3 3 -2 2
//4 6 12 6

