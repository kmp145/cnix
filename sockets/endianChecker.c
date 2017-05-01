#include <stdio.h>

int main() {
	
	int i, test = 0x04030201;
	char *tp;
	tp = &test;
	for (i=0;i<4;i++)
		fprintf(stdout, "Byte %d contains: %d\n",i, *tp++);
	return 0;
}
