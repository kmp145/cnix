#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"
/*
const char * test(char x[20]){
	//char x[20];
	fgets(x,20,stdin);
	//printf("%s\n",x);
	return x;
}*/
/*
const char * inputStr(char userInput[], char msg[100], int length){
	//printf("%s\n", msg);//used for debugging REMOVE FOR FINAL
	fgets(userInput,length,stdin);
	return userInput;
}*/ //This function is causing errors which will not let me include functions in this code

int inputInt(char msg[]){
	printf("%s\n",msg);
	int userInput;
	fgets(userInput,5,stdin);
	return userInput;
}

int diplayMenu(){
	fprintf(stdout,"Welcome to phase 1 of my assignment!\nAdam Lock student nuumber:\t 10424430\n\n");
	int userChoice;
	while (1){
		//fprintf("What would you like to do?\n1)Display current user settings.\n2)Change a user setting.\n3)Display contents of the sharing list\n4)Change a file's permission.\n99)Exit.");
		userChoice = inputInt("What would you like to do?\n1)Display current user settings.\n2)Change a user setting.\n3)Display contents of the sharing list\n4)Change a file's permission.\n99)Exit.\n");
		printf("%i\n",userChoice);
		
	}
	return 0;
}
/*
int main(){
	char inputsStr[20];
	char y[20];
	//printf("Input something:\t");
	//fgets (inputStr, 20, stdin);
	//strcpy(inputsStr, inputStr("input\t",10));
	//strcpy(inputsStr, test());	
	//inputStr = test();	
	test(y);
	inputStr(y, "msg",20);
	printf("%s\n",y);
	return 0;
}


int main(){
	int i = inputInt("msg");
	printf("%i",i);
	return 0;
}*/
