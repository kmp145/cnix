#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "logger.h"

struct settings_t{
	char placeholder[20];
};

struct settings_t loadSettings(){//change freads to fgets
	struct settings_t settings;
	FILE *fp;
	fp = fopen("settings.conf", "r");
	if(fp != NULL){//if the file exists add if readable
		fread(&settings, sizeof(settings), 1, fp);//modify read for comments/errors
		fclose(fp);
	}
	else{//if the file does not exist return create file with default settings
		fp = fopen("settings.conf", "w");
		strcpy(settings.placeholder,"defaultSettings");
		fprintf(fp, "%s\n","test");
		fclose(fp);
		logThis("Default settings were used since there was no conf file found.","log.txt");	
	}
	return settings;
}

int main(){
	struct settings_t settings;
	settings = loadSettings();
	printf("%s\n",settings.placeholder);
	return 0;
}
