#include "main.h"
#include <time.h>

int enterInput(TrainingData* dataBuffer)
{
	printf("Enter number of nuerons(3~10): ");
	scanf_s("%d", &(dataBuffer->nueron));
	printf("Do you want to use 1 as bias? (Yes: 1 / No: 0): ");
	//bias must be 1 or 0... check again..
	scanf_s("%d", &(dataBuffer->bias));
	printf("Enter the input data x1, x2, target: ");
	scanf_s("%lf %lf %lf", &(dataBuffer->x1), &(dataBuffer->x2), &(dataBuffer->target));
		
	return 0;
}

int initWeight(TrainingData* dataBuffer)
{
	srand(time(NULL));
	
	dataBuffer->weight[0] = (rand() % 50) / 10.0;

}