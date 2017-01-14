#!/bin/bash

cd /home
wget -O data.mbtiles $FILE
./mbtiles-server $PORT data.mbtiles
