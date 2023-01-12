#include<iostream>
#include<vector>
using namespace std;
int sizeA = 0, sizeB = 0;
int main()
{
    int a, b, n = 0, c;
    cin >> a;
    if(a != 0){
    b = a;
    while(b != 0){
        n++;
        b /= 10;
    }
    vector<int> arr;
    c = a;
    for(int i = 0; i < n; i++){
        arr.push_back(a % 10);
        a /= 10;
    }
    sizeA = n;
    for(int i = 2; i < c; i++){
        int h = i;
        int k = 0;
        while(h != 0){
            k++;
            h /= 10;
        }
        sizeB = k;
        int a1[sizeB];
        int i2 = i;
        for(int j = 0; j < sizeB; j++){
            a1[j] = i2 % 10;
            i2 /= 10;
        }
        vector<int> res;
        for(int j = 0; j < sizeA+sizeB; j++) res.push_back(0);
        for(int j1 = 0; j1 < sizeA; j1++){
            for(int j2 = 0; j2 < sizeB; j2++){
                res[j1+j2] += (arr[j1]*a1[j2]) % 10;
                res[j1+j2+1] += (arr[j1]*a1[j2]) / 10;
            }
        }
        for(int i1 = 0; i1 < sizeA+sizeB-1; i1++) {
                if(res[i1] > 9){
                    res[i1+1] += res[i1]/10;
                    res[i1] = res[i1]%10;
                }
            }
            arr.clear();
        if(res[sizeA+sizeB-1] == 0) {
        for(int i1 = 0; i1 < sizeA+sizeB-1; i1++) {
                arr.push_back(res[i1]);
        }
        sizeA += sizeB-1;
    }
    else {
        for(int i1 = 0; i1 < sizeA+sizeB; i1++) {
            arr.push_back(res[i1]);
        }
        sizeA += sizeB;
    }
    res.clear();
    }
    for(int i = sizeA-1; i >= 0; --i) cout << arr[i];
    }
    else cout << 1;
}
