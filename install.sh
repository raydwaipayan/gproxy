#!/bin/sh
# Creator: Dwaipayan Ray
# Feel free to modify this program and add your own options

# Check for existence of gtk+-3.0, else exit
pkg-config --modversion gtk+-3.0 2>/dev/null || {
	echo >&2 "I require gtk+-3.0 but it's not installed.  Aborting.";
	exit 1; 
} 

# Check if root
if [[ `id -u` -ne 0 ]]; then
	echo "This script must be run as root";
	exit 1;
fi

# Create the binary
gcc `pkg-config --cflags gtk+-3.0` src/gproxy.c -o src/gproxy `pkg-config --libs gtk+-3.0` -w

# Copy over files
cp src/gproxy /usr/local/bin/gproxy
cp src/gproxy.sh /usr/local/lib/gproxy.sh

# Set file permissions
chmod +x  /usr/local/bin/gproxy
chmod +x /usr/local/lib/gproxy.sh

# End
echo "Successfully installed! Run using sudo gproxy"
