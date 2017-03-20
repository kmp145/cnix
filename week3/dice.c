#include <stdio.h>
#define NUM_OUT_OF_RANGE -1
#define FALSE 0
#define TRUE !FALSE

void Dice_Sort(int *dice_array, int number_of_dice){
	int sorted = FALSE, temp;
	while(!sorted){
		sorted = TRUE;
		for (int i = 0; i < number_of_dice-1; i++){
			if (dice_array[i] < dice_array[i+1]){
				sorted = FALSE;
				temp = dice_array[i];
				dice_array[i] = dice_array[i+1];
				dice_array[i+1] = temp;
			}
		}
	}
}


int Roll_Dice(int number_of_dice, int number_of_faces){
	int sum = 0;
	for (int i = 0; i < number_of_dice; i++){
		sum += rand()%number_of_faces+1;
	}
	return sum;
}

int Roll_Stat(int number_of_dice, int use_highest){
	int sum = 0, dice_array[number_of_dice];
	if (use_highest > number_of_dice)
		return NUM_OUT_OF_RANGE;
	for (int i = 0; i<number_of_dice; i++){
		dice_array[i] = Roll_Dice(1,6);
	}
	Dice_Sort(dice_array, number_of_dice);

	/*for (int i = 0; i<number_of_dice; i++){
		printf("%i sorted\n",dice_array[i]);
	}*/

	for (int i = 0; i<use_highest; i++){
		sum += dice_array[i];	
	}
	
	return sum;
}




