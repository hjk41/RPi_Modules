#include "HC_SR04.h"
#include <iomanip>
#include <iostream>
using namespace std;

int main(int argc, char ** argv)
{
	const int trig = 2;
	const int echo = 3;
	HC_SR04 device(trig, echo);
	
	while(true)
	{
		double d = device.GetDist();
		cout <<setprecision(6) << d << endl;
		SleepUs(200000);
	}

	return 0;
}
