#include <iostream>
#include "RPi_GPIO.h"
#include <stdlib.h>
using namespace std;

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		cout << "usage: " << argv[0] <<" GPIO" << endl;
		return 1;
	}
	int port = atoi(argv[1]);

	GPIO::GPIOInit();
	GPIO::GPIOSetInput(port);
	cout << GPIO::GPIORead(port) <<endl;
	return 0;
}
