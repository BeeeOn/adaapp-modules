/**
 * @file Main.cpp
 * @Author BeeeOn team - Peter Tisovčík <xtisov00@stud.fit.vutbr.cz>
 * @date September, 2016
 */

#include "Startup.h"

int main(int argc, char **argv)
{
	Startup server;
	server.setUnixOptions(true);
	return server.run(argc, argv);
}
