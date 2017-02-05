# 🌐 MBTiles-Server
Little C++ server that serves MBTiles vector tiles.

## Run using Docker

1. Build the docker image

```
cd mbtiles-server
docker build . -t mbtiles
```

2. Run the image as a container

You need to specify the PORT that the MBTiles-Server will listen on and a FILE url to a .mbtiles file,
so that the container can download the necessary data base.

You can get .mbtiles files e.g. from https://openmaptiles.org/downloads/

```
docker run -e FILE=https://openmaptiles.os.zhdk.cloud.switch.ch/v3.3/extracts/cologne_germany.mbtiles -e PORT=8989 -p 8989:8989 mbtiles
```

## Test

Open and adjust the test/test.html file.
