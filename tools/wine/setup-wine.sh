#!/bin/bash

# Check if the number of cores is provided as an argument
if [ -z "$1" ]; then
  CORES=1
else
  CORES=$1
fi

# Clone Wine
mkdir -p ./winesrc
git clone https://gitlab.winehq.org/wine/wine.git ./winesrc

# Make build directories
mkdir -p ./build/wine32
mkdir -p ./build/wine64

# Configure and build the 64-bit version
cd ./build/wine64
../../winesrc/configure CFLAGS="-march=native -Og -fno-inline -fno-omit-frame-pointer -fno-optimize-sibling-calls -pipe -fstack-protector-strong" --enable-win64
make -j$CORES

echo "Wine 64-bit configured and built with $CORES core(s)."

# Configure and build the 32-bit version
cd ../wine32
PKG_CONFIG_PATH=/usr/lib/pkgconfig ../../winesrc/configure CFLAGS="-march=native -Og -fno-inline -fno-omit-frame-pointer -fno-optimize-sibling-calls -pipe -fstack-protector-strong" --with-wine64=../wine64
make -j$CORES

echo "Wine 32-bit configured and built with $CORES core(s)."