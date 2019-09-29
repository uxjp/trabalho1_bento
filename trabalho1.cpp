#include <iostream>
#include <math.h>

using namespace std;

double f_de_x(double a, double x)
{
    
    return a*exp(x) - 4*x*x;
}

double f_linha_de_x(double a, double x)
{
    
    return a*exp(x) - 8*x;
}

int main(int argc, char const *argv[])
{   
    double amplitude = 0.5;

    for(int i = -10; i <=10; i = i + 1){
        cout << "i  " << f_de_x(amplitude, i) << endl;    
    }
    return 0;
}
