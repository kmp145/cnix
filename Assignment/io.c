#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"



const char * inputStr(char * userInput,char msg[100], int length, int flag){
	/*
	#################################################################################
	#				FLAGS						#
	#	0 = Print msg with '\n', remove trailing '\n' from input		#
	#	1 = Print msg without '\n', remove trailing '\n' from input		#
	#	2 = Print msg with '\n', don't remove trailing '\n' from input		#
	#	3 = Print msg without '\n', don't remove trailing '\n' from input	#
	#################################################################################*/
	
	if (flag == 0 || flag == 3)
		fprintf(stdout, "%s\n", msg);
	else
		fprintf(stdout, "%s", msg);
	fgets(userInput,length,stdin);

	if (flag == 0 || flag == 1)
		userInput[strcspn(userInput, "\n")] = 0;//Removes trailing \n
	
	return userInput;
} 

int inputInt(int *userInput,char msg[], int length, int flag){//NEEDS FIXING

	/*
	#########################################################################
	#			FLAGS						#
	#		0 = Return input -1					#
	#		1 = Return input					#
	#########################################################################*/

	//char *x = malloc(sizeof(int));
	char x[255];
	int y;
	fprintf(stdout, "%s\n",msg);
	fgets(x, length, stdin);
	//userInput = atoi(x);
	y = atoi(x);
	if (flag == 0){
		y-=1;
	}
	return (y);

}

int displayMenu(char *menuOptions[], int optionNum, int flag){

	/*
	#########################################################################
	#			FLAGS						#
	#		0 = Print menu with numbers				#
	#		1 = Print menu without numbers				#
	#########################################################################*/
	
	int i = 0, x;
	for (i = 0; i < optionNum; i++){
		if(flag == 0){
			x = i +1;
			fprintf(stdout, "%d.\t", x);
		}
		fprintf(stdout, "%s\n", menuOptions[i]);

	}
	return 0;
}


/*
int main(){
	
	char *str;
	int *myInt;
	char *a[2];
	a[0] = "blah";
	a[1]= "hmm";
	diplayMenu(a, 2, 0);
	myInt = malloc(sizeof(int));
	str = malloc(120 * sizeof(char));
	inputStr(str, "msg", 120, 0);
	fprintf(stdout, "Inputted msg:\t%s\n",str);
	myInt = inputInt(myInt, "msg", 12, 0);// FIX
	fprintf(stdout, "Inputted int:\t%d\n",myInt);
	//strcpy(str,inputStr("Msg", 152));
	return 0;

}*/
