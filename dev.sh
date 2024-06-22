#!/bin/bash

# Remove the builddir directory, configure and compile the project
rm -rf builddir && \
meson setup builddir && \
meson compile -C builddir && \
# Set memory limit to 10MiB
ulimit -v 102400 && \
# Run the compiled program with root privileges
sudo ./builddir/src/ethernetcap
