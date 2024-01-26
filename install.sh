g++ -O3 ./main.cpp -o /usr/bin/alinxt
gzip -fk ./alinxt.6

manpath="/usr/share/man/man6/"
if [ ! -d "$manpath" ]; then
  # Create the path
  mkdir -p "$manpath"
fi

mv ./alinxt.6.* $manpath
