cls
del pizza.o
del pizza.dll
gcc -c -std=iso9899:1999 -Wall -Wextra -Werror -pedantic-errors -m64 -fpic -o pizza.o pizza.c
gcc -shared -o pizza.dll pizza.o -std=iso9899:1999 -Wall -Wextra -Werror -pedantic-errors -m64
pause