#include <ctime>
#include <cmath>
#include <cstdio>
#include <random>
#include <cstdlib>
#include <iostream>

using namespace std;

double f(double x)
{
    return  (  pow( -(x - 3) , 2 ) + 4 );
}
/*       2
f(x) = -x  + 4x - 2
             b
min(f) = - -----
            2a
       = -4 / (-1 * 2)
       = 2
*/
int rando = 0;
double ran()
{
	typedef mersenne_twister_engine<uint_fast64_t,64,312,156,31,0xb5026f5aa96619e9,29,0x5555555555555555,17,0x71d67fffeda60000,37,0xfff7eee000000000,43,6364136223846793005> mersenne;
	mersenne r(time(0) * ++rando);
	double half_rm = r.max() / 2;
	return (half_rm - r()) / double(r.max());
}
double SA(double &T,double &deltaT, double &X, double (*F)(double))
{
    if(T - 0 < 0.01)
        return X;
    srand(time(0));
    double deltaX = T * ran();
    double targetX = X + deltaX;
    double deltaF = F(X) - F(targetX);
    //cout << "SA begin.\n";
    //cout << "Orgin value now = " << X << endl;
    //cout << "Diffrent value = " << deltaX << endl;
    //cout << "Target value = " << targetX << endl;
    //cout << "Better = " << deltaF << endl;
    if(deltaF > 0)
    {
        //cout << "Reflush orgin value ,because dF > 0\n";
        X = targetX;
    }
	//If f'(x) is a muti-answer function, use follwing comment.
	//It helps to jump out the wrong answer.
	//If not, DON NOT USE IT!!!
	//It'll make many mistakes!
	/*
    else
    {
        double arg = pow( 2.71828182845, deltaF / T );
        if(ran() + 0.5 > arg)
			X = targetX;
    }*/
    T = T * deltaT;
    //cout << "Ready to take the next SA.\n";
    SA(T, deltaT, X, F);
}
int main()
{
	double t = 10000, dt = 0.99, x = 10;
    double ans =  SA(t, dt, x, f);
    cout << ans;
    return 0;
}
