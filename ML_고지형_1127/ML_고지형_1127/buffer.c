#define _CRT_SECURE_NO_WARNINGS 
#include "main.h"
#include <time.h>

int enterInput(inputData* inputBuffer)
{
	while (1)	// input 갯수 지정
	{
		printf("how many inputs do you want to use? (%d ~ %d): ", 1, NUMBER_OF_INPUT);
		scanf_s("%d", &(inputBuffer->inputNum));

		if (inputBuffer->inputNum < 1 || inputBuffer->inputNum > NUMBER_OF_INPUT)
		{
			printf("You enter wrong number. \n");
			continue;
		}

		else
			break;
	}

	while (1)	// output 갯수 지정
	{
		printf("how many outputs do you want to use? (%d ~ %d): ", 1, NUMBER_OF_OUTPUT);
		scanf_s("%d", &(inputBuffer->outputNum));

		if (inputBuffer->outputNum < 1 || inputBuffer->outputNum > NUMBER_OF_OUTPUT)
		{
			printf("You enter wrong number. \n");
			continue;
		}

		else
			break;
	}

	while (1)	// layer 갯수 지정
	{
		printf("how many layers do you want to use? (%d ~ %d): ", MIN_LAYER, MAX_LAYER);
		scanf_s("%d", &(inputBuffer->layer));

		if (inputBuffer->layer < MIN_LAYER || inputBuffer->layer > MAX_LAYER)
		{
			printf("You enter wrong number. \n");
			continue;
		}

		else
			break;
	}

	while (1)
	{
		printf("Do you want to use 1 as bias? (Yes: 1 / No: 0): ");
		scanf_s("%d", &(inputBuffer->bias));

		if (inputBuffer->bias != 1 && inputBuffer->bias != 0)
		{
			printf("You enter wrong number. \n");
			continue;
		}

		else
			break;
	}

	while (1)	// 뉴런 갯수 지정
	{
		for (int i = 0; i < (inputBuffer->layer);)
		{
			printf("Enter the number of %d layer's nuerons(%d~%d): ", i + 1, MIN_NUERON, MAX_NUERON);
			scanf_s("%d", &(inputBuffer->nueron[i]));

			if (inputBuffer->nueron[i] < MIN_NUERON || inputBuffer->nueron[i] > MAX_NUERON)
				printf("You enter wrong number. \n");

			else
			{
				i++;
			}
		}

		break;	// escape for loop, break immediately.
	}
	inputBuffer->time++;
	return 0;
}

int initParam(inputData* inputBuffer)
{
	srand((unsigned int)time(NULL));
	//srand(10);

	int i = 0;
	int j = 0;
	int k = 0;
	int numOutput = 0;

	for (i=0; i< MAX_LAYER; i++)	// random weight generator
		for (j = 0; j < (MAX_NUERON + NUMBER_OF_OUTPUT); j++)
			for (k = 0; k < (inputBuffer->bias + NUMBER_OF_INPUT); k++)
				for(numOutput = 0; numOutput<NUMBER_OF_OUTPUT; numOutput++)
					inputBuffer->weight[numOutput][i][j][k] = ((double)rand() / 32767.0) * 2 - 1;	// -1 ~ 1까지 값
	
	for (j = 0; j < NUMBER_OF_DATA; j++)	// random data generator
		{
		for (i = 0; i < NUMBER_OF_INPUT; i++)
			inputBuffer->x[i][j] = (((double)(rand() % 60) - 30.0) / 10.0);	// -3.0 ~ 3.0까지 값
		
			inputBuffer->target[j] = makeBoundary(inputBuffer, j, X1_INTERCEPT, X2_INTERCEPT, HORIZON_INTERCEPT) == 1? TARGET_HIGH : TARGET_LOW;	// intercept는 양수이면서 5보다 작은 값으로..
			inputBuffer->biasWeight[j] = ((double)rand() / 32767.0) * 2 - 1;	// -1 ~ 1까지 값
				// biasWeight, target are allocated twice. but we use later one. just for reducing code lines.
		}

	return 0;
}

int inspectParam(inputData* inputBuffer, inputData* inspectBuffer)
{
	int i = 0;
	int j = 0;

	memcpy(inspectBuffer, inputBuffer, sizeof(inputData));
	inspectBuffer->inputNum = NUMBER_OF_INPUT;
	inspectBuffer->outputNum = NUMBER_OF_OUTPUT;

	for (j = 0; j < NUMBER_OF_DATA; j++)
		for (i = inspectBuffer->inputNum; i < NUMBER_OF_INPUT; i++)
			inspectBuffer->x[i][j] = 0;

	return 0;
}

int copyWeight(inputData* inputBuffer, weight_t* weightBuffer)
{
	memcpy(weightBuffer->weight, inputBuffer->weight, sizeof(inputBuffer->weight));
	memcpy(weightBuffer->biasWeight, inputBuffer->biasWeight, sizeof(inputBuffer->biasWeight));

	return 0;
}

int pasteWeight(inputData* inspectBuffer, weight_t* weightBuffer)
{
	memcpy(inspectBuffer->weight, weightBuffer->weight, sizeof(weightBuffer->weight));
	memcpy(inspectBuffer->biasWeight, weightBuffer->biasWeight, sizeof(weightBuffer->biasWeight));

	return 0;
}

int formula(double x1, double x2)	// enter the formula
{
	//if (pow((pow(x1, 2) + pow(x2, 2) - 1), 3) - (pow(x1, 2) * pow(x2, 3)) < 0)
	if ( (pow((pow(x1, 2) + pow(x2, 2) - 1), 3) - (pow(x1, 2) * pow(x2, 3)) < 0))	// shape heart column
		return 1;	// target = 1

	else
		return 0;	// target = 0
}

int makeBoundary(inputData* inputBuffer, int order, int intercept1, int intercept2, int intercept3)	// for random target
{
	double x1 = inputBuffer->x[0][order];
	double x2 = inputBuffer->x[1][order];

	return formula(x1, x2);
}
/*
int inspectBoundary(double* inputBuffer, int intercept1, int intercept2, int intercept3)	// for inspection
{
	double x1 = inputBuffer[0];
	double x2 = inputBuffer[1];

	return formula(x1, x2);
}
*/
int gridBoundary(gridData* gridBuffer, int grid_x1, int grid_x2, int intercept1, int intercept2, int intercept3)	// for grid inspection
{
	double x1 = gridBuffer->x[0][grid_x1];
	double x2 = gridBuffer->x[1][grid_x2];

	return formula(x1, x2);
}