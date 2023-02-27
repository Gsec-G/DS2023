#include <stdio.h>
void switchByValue(int, int);
void switchByPtr(int*, int*);
void main()
{
	printf("Hello 1058 to DS!\n");
	int a = 7;
	int b = 8;
	printf("Before: a=%d, b=%d\n", a, b);
	switchByValue(a, b);
	printf("After value: a=%d, b=%d\n", a, b);
	switchByPtr(&a, &b);
	printf("After pointer: a=%d, b=%d\n", a, b);
}
void switchByValue(int x, int y)
{
	int z = x;
	x = y;
	y = z;
}
void switchByPtr(int* x, int* y)
{
	int z = *x;
	*x = *y;
	*y = z;
}
