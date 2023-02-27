#include <stdio.h>
void switchByValue(int*, int*, int*);
void switchByPointer(int**, int**);
void main()
{
	printf("Hello 1066 to DS!\n");
	int a = 7;
	int b = 8;
	int* pa = &a;
	int* pb = &b;
	int* vec[2];
	vec[0] = pa; vec[1] = pb;
	printf("Before: a=%d, b=%d\n", a, b);
	switchByValue(pa, pb, vec);
	printf("After value: a=%d, b=%d\n", a, b);
	switchByPointer(&pa, &pb);
	printf("After poiner: a=%d, b=%d\n", a, b);


}
void switchByPointer(int** px, int** py)
{
	int z = **px;
	**px = **py;
	**py = z;
}
void switchByValue(int* px, int* py, int* array)
{
	int pz = *px;
	*px = *py;
	*py = pz;

}