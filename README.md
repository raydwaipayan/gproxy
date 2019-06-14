# GPROXY
Gproxy is a gtk application developed in c and shell. It simplifies the process of setting proxy for various system utilities in linux.

## Requirements
* gcc
* gtk+-3.0
* bash

## Usage
```
gcc `pkg-config --cflags gtk+-3.0` gproxy.c -o gproxy `pkg-config --libs gtk+-3.0`
./gproxy
```
**For setting certain proxy settings, root access is needed. Run gproxy as sudo.**
**bash is required**