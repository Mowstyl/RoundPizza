cls
del pizza.o
del pizza.dll
gcc -c -fopenmp -std=c99 -Wall -Wextra -m64 -fpic -o pizza.o pizza.c
gcc -shared -o pizza.dll pizza.o -fopenmp -std=c99 -Wall -Wextra -Werror -pedantic-errors -m64 -lm
pause