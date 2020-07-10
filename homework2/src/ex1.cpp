//  Exercise 1.
#include <iostream>
using namespace std;

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

void printMAP(int arr[][10], int num, int k) {
    double sum=0;
    cout << "---------------------------" << endl;
    for (int i = 0; i < num; i++) {
        double ap = getAP(arr[i], k);
        cout << "AP@" << k << "-query" << i+1 << ": " << ap << endl;
        sum += ap;
    }
    cout << "---------------------------" << endl;
    cout << "MAP@" << k << ": " << sum/num << endl;
}

double getRR(int arr[], int k) {
    for (int i = 0; i < k; i++) {
        if(arr[i]!=0)
            return (double)1/(i+1);
    }
    return 0;
}

void printMRR(int arr[][10], int num, int k) {
    double sum=0;
    cout << "---------------------------" << endl;
    for (int i = 0; i < num; i++) {
        double rr = getRR(arr[i], k);
        cout << "RR@" << k << "-query" << i+1 << ": " << rr << endl;
        sum += rr;
    }
    cout << "---------------------------" << endl;
    cout << "MRR@" << k << ": " << sum/num << endl;
}

int main() {
    int query[3][10] = {
        {1,0,1,0,0,1,1,0,0,1},
        {1,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,1,1,0,0,1}
    };
    printMAP(query,3,5);
    printMAP(query,3,10);
    printMRR(query,3,5);
    printMRR(query,3,10);
    cout << "---------------------------" << endl;
    return 0;
}