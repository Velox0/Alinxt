#!/usr/bin/sh

mkdir /tmp/alinxt
wget -O /tmp/alinxt/main.cpp https://raw.githubusercontent.com/Velox0/Alinxt/main/main.cpp
wget -O /tmp/alinxt/modules.hh https://raw.githubusercontent.com/Velox0/Alinxt/main/modules.hh
wget -O /tmp/alinxt/version.hh https://raw.githubusercontent.com/Velox0/Alinxt/main/version.hh
wget -O /tmp/alinxt/alinxt.6 https://raw.githubusercontent.com/Velox0/Alinxt/main/alinxt.6

sudo g++ -O3 /tmp/alinxt/main.cpp -o /usr/bin/alinxt
gzip -f      /tmp/alinxt/alinxt.6

manpath="/usr/share/man/man6/"
sudo mv /tmp/alinxt/alinxt.6.* $manpath