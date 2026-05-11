#include <cstdio>
#include <cmath> 
using namespace std;


int main()
{
    double h = 1;
    double x = 1;

    for (int n = 0; n < 14; n++) 
    {
        double deriv = (exp(x + h) - exp(x)) / h;

        printf("h = %10.10e x = %f e^x = %10.10e deriv(e^x) = %10.10e diff = %10.10e \n", h, x, exp(x), deriv, fabs(exp(x) - deriv));
        h /= 10;

    }

    return 0;
}