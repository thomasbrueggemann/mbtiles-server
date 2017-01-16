CC = g++

CFLAGS = -Ofast -std=c++14 -Wall
LDFLAGS = -pthread -lboost_system -lboost_filesystem -lsqlite3 -lprotobuf-lite -lz
OBJ = decodegzip.o vector_tile.pb.o vectortile.o mbtilereader.o

EXE = mbtiles-server
INC =

all: $(EXE)

clean:
	rm -f *~ *.o core $(EXE)
	rm -rf *.dSYM

$(EXE): % : %.o $(OBJ)
	$(CC) $(CFLAGS) $@.o -o $@ $(OBJ) $(LDFLAGS)

%.o: %.cpp $(INC)
	$(CC) $(CFLAGS) -c $<
