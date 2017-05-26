#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

typedef struct shareList_t{
	char fileLocation[256];
	char fileName[20];
	char userName[20];
	char permissionLevel[2];//1 = shared, 0 = not shared	
} shareList_t;

void saveSharingList(shareList_t *sharingList, int counter){
	fprintf(stdout, "In save share list counter:\t%d\n", counter);
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

}

shareList_t *loadSharingList(){
	shareList_t sharingList[100];
	char buffer[512], delimitor[2] = ":", fileLocation[256], filename[20], username[20], permission[2];
	int  error = 0;
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
					error = 1;
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
		//logThis("Some Invalid files were dropped from sharingList.txt",settings.logFile);	
	}
	//fprintf(stdout,"%d\n",counter);
	saveSharingList(sharingList, (uintptr_t)counter);
	//maintainSharingList(sharingList,counter);
	return sharingList;//change
}

int main(){
	//ADD FILE:
	shareList_t *sharingList;
	sharingList = loadSharingList();
	
	return 0;
}

/*
./testTransfer.txt:testTransfer.txt:Peer1:1
./testTransfer.txt:testTransfer.txt:Peer2:0
./testTransfer.txt:testTransfer.txt:Peer3:1
./testTransfer.txt:testTransfer.txt:Peer4:0
*/
