#include <iostream>
#include <vector>

#include "crow.h"
#include "cppGzip/DecodeGzip.h"
#include "VectorTile.h"
#include "MBTileReader.h"

const std::string VERSION = "1.0.0";
const int PORT = 8666;

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

	// init crow http server
	crow::SimpleApp app;

	// init mbtiles reader
	class MBTileReader mbTileReader("cairo_egypt.mbtiles");
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
	([&mbTileReader](int a, int b, int c)
	{
		std::string blob;
		mbTileReader.GetTile(a, b, c, blob);

        return a + b + c;
    });

	crow::logger::setLogLevel(crow::LogLevel::Debug);

	std::cout << "API listening on port " + std::to_string(PORT) + "..." << std::endl;
	app.port(PORT).multithreaded().run();
}
