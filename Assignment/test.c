#include <stdio.h>
#include <string.h>

int main(){
	char str[150] = "username:test", ch = ':', *ret;
	ret = strchr(str,ch);
	ret ++;
	fprintf(stdout, "%s\n",ret);	
}
