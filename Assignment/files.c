#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdint.h>
#include <inttypes.h>
#include "io.h"
#include "logger.h"
#include "files.h"


//shareList_t loadSharingList(shareList_t sharingList[100]);

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
void saveSharingList(shareList_t *sharingList, int counter){
	//fprintf(stdout, "In save share list counter:\t%d\n", counter);
	FILE *fp;
	int i;
	char output[512];
	//counter = &shareCounter;
	fp=fopen("sharingList.txt", "w");
	fprintf(stdout, "%s xcxcx\n", sharingList[2].fileName);
	for(i = 0; i < counter; i++){//KNOWN BUG CATS fileLOCATION TWICE
		strcpy(output, "");
		strcat(output,sharingList[i].fileLocation);
		strcat(output,":");
		strcat(output,sharingList[i].fileName);
		strcat(output,":");
		strcat(output,sharingList[i].userName);
		strcat(output,":");
		strcat(output,sharingList[i].permissionLevel);
		fputs(output,fp);
	}
	/*	
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
	fclose(fp);
*/
}
/*
shareList_t createSharingList(settings_t settings){


	for files in directory{
		check if its readable
			add to filename list
			default to user name x
			default to not sharable
	}
		

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
	return 5;shareList;
	
}*/

void maintainSharingList(shareList_t *sharingList, int counter){
	
	//ADD FILE:
	FILE *fp;
	char targetFile[512], permStr[256], userChoice[10];
	int i = 0, x, y;
	fprintf(stdout, "%d Input file LOCATION:\t",counter);//CHANGE TO something from io.c
	fgets(targetFile, 512, stdin);//CHANGE TO io.c
	if((fp=fopen(targetFile, "r"))){//Doesn't work properally
		fprintf(stdout, "%s is a valid file...\n",targetFile);
	}
	else{
		fprintf(stdout, "%s is an invalid file...\n",targetFile);
	}

	//EDIT FILE:
	fprintf(stdout, "What permission would you like to change?\n");
	for (i = 0; i < counter; i++){
		
		//fprintf(stdout, "%d\n",sharingList[i].permissionLevel[0]);
		if(sharingList[i].permissionLevel[0] == 49) {
			sprintf(permStr, "is shared with %s.\n", sharingList[i].userName);
		}
		else{
			sprintf(permStr, "is not shared with %s.\n", sharingList[i].userName);
		}

		fprintf(stdout, "%d. %s %s", i+1, sharingList[i].fileName, permStr);
	}
	
	fgets(userChoice, 10, stdin);// CHANGE TO IO
	x = atoi(userChoice);//add error handling
	
	fprintf(stdout, "Would you like:\n1. Share %s with %s\n2. Not share %s with %s\n", sharingList[x].fileName, sharingList[x].userName, sharingList[x].fileName, sharingList[x].userName);
	
	fgets(userChoice, 10, stdin);//CHANGE TO IO
	y = atoi(userChoice);//add error handling
	y-= 1;
	if (y == 1 || y == 0){
		sprintf(sharingList[x].permissionLevel, "%d", y);
		saveSharingList(sharingList, counter);
		fprintf(stdout, "Permission successfully changed.\n");
	}
	else{
		fprintf(stdout, "Invalid permission entered, no changes will be made.\n");
	}
	
	return;
}


shareList_t *loadSharingList(settings_t settings){
	shareList_t sharingList[100];
	char buffer[512], delimitor[2] = ":", fileLocation[256], filename[20], username[20], permission[2];
	int  error = FALSE;
	int counter = 0;
	FILE *fp;
	if((fp = fopen("sharingList.txt","r"))){
		while(fgets(buffer,512,fp) != NULL){
			if (buffer[0] != '\n'){
				//fprintf(stdout, "%s",buffer);//DEBUG
			
				strcpy(fileLocation, strtok(buffer,delimitor));
				strcpy(filename, strtok(NULL,delimitor));
				strcpy(username, strtok(NULL,delimitor));
				strcpy(permission, strtok(NULL,delimitor));


				if( access(fileLocation, R_OK) != -1 && (!strcmp(permission,"0\n") || !strcmp(permission,"1\n"))){//if file and permission is valid
					//fprintf(stdout, "%s is a valid file with vaild permissions\n", filename);//DEBUG
					strcpy(sharingList[counter].fileLocation,fileLocation);
					strcpy(sharingList[counter].fileName,filename);
					strcpy(sharingList[counter].userName,username);
					strcpy(sharingList[counter].permissionLevel,permission);
					counter += 1;
				}
				else{//if file is invalid
					error = TRUE;
					//LOG THIS
				}
			}
		}//end of while read file
	fclose(fp);
	}//end of if open file
	else{
		fp = fopen("sharingList.txt", "w");
		fclose(fp);
	}
	if(error){// if an invalid file was found in list
		logThis("Some Invalid files were dropped from sharingList.txt",settings.logFile);	
	}
	//fprintf(stdout,"%d\n",counter);
	saveSharingList(sharingList, (uintptr_t)counter);
	maintainSharingList(sharingList,counter);
	return sharingList;//change
}

