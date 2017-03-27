#include <time.h>
#include <stdio.h>//debugging


void logThis(char logMsg[100], char logFile[20]){
	char formattedTime[20];
	struct tm tm;
	time_t time1;
	time1 = time(NULL);
	tm = *localtime(&time1);
	strftime(formattedTime, sizeof formattedTime, "%Y-%m-%d %H:%M:%S", &tm);//formats the time
	//printf("%s\n",asctime(localtime(&time1)));//debug
	//printf("%s\n",formattedTime);//debug
	FILE *fp;
	fp = fopen(logFile, "a");
	fprintf(fp, "%s %s\n", formattedTime, logMsg);
}


