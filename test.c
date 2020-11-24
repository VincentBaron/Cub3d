#include <stdio.h>

int main()
{
	int x;
	int y;

	x = -1;
	y = 0;

	if ((x || y) != 0)
		printf("yolo");
	if (x == -1 || y == -1)
		printf("yolo2");
}