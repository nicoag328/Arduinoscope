#!/bin/bash

FILES="src/arduinoscope.c src/serial.h src/queue.h"
OUTPUT="bin/arduinoscope"
LIBS="gtk+-3.0 libserialport"

mkdir bin
gcc $FILES -o $OUTPUT $(pkg-config --cflags --libs $LIBS)
