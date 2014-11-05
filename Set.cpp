#include <iostream>
#include "RPi_GPIO.h"
#include <stdlib.h>
using namespace std;

int main(int argc, char ** argv)
{
	if (argc != 3)
	{
		cout << "usage: " << argv[0] <<" GPIO " << "0/1" << endl;
		return 1;
	}
	int port = atoi(argv[1]);
	int enable = atoi(argv[2]);

	GPIO::GPIOInit();
	GPIO::GPIOSetOutput(port);
	
	if (enable)
		GPIO::GPIOSetHigh(port);
	else
		GPIO::GPIOSetLow(port);	

	return 0;
}
