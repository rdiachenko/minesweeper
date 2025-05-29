#include <string>
#include <iostream>
#include <memory>
#include <exception>
#include <stdexcept>
#include "Config.h"
#include "GameLoop.h"

int main(int argc, char** argv)
{
	try {
		std::string confPath = "resources/classic.conf";

		if (argc > 1) {
			if (!argv[1]) {
				throw std::invalid_argument("Invalid config path argument");
			}
			confPath = argv[1];
		}
		
		if (confPath.empty()) {
			throw std::invalid_argument("Config path cannot be empty");
		}
		
		std::cout << "Loading config from: " << confPath << std::endl;
		
		auto config = std::make_shared<Config>(confPath);
		if (!config) {
			throw std::runtime_error("Failed to create config object");
		}
		
		GameLoop loop(config.get());
		
		std::cout << "Starting game loop..." << std::endl;
		loop.run();
		
		std::cout << "Game ended successfully." << std::endl;
		return 0;
		
	} catch (const std::invalid_argument& e) {
		std::cerr << "Invalid argument error: " << e.what() << std::endl;
		std::cerr << "Usage: " << (argv[0] ? argv[0] : "minesweeper") << " [config_path]" << std::endl;
		return 1;
	} catch (const std::runtime_error& e) {
		std::cerr << "Runtime error: " << e.what() << std::endl;
		return 2;
	} catch (const std::exception& e) {
		std::cerr << "Unexpected error: " << e.what() << std::endl;
		return 3;
	} catch (...) {
		std::cerr << "Unknown error occurred. The application will now terminate." << std::endl;
		return 4;
	}
}