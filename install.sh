g++ -O3 ./main.cpp -o /usr/bin/alinxt
gzip -fk ./alinxt.6
mv ./alinxt.6.* /usr/share/man/man6/
