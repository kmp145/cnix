#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
const char * test(char x[20]){
	//char x[20];
	fgets(x,20,stdin);
	//printf("%s\n",x);
	return x;
}*/

const char * inputStr(char userInput[], char msg[100], int length){
	printf("%s\n", msg);//used for debugging REMOVE FOR FINAL
	fgets(userInput,length,stdin);
	return userInput;
}

int inputInt(char msg[]){
	printf("%s\n",msg);
	int userInput;
	scanf("%i",&userInput);
	return userInput;
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
