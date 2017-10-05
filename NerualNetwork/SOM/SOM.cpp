#include "SOM_H.h"

void main()
{
	SOM_NET network;
	network.train();
	network.exportFile("bupatest.dat");
}
