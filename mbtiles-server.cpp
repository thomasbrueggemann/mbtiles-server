#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>

#include "crow.h"
#include "mbtilereader.h"

const std::string VERSION = "1.0.0";

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
	MBTileReader mbTileReader(argv[2]);
	std::cout << "Loading file: " << argv[2] << std::endl;

	// declaration of routes
	CROW_ROUTE(app, "/")
	([]()
	{
		return "=== MBTILES-SERVER ===\nUsage: GET /{z}/{x}/{y}";
	});

	CROW_ROUTE(app, "/<int>/<int>/<int>")
	([&mbTileReader](int zoom, int col, int row)
	{
		// get the tile
		std::string blob;

		try {
			mbTileReader.GetTile(zoom, col, row, blob);
		}
		catch(std::exception e) {
			auto res = crow::response(500, "tile not found");
			res.set_header("Access-Control-Allow-Origin", "*");
			return res;
		}

		// prepare response
		auto res = crow::response(blob);
		res.set_header("Access-Control-Allow-Origin", "*");
		res.set_header("Content-Type", "application/octet-stream");
		res.set_header("Content-Encoding", "gzip");
		res.set_header("Cache-Control", "public");
		return res;
    });

	crow::logger::setLogLevel(crow::LogLevel::Critical);

	std::cout << "API listening on port " + std::to_string(port) + "..." << std::endl;
	app.port(port).multithreaded().run();
}
