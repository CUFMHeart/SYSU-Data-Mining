//  Exercise 3.
//  法1-投点法
#include <iostream>
#include <ctime>
#include <vector>
#include <numeric>
#include <cmath>
using namespace std;

int main()
{	
    int plan_num, point_num, test_times;
    vector<double> point_num_s;
    vector<double> value_s;
    srand(static_cast<unsigned int>(time(0)));

    cout << "Enter the number of plans: ";
    cin >> plan_num;
    cout << "Enter the sequence of sampling times: ";
    for (int i = 0; i < plan_num; i++)
    {
        cin >> point_num;
        point_num_s.push_back(point_num);
    }
    cout << "Enter the number of repetitions per sample: ";
    cin >> test_times;

    cout << "----------------------------------------------------" << endl;
    cout << "N\tMEAN\t\tVARIANCE" << endl;
    for_each (begin(point_num_s), end(point_num_s), [&](const int point_num_t)
    {
        for (int i = 0; i < test_times; i++)
        {
            int result = 0;
            double high = 1000000;
            double x, y, fun, z, a, b, value;
            for (int j = 0; j < point_num_t; j++)
            {
                x = static_cast<double>(rand()) / RAND_MAX * 2 + 2;
                y = static_cast<double>(rand()) / RAND_MAX * 2 - 1;
                z = static_cast<double>(rand()) / RAND_MAX * high;
                a = y*y*exp(-y*y) + pow(x, 4)*exp(-x*x);
                b = x * exp(-x*x);
                fun = a / b;
                if (z < fun)
                    result++;
            }
            value = 2 * 2 * high * result / point_num_t;
            value_s.push_back(value);
        }
        double sum = accumulate(begin(value_s), end(value_s), 0.0);
        double mean = sum / value_s.size();
        double accum = 0.0;
        for_each (begin(value_s), end(value_s), [&](const double value_t)
        {
            accum += (value_t-mean) * (value_t-mean);
        });
        double variance = accum / value_s.size();
        printf("%d\t%-12.0lf\t%-12.0lf\n", point_num_t, mean, variance);
        value_s.clear();
    });
    cout << "----------------------------------------------------" << endl;
    return 0;
}