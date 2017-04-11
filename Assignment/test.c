#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(){/*
	char str[150] = "username:test", ch = ':', *ret;
	ret = strchr(str,ch);
	ret ++;
	fprintf(stdout, "%s\n",ret);	
	struct dirent *entry;
	DIR *dir = opendir("sharingDir");
	entry = readdir(dir);
	printf("%s\n",entry->d_name);
	while ((entry = readdir(dir)) != NULL) {
        printf("%s\n",entry->d_name);
    	}

   	 closedir(dir);*/
	char buffer[251];
	FILE *fp;
	fp = fopen("sharingList.txt", "r");
	while(fgets(buffer, 250, fp)!= NULL){
		fprintf(stdout,"%s\n",buffer);
	}
	return 0;
}
