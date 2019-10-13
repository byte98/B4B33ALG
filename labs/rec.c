#include <stdio.h>

int ff(int x, int y)
{
	if (y > 0) return (x * ff(x, y-1));
	return 1;
}

void st_ff(int n)
{
	if (n < 1) return;
	printf("1");
	st_ff(n - 1);
	printf("22");
}

void print_seq(int n, int c)
{
	if (c > n) return;
	printf("%d ", c);
	print_seq(n, c++);
	printf("%d ", c);
	return;
}

int main()
{
	printf("%d\n", ff(2, 5));
	st_ff(3);
	printf("\n");
//	print_seq(5, 1);
	printf("\n");
	return 0;
}
