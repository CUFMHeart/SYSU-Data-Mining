//  Exercise 1.
//  投点法
#include <iostream>
#include <ctime>
#include <vector>
#include <numeric>
using namespace std;

int main()
{	
    int plan_num, point_num, test_times;
    vector<double> point_num_s;
    vector<double> pi_s;
    srand(static_cast<unsigned int>(time(0)));

    cout << "Enter the number of plans: ";
    cin >> plan_num;
    cout << "Enter the sequence of the total number of points thrown: ";
    for (int i = 0; i < plan_num; i++)
    {
        cin >> point_num;
        point_num_s.push_back(point_num);
    }
    cout << "Enter the number of throws per test: ";
    cin >> test_times;

    cout << "----------------------------------------------------" << endl;
    cout << "N\tMEAN\t\tVARIANCE" << endl;
    for_each (begin(point_num_s), end(point_num_s), [&](const int point_num_t)
    {
        for (int i = 0; i < test_times; i++)
        {
            int result = 0;
            double x, y, pi;
            for (int j = 0; j < point_num_t; j++)
            {
                x = static_cast<double>(rand()) / RAND_MAX;
                y = static_cast<double>(rand()) / RAND_MAX;
                if (x*x + y*y < 1.0)
                    result++;
            }
            pi = 4.0 * result / point_num_t;
            pi_s.push_back(pi);
        }
        double sum = accumulate(begin(pi_s), end(pi_s), 0.0);
        double mean = sum / pi_s.size();
        double accum = 0.0;
        for_each (begin(pi_s), end(pi_s), [&](const double pi_t)
        {
            accum += (pi_t-mean) * (pi_t-mean);
        });
        double variance = accum / pi_s.size();
        printf("%d\t%-8.6lf\t%-12.9lf\n", point_num_t, mean, variance);
        pi_s.clear();
    });
    cout << "----------------------------------------------------" << endl;
    return 0;
}