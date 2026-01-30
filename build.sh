#!/bin/bash
set -e

# Configuration
MINIFB_DIR="minifb"
SRC_DIR="src"
HEADERS_DIR="headers"
OUTPUT_EXE="game.exe"

echo "Building Game with MiniFB..."

# Find all .c files in src directory
SOURCES=$(find "$SRC_DIR" -type f -name "*.c")

# MiniFB sources
MINIFB_SOURCES="$MINIFB_DIR/src/MiniFB_common.c \
$MINIFB_DIR/src/MiniFB_internal.c \
$MINIFB_DIR/src/MiniFB_timer.c \
$MINIFB_DIR/src/windows/WinMiniFB.c \
$MINIFB_DIR/src/gl/MiniFB_GL.c"

if [ -z "$SOURCES" ]; then
    echo "Error: No .c files found in $SRC_DIR"
    exit 1
fi

# Compile
# -I"$MINIFB_DIR/include" : Look for MiniFB.h
# -I"$MINIFB_DIR/src" : Needed for MiniFB internal headers
gcc $SOURCES $MINIFB_SOURCES -o "$OUTPUT_EXE" -O2 -Wall \
    -I"$MINIFB_DIR/include" \
    -I"$MINIFB_DIR/src" \
    -I"$HEADERS_DIR" \
    -lopengl32 -lgdi32 -lwinmm

echo "Build complete! ./$OUTPUT_EXE created."
