//  Exercise 2.
//  法2-平均值法
#include <iostream>
#include <ctime>
#include <vector>
#include <numeric>
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
    cout << "N\tMEAN\t\t VARIANCE" << endl;
    for_each (begin(point_num_s), end(point_num_s), [&](const int point_num_t)
    {
        for (int i = 0; i < test_times; i++)
        {
            double result = 0;
            double x, value;
            for (int j = 0; j < point_num_t; j++)
            {
                x = static_cast<double>(rand()) / RAND_MAX;
                result += x * x * x;
            }
            value = result / point_num_t;
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
        printf("%d\t%8.6lf\t%12.9lf\n", point_num_t, mean, variance);
        value_s.clear();
    });
    cout << "----------------------------------------------------" << endl;
    return 0;
}