void saveSettings(settings_t *settings){
	char temp[20], output[256];
	FILE *fp;
	fp = fopen("settings.conf","w");
	strcpy(output, "username:");
	strcat(output,settings->username);
	strcat(output, "\nip:");
	strcat(output,settings->IPAddress);
	strcat(output, "\nlogfile:");
	strcat(output,settings->logFile);
	strcat(output, "\nport:");
	sprintf(temp,"%d",settings->port);
	strcat(output,temp);
	strcat(output,"\n");
	fputs(output,fp);
	fclose(fp);

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
						//printf("invalid");//debug
						logThis("Invalid username setting detected, using default value.",settings->logFile);
				}

				else if(!strcmp(label, "ip")){
					if (value != NULL){
						//assign
						strcpy(settings->IPAddress,value);
					}
					else
						//printf("invalid");//debug
						logThis("Invalid IP address setting detected, using default value.",settings->logFile);
				}
				
				else if(!strcmp(label, "logfile")){
					if (value != NULL){
						//assign
						strcpy(settings->logFile,value);
					}
					else
						//printf("invalid");//debug
						logThis("Invalid logfile setting detected, using default value.",settings->logFile);
				}
				else if(!strcmp(label, "port")){
					if (value != NULL){
						settings->port = atoi(value);//this needs updating
					}
					else
						//printf("invalid");//debug
						logThis("Invalid port setting detected, using default value.",settings->logFile);
				}
				
				else{
					//when invalid setting detected
				}
				fclose(fp);
			}	
		}
	}
	else{//if the file does not exist return create file with default settings
		//fprintf(fp, "%s\n","defaultSettings");//debug
		logThis("Default settings were used since there was no conf file found.",settings->logFile);
		saveSettings(settings);	
		
	}
	
	return 0;
}

int main(){
	//intialiseLogger()
	settings_t settings = {"User","192.168.0.12","./log.txt",777};
	shareList_t *sharingList;
	loadSettings(&settings);//gets settings
	sharingList = loadSharingList(settings);//gets sharing List
	//maintainSharingList(sharingList);
	//fprintf(stdout, "%s\n",sharingList[0].fileName);
	//fprintf(stdout,"%s\n%s\n%s\n%d\n",settings.username, settings.IPAddress, settings.logFile, settings.port);
	//REPLACE BELOW WITH DISPLAYMENU()
	/*while (1){//This section is supposed to be in a function displayMeun(), located in io.c however i would get an error about multiple definitions of functions in that c file
		fprintf(stdout,"What would you like to do?\n1)Display current user settings.\n2)Change a user setting.\n3)Display contents of the sharing list\n4)Change a file's permission.\n99)Exit.\n");
		//userChoice = inputInt("What would you like to do?\n1)Display current user settings.\n2)Change a user setting.\n3)Display contents of the sharing list\n4)Change a file's permission.\n99)Exit.\n");
		fgets(userChoice,3,stdin);
		fprintf(stdout,"%s\n",userChoice);
		if(strcmp(userChoice,"1")){
			//display current user
			fprintf(stdout,"tasr");		
		}
		else if(strcmp(userChoice,"2")){
			//change user settings	
		}
		else if(strcmp(userChoice,"3")){
			//display contents of sharing list		
		}
		else if(strcmp(userChoice,"4")){
			//change file permission		
		}
		else if(strcmp(userChoice,"99")){
			//exit	
			break;	
		}
		else
			fprintf(stdout,"Invalid choice!");
		
		
	}*/ 
	logThis("Program finished with no fatal errors.",settings.logFile);
	return 0;
}
