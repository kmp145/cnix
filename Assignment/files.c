#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "logger.h"

struct settings_t{
	char placeholder[20];
};

struct settings_t loadSettings(){
	struct settings_t settings;
	FILE *fp;
	fp = fopen("settings.conf", "r");
	if(fp){//if the file exists and is readable
		fread(&settings, sizeof(settings), 1, fp);
		fclose(fp);
	}
	else{//if the file does not exist return create file with default settings
		fopen("settings.conf", "w");
		strcpy(settings.placeholder,"defaultSettings");
		fwrite(&settings, sizeof(settings), 1, fp);
		fclose(fp);	
	}
	return settings;
}

int main(){
	struct settings_t settings;
	settings = loadSettings();
	printf("%s\n",settings.placeholder);
	return 0;
}
