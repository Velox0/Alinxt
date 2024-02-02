#!/usr/bin/sh
# This script should be run to quick install alinxt

# Make directory if does not exist
if [ ! -d "/tmp/alinxt" ]; then
  mkdir /tmp/alinxt
fi

# Download from source to tmp
wget -O /tmp/alinxt/main.cpp https://raw.githubusercontent.com/Velox0/Alinxt/main/main.cpp
wget -O /tmp/alinxt/modules.hh https://raw.githubusercontent.com/Velox0/Alinxt/main/modules.hh
wget -O /tmp/alinxt/version.hh https://raw.githubusercontent.com/Velox0/Alinxt/main/version.hh
wget -O /tmp/alinxt/alinxt.6 https://raw.githubusercontent.com/Velox0/Alinxt/main/alinxt.6

# Compile code and zip man page
sudo g++ -O3 /tmp/alinxt/main.cpp -o /usr/bin/alinxt
gzip -f      /tmp/alinxt/alinxt.6

## Setup man page path
manpath="/usr/share/man/man6/"
if [ ! -d "$manpath" ]; then
  # Create the path
  sudo mkdir -p "$manpath"
fi

# Move man page to user man6 (games)
sudo mv /tmp/alinxt/alinxt.6.* $manpath