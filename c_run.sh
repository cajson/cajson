set -x
./cj prog/c/$1.cj -o prog/c/$1.c
gcc -I ./sys/ prog/c/$1.c -o a.exe
./a.exe

