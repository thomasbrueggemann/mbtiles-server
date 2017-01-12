#include <iostream>

#include "crow.hpp"

const std::string VERSION = "1.0.0";
const int PORT = 8666;

// MAIN
int main(int argc, char* argv[]) {

	std::cout << "MBTILES - SERVER v" << VERSION << std::endl;

	// init API server
	crow::SimpleApp app;

	// declaration of routes
	CROW_ROUTE(app, "/")([]
	{
        return "GREENWAVE API v" + VERSION;
    });

	crow::logger::setLogLevel(crow::LogLevel::Debug);

	std::cout << "API listening on port " + std::to_string(PORT) + "..." << std::endl;
	app.port(PORT).multithreaded().run();
}
