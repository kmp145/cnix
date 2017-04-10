#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "io.h"
#include "logger.h"
#include "files.h"

/*
loadSharing list(){
	if (sharing list exists) {
		if (sharing list cannot be read) {
			Display error message to user
			log event
			terminate program
		}
		else {
			for (files in sharing list){
				read list
				If (file doesn’t exist or can’t be read) {
					Remove file from list
					Display message to user
				}
			}
	
		}
	}
	else{
		create sharing list file
		populatelist()
	}
}
FOR SHARING LIST UPDATING FILE: WRITE ALL GOOD RECORDS TO NEW FILE DELETE OLD RENAME NEW.
*/

void saveSharingList(shareList_t sharingList){/*
	FILE *fp;
	int counter = 0;
	char listNum[60];
	fp=fopen("sharingList.txt", "w");
	while (strcmp(sharingList.fileName[counter],"NO")){//"NO" is a default value given to indicate when no more files are left, however the loop is off by 1
		strcpy(listNum,sharingList.fileName[counter]);
		strcat(listNum,":");
		strcat(listNum,sharingList.userName[counter]);
		strcat(listNum,":");
		strcat(listNum,sharingList.permissionLevel[counter]);
		strcat(listNum,"\n");
		//fprintf(stdout,"%s\n",listNum);//debug
		fputs(listNum,fp);
		counter ++;		
	}
	fclose(fp);*/
}

shareList_t createSharingList(settings_t settings){
/*

	for files in directory{
		check if its readable
			add to filename list
			default to user name x
			default to not sharable
	}
		
*/
	int counter = 0, i;
	shareList_t shareList;
	for (i = 0; i<10;i++){//sets defaults to NO it help later on
		strcpy(shareList.fileName[i],"NO");
	}
	struct dirent *entry;
	DIR *dir = opendir("sharingDir");
	while ((entry = readdir(dir))!=NULL){
		
		if(!(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0 || strcmp(entry->d_name,"\0")==0 )){
			//fprintf(stdout, "%s\n", entry->d_name);//debug
			strcpy(shareList.fileName[counter], entry->d_name);
			strcpy(shareList.userName[counter], settings.username);
			strcpy(shareList.permissionLevel[counter], "NOTSHARED");			
		}
		counter ++;
		
		
	}
	closedir(dir);
	saveSharingList(shareList);	
	return shareList;
	
}

shareList_t loadSharingList(settings_t settings){
	FILE *fp;
	char buffer[251], filename[12], username[20], *permissionlevel, delimitor[2] = ":", logMsg[45];
	shareList_t sharingList;
	int counter = 0, errorFound = FALSE;
	if(!access("./sharingList.txt", F_OK)){
		//sharing list exists	
		if(!access("./sharingList.txt", R_OK)){
			//sharing list is readable
			fp=fopen("sharingList.txt", "r");
			while (fgets(buffer, 250, fp) != NULL){
				fprintf(stdout, "%s\n THIS IS BUFFER", buffer);//debug
				permissionlevel = strtok(buffer,delimitor);
				strcpy(filename,permissionlevel);
				fprintf(stdout,"%s\n THIS IS FILENAME",filename);//debug
				permissionlevel = strtok(NULL,delimitor);
				strcpy(username,permissionlevel);
				fprintf(stdout, "%s\n THIS IS USERNAME",username);//debug
				permissionlevel = strtok(NULL, delimitor);
				fprintf(stdout,"%s\n THIS IS PERMISSIONLEVEL",permissionlevel);//debug
				if (!access(filename, F_OK) && !access(filename, R_OK)){//if file in file list is valid
					strcpy(sharingList.fileName[counter],filename);
					strcpy(sharingList.userName[counter],strtok(username,"\n"));
					strcpy(sharingList.permissionLevel[counter],permissionlevel);
					fprintf(stdout, "%s is a valid file on the sharing list\n", filename);
				}
				else{//if the file is invalid
					strcpy(logMsg, "Invalid file detected! Dropping ");
					strcat(logMsg, filename);
					strcat(logMsg, " from sharing list...");
					fprintf(stdout, "%s\n",logMsg);
					errorFound = TRUE;//signals to drop invalid files later on
					logThis(logMsg,settings.logFile);
				}
			}
			fprintf(stdout,"out of the loop");
		}
		else{
			//logThis("Sharing list is not readable, creating a new list...",settings.logFile);
			sharingList = createSharingList(settings);
		}
		
		
	}
	else{
		//printf("File does not exist");//debug
		//sharing list doesn't exist
		sharingList = createSharingList(settings);
	}
	if (errorFound){
		//rewrite the sharingList.txt using only sharingList to get rid of errors
		//saveSharingList(sharingList);
	}
	fclose(fp);
	return sharingList;
}

int loadSettings(settings_t *settings){//change freads to fgets
	char buffer[150], label[20], *value, delimitor[2] = ":";
	FILE *fp;
	if((fp=fopen("settings.conf", "r"))){//if the file exists add if readable
		//strcpy(settings->username,"username test");
		while (fgets(buffer,150,fp)){
			if (buffer[0] != '#' && buffer[0] != '\0'){
				value = strtok(buffer,delimitor);
				strcpy(label,value);
				value = strtok(NULL,delimitor);
				if(!strcmp(label, "username")){
					if (value != NULL){
						value[strlen(value)-1] = '\0';//remove trailing \n NEEDS FIXING
						strcpy(settings->username,value);
						//assign
					}
					else
						printf("invalid");
						//log
				}

				else if(!strcmp(label, "ip")){
					if (value != NULL){
						//assign
						strcpy(settings->IPAddress,value);
					}
					else
						printf("invalid");
						//log
				}
				
				else if(!strcmp(label, "logfile")){
					if (value != NULL){
						//assign
						strcpy(settings->logFile,value);
					}
					else
						printf("invalid");
						//log
				}
				else if(!strcmp(label, "port")){
					if (value != NULL){
						settings->port = value;//this needs updating
					}
					else
						printf("invalid");
						//log
				}
				else{
					//when invalid setting detected
				}
			}
		}
	}
	else{//if the file does not exist return create file with default settings
		//fprintf(fp, "%s\n","defaultSettings");//debug
		logThis("Default settings were used since there was no conf file found.",settings->logFile);	
	}
	return 0;
}

int main(){
	//intialiseLogger()
	settings_t settings = {"User","192.168.0.12","./log.txt",777};
	shareList_t sharingList;
	loadSettings(&settings);
	sharingList = loadSharingList(settings);
	//printf("%s\n",settings.username);//debug
	logThis("Program finished with no fatal errors.",settings.logFile);
	return 0;
}
