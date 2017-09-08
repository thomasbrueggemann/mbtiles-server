#ifndef MBTILE_READER_H
#define MBTILE_READER_H

#include <sqlite3.h>
#include <string>
#include <map>
#include <vector>

typedef std::vector<std::vector<unsigned int> > TileInfoRows;

class MBTileReader
{
public:
	MBTileReader(const char *filename);
	virtual ~MBTileReader();

	void GetTile(unsigned int zoomLevel,
		unsigned int tileColumn,
		unsigned int tileRow,
		std::string &blobOut);

protected:
	sqlite3 *db;
};

#endif //MBTILE_READER_H
