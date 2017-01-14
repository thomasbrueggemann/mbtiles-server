#include <iostream>
#include <vector>
#include <cstdlib>

#include "crow.h"
#include "decodegzip.h"
#include "vectortile.h"
#include "mbtilereader.h"

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
	std::cout << "Loading file: " << argv[2] << std::endl;

	// get format
	std::string format = mbTileReader.GetMetadata("format");
	std::cout << format << std::endl;

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
	CROW_ROUTE(app, "/")
	([]()
	{
		return "=== MBTILES-SERVER ===\nUsage: GET /{z}/{x}/{y}";
	});

	CROW_ROUTE(app, "/<int>/<int>/<int>")
	([&mbTileReader, &format, &versionInts](int zoom, int col, int row)
	{
		// get the tile
		std::string blob;
		mbTileReader.GetTile(zoom, col, row, blob);
		std::cout << versionInts[0] << std::endl;

		// PBF
		if(format == "pbf" && versionInts[0] == 2)
		{
			// ungzip the data
			std::stringbuf buff;
			buff.sputn(blob.c_str(), blob.size());
			DecodeGzip dec(buff);

			std::string tileData;

			char tmp[1024];
			while(dec.in_avail())
			{
				std::streamsize bytes = dec.sgetn(tmp, 1024);
				tileData.append(tmp, bytes);
			}

			// prepare response
			auto res = crow::response(tileData);
			res.set_header("Access-Control-Allow-Origin", "*");
			res.set_header("Content-Type", "application/x-protobuf");
			return res;
		}

		// JPG
		if(format == "jpg")
		{
			// prepare response
			auto res = crow::response(blob);
			res.set_header("Access-Control-Allow-Origin", "*");
			res.set_header("Content-Type", "image/jpeg");
			return res;
		}

		// PNG
		if(format == "png")
		{
			// prepare response
			auto res = crow::response(blob);
			res.set_header("Access-Control-Allow-Origin", "*");
			res.set_header("Content-Type", "image/png");
			return res;
		}

		// not the right format
		return crow::response(501);
    });

	crow::logger::setLogLevel(crow::LogLevel::Info);

	std::cout << "API listening on port " + std::to_string(port) + "..." << std::endl;
	app.port(port).multithreaded().run();
}
