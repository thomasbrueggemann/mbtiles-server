#include <iostream>
#include <vector>
#include <cstdlib>

#include "crow.h"
#include "cppGzip/DecodeGzip.h"
#include "VectorTile.h"
#include "MBTileReader.h"

const std::string VERSION = "1.0.0";

// http://stackoverflow.com/a/236803/4288232
void strsplit(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

// MAIN
int main(int argc, char* argv[]) {

	std::cout << "MBTILES - SERVER v" << VERSION << std::endl;

	// check if correct amount of arguments was submitted
	if(argc != 3) {
		std::cout << "Usage: mbtiles-server {PORT} {MBTILES-FILE}" << std::endl;
		return 1;
	}

	// parameters
	int port = atoi(argv[1]);

	// init crow http server
	crow::SimpleApp app;

	// init mbtiles reader
	class MBTileReader mbTileReader(argv[2]);
	std::string format = mbTileReader.GetMetadata("format");

	// get version numbers
	std::string version = mbTileReader.GetMetadata("version");
	std::vector<std::string> versionSplit;
	strsplit(version, '.', versionSplit);
	std::vector<int> versionInts;
	for (size_t i = 0; i < versionSplit.size(); i++)
	{
		versionInts.push_back(atoi(versionSplit[i].c_str()));
	}

	// declaration of routes
	CROW_ROUTE(app, "/<int>/<int>/<int>")
	([&mbTileReader](int zoom, int col, int row)
	{
		std::string blob;
		mbTileReader.GetTile(zoom, col, row, blob);

        return blob;
    });

	crow::logger::setLogLevel(crow::LogLevel::Debug);

	std::cout << "API listening on port " + std::to_string(port) + "..." << std::endl;
	app.port(port).multithreaded().run();
}
