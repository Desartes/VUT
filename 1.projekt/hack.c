#include <stdio.h>
int main()
{
	int p = 42,
		*pi = (int *)malloc(10);

	for (int i = 0; 1 ; ++i) {
			printf("Adresa: 0x%x\t%d\n", pi + i, *(pi + i));
	}
	return 0;
}