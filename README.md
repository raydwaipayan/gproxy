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
** For setting apt proxy, root access is needed. Run gproxy as sudo. **
** Currently for environment proxy only bash is supported **