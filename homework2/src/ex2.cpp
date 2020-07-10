//  Exercise 2.
#include <iostream>
#include <cmath>
using namespace std;

double getP(int arr[], int k) {
    int count=0;
    for (int i = 0; i < k; i++) {
        if (arr[i]!=0) {
            count++;
        }
    }
    return (double)count/k;
}

double getR(int arr[], int k, int allRelNum) {
    int count=0;
    for (int i = 0; i < k; i++) {
        if(arr[i]!=0) {
            count++;
        }
    }
    return (double)count/allRelNum;
}

double getAP(int arr[], int k) {
    int a[10];
    double sum=0;
    int count=0;
    a[0]=arr[0];
    for (int i = 1; i < k; i++) {
        a[i] = a[i-1]+arr[i];
    }
    for (int i = 0; i < k; i++) {
        if(arr[i]!=0) {
            sum += (double)a[i]/(i+1);
            count++;
        }
    }
    if (count) {
        return sum/count;
    }
    return 0;
}

double getDCG(int arr[], int k) {
    double dcg = arr[0];
    for (int i = 1; i < k; i++) {
        double temp = log(i+1)/log(2);
        dcg += (double)arr[i]/temp;
    }
    return dcg;
}

double getRR(int arr[], int k) {
    for (int i = 0; i < k; i++) {
        if(arr[i]!=0)
            return (double)1/(i+1);
    }
    return 0;
}

int main() {
    int allRelNum = 0;
    int arr[10] = {4,1,0,3,4,1,0,1,0,2};
    int arrb[10] = {1,1,0,1,1,1,0,1,0,1};
    int arrc[10] = {4,4,3,2,1,1,1,0,0,0};
    for (int i = 0; i < 10; i++) {
        if (arr[i]!=0)
            allRelNum++;
    }
    cout << "---------------------------" << endl;
    cout << "P@5: " << getP(arr, 5) << endl;
    cout << "P@10: " << getP(arr, 10) << endl;
    cout << "---------------------------" << endl;
    cout << "R@5: " << getR(arr, 5, allRelNum) << endl;
    cout << "R@10: " << getR(arr, 10, allRelNum) << endl;
    cout << "---------------------------" << endl;
    cout << "P@7: " << getP(arr, allRelNum) << endl;
    cout << "---------------------------" << endl;
    cout << "AP: " << getAP(arrb, 10) << endl;
    cout << "---------------------------" << endl;
    cout << "DCG_5: " << getDCG(arr, 5) << endl;
    cout << "IDCG_5: " << getDCG(arrc, 5) << endl;
    cout << "NDCG_5: " << getDCG(arr, 5)/getDCG(arrc, 5) << endl;
    cout << "---------------------------" << endl;
    cout << "RR@5: " << getRR(arr, 5) << endl;
    cout << "RR@10: " << getRR(arr, 10) << endl;
    cout << "---------------------------" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "P-R-" << i+1 << ": " << getP(arr, i+1) << " ~ " << getR(arr, i+1, allRelNum) << endl;
    }
    return 0;
}