#include <stdio.h>
void switchByValue(int, int);
void switchByPointer(int*, int*);
void main()
{
	printf("Hello 1056 to DS!\n");
	int a = 7;
	int b = 8;
	printf("Before: a=%d, b=%d\n", a, b);
	switchByValue(a, b);
	printf("After by value: a=%d, b=%d\n", a, b);
	switchByPointer(&a, &b);
	printf("After by pointer: a=%d, b=%d\n", a, b);
}
void switchByPointer(int* x, int* y)
{
	int z = *x;
	*x = *y;
	*y = z;
}
void switchByValue(int x, int y)
{
	int z = x;
	x = y;
	y = z;
}