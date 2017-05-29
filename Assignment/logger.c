#include <time.h>
#include <stdio.h>
#include <string.h>

//#include "files.h"



void logThis(char logMsg[100], char logFile[20]){
	char formattedTime[20];
	char logged[512];
	struct tm tm;
	time_t time1;
	time1 = time(NULL);
	tm = *localtime(&time1);
	strftime(formattedTime, sizeof formattedTime, "%Y-%m-%d %H:%M:%S - ", &tm);//formats the time
	//printf("%s\n",asctime(localtime(&time1)));//debug
	//printf("%s\n",formattedTime);//debug
	strcpy(logged, formattedTime);
	strcat(logged, logMsg);
	FILE *fp;
	fp = fopen(logFile, "a");
	fputs(logged, fp); 
	//fprintf(fp, "%s %s\n", formattedTime, logMsg);
	fclose(fp);
}

//add logger startup which cleans log file etc..
void initLogger(char logFile[20]){
	FILE *fp;
	fp = fopen(logFile, "w");//clears log file
	fputs("",fp);
	fclose(fp);
	logThis("Program started up...\n", logFile);	
	return;

}
