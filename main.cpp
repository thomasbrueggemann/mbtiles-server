#include <iostream>
#include <vector>

#include "crow.h"
#include "VectorTile.h"
#include "MBTileReader.h"

const std::string VERSION = "1.0.0";
const int PORT = 8666;

// MAIN
int main(int argc, char* argv[]) {

	std::cout << "MBTILES - SERVER v" << VERSION << std::endl;

	// init crow http server
	crow::SimpleApp app;

	// init mbtiles reader
	class MBTileReader mbTileReader("cairo_egypt.mbtiles");
	std::string format = mbTileReader.GetMetadata("format");
	std::vector<int> versionInts;
	for (size_t i=0;i<versionSplit.size();i++) versionInts.push_back(atoi(versionSplit[i].c_str()));

	// declaration of routes
	CROW_ROUTE(app, "/<int>/<int>/<int>")
	([](int x, int, y, int z){
	{
		std::string blob;
		mbTileReader.GetTile(z, x, y, blob);

        return x + y + z;
    });

	crow::logger::setLogLevel(crow::LogLevel::Debug);

	std::cout << "API listening on port " + std::to_string(PORT) + "..." << std::endl;
	app.port(PORT).multithreaded().run();
}
