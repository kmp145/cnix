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

void saveFriends(friendsList_t **friends, int counter){
	
	FILE *fp;
	int i = 0;
	char output[256], portstr[10];
	fp = fopen("friendsList.txt",  "w");
	//fprintf(stdout, "%d COUNTER", counter);
	for (i = 0; i < counter; i++){
		output[0] = 0;
		strcat(output,friends[i]->username);
		//printf("%s\n",output);
		strcat(output,":");
		//printf("%s\n",output);
		strcat(output,friends[i]->IPAddress);
		//printf("%s\n",output);
		strcat(output,":");
		//printf("%s\n",output);
		sprintf(portstr, "%d", friends[i]->port);
		strcat(output, portstr);
		strcat(output, "\n");
		//printf("%s\n",output);
		fputs(output,fp);
	}
	fclose(fp);
}

void maintainFriends(friendsList_t **friends, int counter, int flag){

	if (flag == 0){//Add friend
		char *username, *IPAddress;
		int port=0;
		username = malloc(sizeof(char)*20);
		IPAddress = malloc(sizeof(char)*17); 
	

		inputStr(username, "Name:\t", 20, 1);
		fprintf(stdout, "\n");
		inputStr(IPAddress, "IP:\t", 17, 1);
		fprintf(stdout, "\n");
		port = inputInt(&port,"Port:\t",8, 1);
	
		strcpy(friends[counter]->username, username);//ADD ERROR CHECK 
		strcpy(friends[counter]->IPAddress, IPAddress);
		friends[counter]->port = port;
		counter ++;
		free(username);
		free(IPAddress);
		saveFriends(friends, counter);
	
		fprintf(stdout, "\n\nSuccessfully added! %s\n",username);
	}
	else if(flag ==1){///EDIT FRIENDS
		fprintf(stdout, "Not added yet!\n");
	}
	return;
}

