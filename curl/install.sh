#!/usr/bin/sh
# This script should be run to quick install alinxt

# Make directory if does not exist
if [ -d "/tmp/alinxt" ]; then
  echo Removing preexisting folder
  rm -rf /tmp/alinxt
fi

echo Setting up directory
sleep 1
mkdir /tmp/alinxt

# Download from source to tmp

echo Downloading source files from GitHub...
wget --quiet -O /tmp/alinxt/main.cpp https://raw.githubusercontent.com/Velox0/Alinxt/main/main.cpp
wget --quiet -O /tmp/alinxt/modules.hh https://raw.githubusercontent.com/Velox0/Alinxt/main/modules.hh
wget --quiet -O /tmp/alinxt/version.hh https://raw.githubusercontent.com/Velox0/Alinxt/main/version.hh
wget --quiet -O /tmp/alinxt/alinxt.6 https://raw.githubusercontent.com/Velox0/Alinxt/main/alinxt.6

# Compile code and zip man page

echo Compiling...
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

# clear up files

echo Clearing up files.
rm -rf /tmp/alinxt

echo Alinxt is installed.
