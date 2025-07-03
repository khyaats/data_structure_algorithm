#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Function to evaluate f(x)
double f(double x, double a) {
    return (x * x / log(x)) + a * x;
}

int main() {
    double a;
    cin >> a;

    double lo = 1.000001, hi = 1.999999;
    double eps = 1e-9;

    while (hi - lo > eps) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;

        if (f(m1, a) < f(m2, a)) {
            hi = m2;
        }
        else {
            lo = m1;
        }
    }

    double x_min = (lo + hi) / 2;
    cout << fixed << setprecision(10) << f(x_min, a) << endl;

    return 0;
}
