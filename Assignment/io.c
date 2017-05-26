#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"


const char * inputStr(char * userInput,char msg[100], int length){
	//char userInput[length];
	printf("%s\n", msg);//used for debugging REMOVE FOR FINAL
	fgets(userInput,length,stdin);
	userInput[strcspn(userInput, "\n")] = 0;//Removes trailing \n
	return userInput;
} //This function is causing errors which will not let me include functions in this code

int *inputInt(int * userInput,char msg[], int length){
	printf("%s\n",msg);
	fgets(userInput,length,stdin);
	return userInput;
}
/*
int diplayMenu(){
	fprintf(stdout,"Welcome to phase 1 of my assignment!\nAdam Lock student nuumber:\t 10424430\n\n");
	int userChoice;
	while (1){
		//fprintf("What would you like to do?\n1)Display current user settings.\n2)Change a user setting.\n3)Display contents of the sharing list\n4)Change a file's permission.\n99)Exit.");
		userChoice = inputInt("What would you like to do?\n1)Display current user settings.\n2)Change a user setting.\n3)Display contents of the sharing list\n4)Change a file's permission.\n99)Exit.\n");
		printf("%i\n",userChoice);
		
	}
	return 0;
}*/

int main(){
	
	char *str;
	int *myInt;
	myInt = malloc(sizeof(int));
	str = malloc(120 * sizeof(char));
	inputStr(str, "msg", 120);
	fprintf(stdout, "Inputted msg:\t%s\n",str);
	inputInt(myInt, "msg", 12);
	//strcpy(str,inputStr("Msg", 152));
	return 0;

}
