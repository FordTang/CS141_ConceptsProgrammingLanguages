#include <stdio.h>
#include <stdlib.h>

// TODO: define add, sub, mul, divi as functions which take two integer arguments and return the result
// we can't use "div" because it is already defined

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int mul(int a, int b)
{
    return a * b;
}

int divi(int a, int b)
{
    return a / b;
}

// TODO: define function array here. funcs[0] will point to add and so on

int (*funcs[4])(int, int) = {add, sub, mul, divi};

int main(int argc, char **argv) {
    if(argc != 4) {
		printf("Call: %s [op from 0-3] a b\n", argv[0]);
		printf("op is either 0 (for add), 1 (for sub), 2 (for mul), or 3 (for divi)\n");
		printf("a and b are the arguments\n");
		printf("%s 1 5 3 would return 2 (because it is 5-3)\n", argv[0]);
		return 1;
	}
	int op = atoi(argv[1]);
	int a = atoi(argv[2]);
	int b = atoi(argv[3]);
	printf("%i\n", (funcs[op])(a, b));
}
