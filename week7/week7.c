#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct data_t{
	char *word;
	int freq;
} data_t;

int main(){
	int maxLength = 255;
	char line[maxLength];
	data_t test;
	FILE *fp;
	fp = fopen("file.txt","r");
	while(fgets(line, maxLength, fp)){
		fprintf(stdout, "%s\n",line);

	}

}