void loadFriends(friendsList_t **friends, settings_t settings, int flag){
	/*
	#################################################
	#			FLAGS			#
	#		0 = Add Friend			#
	#		1 = Edit friends		#
	#		3 = Only load friends		#
	##################################################*/

	FILE *fp;
	//friendsList_t friends[100];
	char buffer[256], delimitor[2] = ":", portstr[10];
	int counter = 0;
	
	if((fp = fopen("friendsList.txt","r"))){
		while(fgets(buffer,512,fp) != NULL){
			if (buffer[0] != '\n'){
				//fprintf(stdout, "%s\n",buffer);//DEBUG
			
				strcpy(friends[counter]->username, strtok(buffer,delimitor));
				strcpy(friends[counter]->IPAddress, strtok(NULL,delimitor));
				strcpy(portstr, strtok(NULL,delimitor));
				friends[counter]->port = atoi(portstr);
				counter ++;
			}
		}//end of while
	}//end of if
	//saveFriends(friends, counter);//debug
	if(flag == 0 || flag ==1){
		maintainFriends(friends, counter, flag);
	}

	return;
}



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
void saveSharingList(shareList_t **sharingList, int counter){
	//fprintf(stdout, "In save share list counter:\t%d\n", counter);
	FILE *fp;
	int i;
	char output[512];
	//counter = &shareCounter;
	fp=fopen("sharingList.txt", "w");
	//fprintf(stdout, "%s xcxcx\n", sharingList[2]->fileName);//DEBUG
	for(i = 0; i < counter; i++){//KNOWN BUG CATS fileLOCATION TWICE
		output[0] = 0;
		//printf("%s\n",output);
		//fprintf(stdout, "fileLoc: %s\n",sharingList[i].fileLocation);
		strcat(output,sharingList[i]->fileLocation);
		//printf("%s\n",output);
		strcat(output,":");
		//printf("%s\n",output);
		strcat(output,sharingList[i]->fileName);
		//printf("%s\n",output);
		strcat(output,":");
		//printf("%s\n",output);
		strcat(output,sharingList[i]->userName);
		//printf("%s\n",output);
		strcat(output,":");
		//printf("%s\n",output);
		//strcat(output,sharingList[i].permissionLevel[0]);
		//output[sizeof(output)] = sharingList[i].permissionLevel[0];
		if(sharingList[i]->permissionLevel[0] == 49) {
			strcat(output,"1");
		}
		else{
			strcat(output,"0");
		}
		//printf("%s\n",output);
		strcat(output, "\n");
		//fprintf(stdout, "This is perm: %s", sharingList[i].permissionLevel);
		//fprintf(stdout, "Loop: %d. Writing: %s\n",i, output);
		fputs(output,fp);
	}
	fclose(fp);
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

void maintainSharingList(shareList_t **sharingList, int counter, int flag){

	/*
	#################################################
	#			FLAGS			#
	#		0 = Add File			#
	#		1 = Edit permission		#
	##################################################*/

	
	char permStr[256], userChoice[10];
	int i, y;

	if(flag == 0){//ADD FILE
		FILE *fp;
		char *targetFile, *targetPeer, *fileNickname;
		targetFile = malloc(sizeof(char)*256);
		targetPeer = malloc(sizeof(char)*20);
		fileNickname = malloc(sizeof(char)*20);
		inputStr(targetFile, "Input the location of the file you would like to add:\t", 257, 1); 
		if((fp=fopen(targetFile, "r"))){
			fprintf(stdout, "%s is a valid file...\n",targetFile);
			inputStr(fileNickname, "Enter the name of the file:\t", 20,1);
			inputStr(targetPeer, "Who would you like to share it with?", 20, 0);
			if(fileNickname[0] != '\0' && targetPeer[0] != '\0'){
				strcpy(sharingList[counter]->fileLocation, targetFile);
				strcpy(sharingList[counter]->fileName, fileNickname);
				strcpy(sharingList[counter]->userName, targetPeer); 
				fprintf(stdout, "%s successfully added!\n", fileNickname);
			}
		}
		else{
			fprintf(stdout, "%s is an invalid file...\n",targetFile);
		}
		free(targetFile);
		free(targetPeer);
		free(fileNickname);
	}
	else if(flag == 1){//EDIT FILE:
		int x;
		for (i = 0; i < counter; i++){
			//fprintf(stdout, "%d. %s ", i, sharingList[i]->fileName);
			
			//fprintf(stdout, "%d\n",sharingList[i].permissionLevel[0]);
			if(sharingList[i]->permissionLevel[0] == 49) {
				sprintf(permStr, "is shared with %s.\n", sharingList[i]->userName);
			}
			else{
				sprintf(permStr, "is not shared with %s.\n", sharingList[i]->userName);
			}

			fprintf(stdout, "%d. %s %s", i+1, sharingList[i]->fileName, permStr);
		}
		//x = inputInt(z, "What permission would you like to change?", 2, 0);
		fprintf(stdout, "What permission would you like to change?\n");
		fgets(userChoice, 10, stdin);// CHANGE TO IO
		x = atoi(userChoice);//add error handling
		x -= 1;
		fprintf(stdout, "Would you like:\n1. Not share %s with %s\n2. Share %s with %s\n", sharingList[x]->fileName, sharingList[x]->userName, sharingList[x]->fileName, sharingList[x]->userName);
	
		fgets(userChoice, 10, stdin);//CHANGE TO IO
		y = atoi(userChoice);//add error handling
		y-= 1;
		if (y == 0){
			strcpy(sharingList[x]->permissionLevel, "0");
			saveSharingList(sharingList, counter);
			fprintf(stdout, "Permission successfully changed to not share.\n");
			return;
		}
		else if( y == 1){
			strcpy(sharingList[x]->permissionLevel, "1");
			saveSharingList(sharingList, counter);
			fprintf(stdout, "Permission successfully changed to share.\n");
			return;
	
		}
		else{
			fprintf(stdout, "Invalid permission entered, no changes will be made.\n");
			return; //CHANGE
		}
	}
	
}


void loadSharingList(shareList_t **sharingList,settings_t settings, int flag){
	//shareList_t sharingList[100];
	/*
	#################################################
	#			FLAGS			#
	#		0 = Add File			#
	#		1 = Edit permission		#
	#		3 = Only load files		#
	##################################################*/
	char buffer[512], delimitor[2] = ":", fileLocation[256], filename[20], username[20], permission[2];
	int error = FALSE;
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
					strcpy(sharingList[counter]->fileLocation,fileLocation);
					strcpy(sharingList[counter]->fileName,filename);
					strcpy(sharingList[counter]->userName,username);
					strcpy(sharingList[counter]->permissionLevel,permission);
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
	if(flag == 0 || flag == 1){
		maintainSharingList(sharingList,counter, flag);
	}
	return;
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

void mainMenu(shareList_t **sharingList,settings_t settings, friendsList_t **friends){
	while (1){
		int x=0;
		char *menuOptions[4];
		fprintf(stdout, "Bug exists here, to use menu options enter first menu number followed by sub menu option. E.G. enter \"21\" to add a new friend.\n");//KNOWN BUG HERE
		fprintf(stdout, "What would you like to do?\n");
		
		menuOptions[0] = "Edit sharing list";
		menuOptions[1] = "Edit Friends";
		menuOptions[2] = "Download a file";
		menuOptions[3] = "Exit";
		displayMenu(menuOptions, 4, 0);
		x = inputInt(&x,"",2,0);
		
		if (x==0){//Edit share list
			char *editShareMenu[2];
			int y = 0;
			editShareMenu[0] = "Add a file";
			editShareMenu[1] = "Edit permissions to a file";
			displayMenu(editShareMenu, 2, 0);
			//fprintf(stdout, "\n");
			y = inputInt(&y,"asd",2,0);
			if (y == 0 || y == 1){
				loadSharingList(sharingList, settings, y); 
			}

		}
		else if(x==1){//Edit friends
			char *editFriendsMenu[2];
			int y = 0;
			editFriendsMenu[0] = "Add a friend";
			editFriendsMenu[1] = "Edit an existing friend";
			displayMenu(editFriendsMenu, 2, 0);
			y = inputInt(&y,"",4,0);
			if (y == 0 || y == 1){
				loadFriends(friends, settings, y); 

			}
		}
		else if(x==2){//Download file

		}
		else if(x==3){//exit
			return;
		}
		else{
			fprintf(stdout, "Invalid input!\n");
		}
	}	
}

int main(){
	//intialiseLogger()
	int i = 0, maxShares = 25, maxFriends = 25;
	settings_t settings = {"User","192.168.0.12","./log.txt",777};
	loadSettings(&settings);//gets settings
	
	//Intialise sharing List and friends list
	shareList_t *sharingList[maxShares];
	friendsList_t *friends[maxFriends];
	for ( i = 0; i<maxFriends+1;i++){
		friends[i] = malloc(sizeof(friendsList_t));
	}
	for ( i = 0; i<maxShares+1;i++){
		sharingList[i] = malloc(sizeof(shareList_t));
	}
	
	loadSharingList(sharingList,settings, 3);//gets sharing List
	loadFriends(friends, settings, 3);
	
	mainMenu(sharingList, settings, friends);
	logThis("Program finished with no fatal errors.",settings.logFile);
	return 0;
}
