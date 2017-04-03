#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "logger.h"
#include "files.h"


int loadSettings(settings_t *settings){//change freads to fgets
	char buffer[150], label[20], *value, delimitor[2] = ":";
	FILE *fp;
	if((fp=fopen("settings.conf", "r"))){//if the file exists add if readable
		strcpy(settings->username,"username test");
		while (fgets(buffer,150,fp)){
			if (buffer[0] != '#' && buffer[0] != '\0'){
				fprintf(stdout, "%s\n", buffer);
				value = strtok(buffer,delimitor);
				strcpy(label,value);
				value = strtok(NULL,delimitor);
				printf("%s is %s\n",label,value);
				if(!strcmp(label, "username"){
					if (value != NULL){
						//assign
					}
					else
						//log
				}
			}
		}
	}
	else{//if the file does not exist return create file with default settings
		fp = fopen("settings.conf", "w");
		//strcpy(settings.username,"defaultSettings");
		fprintf(fp, "%s\n","defaultSettings");
		fclose(fp);
		logThis("Default settings were used since there was no conf file found.","log.txt");	
	}
	return 0;
}

int main(){
	settings_t settings = {"User","192.168.0.12",777,"./log.txt"};
	loadSettings(&settings);
	printf("%s\n",settings.username);
	logThis("Program finished with no errors.",settings.logLocation);
	return 0;
}
