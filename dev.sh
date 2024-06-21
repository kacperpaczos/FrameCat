#!/bin/bash

# Remove builddir directory, configure and compile the project
rm -rf builddir
meson setup builddir
meson compile -C builddir 

# Run the compiled program with root privileges
sudo ./builddir/src/ethernetcap