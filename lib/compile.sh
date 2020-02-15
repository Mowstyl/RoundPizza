rm pizza.o
rm pizza.dll
gcc -c -fopenmp -std=gnu11 -Wall -Wextra -Werror -pedantic-errors -m64 -fpic -o pizza.o pizza.c
gcc -shared -o pizza.dll pizza.o -fopenmp -std=gnu11 -Wall -Wextra -Werror -pedantic-errors -m64 -lm
