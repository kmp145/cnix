#include <stdio.h>
#include <stdlib.h>
#include "dice.h"
#define STR 0
#define DEX 1
#define CON 2
#define INT 3
#define WIS 4
#define CHA 5

struct Character_t{
	char name[20];
	char sex;
	char race[12];
	char class[12];
	int stats[6];//change to one int
	int level;

};

void saveChar(struct Character_t char1){
	FILE *fp;
	fp = fopen("test.txt", "w");
	fwrite(&char1, sizeof(char1), 1,fp);
	fclose(fp);
}

struct Character_t loadChar(char filename[20]){
	struct Character_t char1;
	FILE *fp;
	fp = fopen(filename,"r");
	fread(&char1, sizeof(char1), 1, fp);
	fclose(fp);
	return char1;
}

struct Character_t createChar(){
	int i;
	printf("Creating new char\n");
	struct Character_t char1;
	printf("Enter your name:\t");
	scanf("%s",char1.name);
	printf("Are you (m)ale or (f)emale?\n");
	scanf(" %c", &char1.sex);
	printf("What race are you?\n");
	scanf("%s",char1.race);
	printf("What class are you?\n");
	scanf("%s", char1.class);

	for (i=0;i<6;i++){
		char1.stats[i] = Roll_Stat(4,3);
		printf("%i\n",char1.stats[i]);
	}

	saveChar(char1);
	return char1;
}

void printChar(struct Character_t char1){
	printf("In print char\n");
	printf("Name:\t%s \nSex:\t%c \nRace:\t%s \nClass:\t%s\n",char1.name, char1.sex, char1.race, char1.class);
}


int main(){
	
	int choice;
	struct Character_t char1;
	
	while(1){
		printf("What would you like to do?\n 1)Create a new character.\n 2)Load an existing character.\n");
		scanf("%d",&choice);
		if(choice == 1){
			char1 = createChar();
			break;
		}
		else if(choice == 2){
			char1 = loadChar("test.txt");
			break;
		}	
		else{
			printf("Invalid choice!\n");
		}	
	}
	printChar(char1);
}
