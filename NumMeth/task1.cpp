#include <cstdio>
#include <cmath> 
using namespace std;


int main()
{
    double y1 = 1;
    double y2 = 1;
    double x1 = 0;
    double x2 = 0;

    for (int n = 0; n < 14; n++) 
    {
        double b = y1 + y2;

        x1 = (b + sqrt(b * b - 4)) / (double)2;
        x2 = (b - sqrt(b * b - 4)) / (double)2;
        y1 *= 10;
        y2 /= 10;
        printf("n = %3d x1 = %20.15e x2 = %20.15e\n", n, x1, x2);
    }

    return 0;
}