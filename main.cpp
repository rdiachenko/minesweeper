#include <string>
#include "Config.h"
#include "GameLoop.h"

int main(int argc, char** argv)
{
	std::string confPath = "resources/classic.conf";

	if (argc > 1)
	{
		confPath = argv[1];
	}
	Config config(confPath);
	GameLoop loop(&config);
	loop.run();
	return 0;
}
