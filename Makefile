CC = g++

CFLAGS = -g -std=c++14 -Wall
LDFLAGS = -pthread -lboost_system -lboost_filesystem -lsqlite3 -lprotobuf-lite -lz
OBJ = vector_tile.pb.o VectorTile.o MBTileReader.o

EXE = mbtiles-server
INC = vector_tile20

all: $(EXE)

clean:
	rm -f *~ *.o core $(EXE)
	rm -rf *.dSYM

$(EXE): % : %.o $(OBJ)
	$(CC) $(CFLAGS) $@.o -o $@ $(OBJ) $(LDFLAGS)

%.o: %.cpp $(INC)
	$(CC) $(CFLAGS) -c $<
