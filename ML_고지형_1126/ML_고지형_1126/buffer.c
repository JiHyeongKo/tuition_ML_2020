#define _CRT_SECURE_NO_WARNINGS 
#include "main.h"
#include <time.h>

int enterInput(inputData* inputBuffer)
{
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

	return 0;
}

int initParam(inputData* inputBuffer)
{
	srand((unsigned int)time(NULL));

	int i = 0;
	int j = 0;
	int k = 0;
	int numOutput = 0;

	for (i=0; i<(inputBuffer->layer); i++)	// random weight generator
		for (j = 0; j < (inputBuffer->nueron[i] + NUMBER_OF_OUTPUT); j++)
			for (k = 0; k < (inputBuffer->bias + NUMBER_OF_INPUT); k++)
				for(numOutput = 0; numOutput<NUMBER_OF_OUTPUT; numOutput++)
					inputBuffer->weight[numOutput][i][j][k] = ((double)rand() / 32767.0) * 2 - 1;	// -1 ~ 1까지 값
	
	for (j = 0; j < NUMBER_OF_DATA; j++)	// random data generator
		{
		for (i = 0; i < NUMBER_OF_INPUT; i++)
			inputBuffer->x[i][j] = (((double)(rand() % 20) - 10.0) / 5.0);	// -2.0 ~ 2.0까지 값

			inputBuffer->target[j] = makeTriangle(inputBuffer, j, X1_INTERCEPT, X2_INTERCEPT, HORIZON_INTERCEPT);	// intercept는 양수이면서 5보다 작은 값으로..
			inputBuffer->biasWeight[j] = ((double)rand() / 32767.0) * 2 - 1;	// -1 ~ 1까지 값
				// biasWeight, target are allocated twice. but we use later one. just for reducing code lines.
		}

	return 0;
}

int makeTriangle(inputData* inputBuffer, int order, int intercept1, int intercept2, int intercept3)	// for random data
{
	if (((inputBuffer->x[1][order] - inputBuffer->x[0][order] - intercept1) < 0) &&
		((inputBuffer->x[1][order] + inputBuffer->x[0][order] - intercept2) < 0) &&
		((inputBuffer->x[1][order] - intercept3) > 0))	// 특정한 삼각형 안에 있으면...
		return 1;	// target = 1

	else	// 특정한 삼각형 밖에 있으면...
		return 0;	// target = 0
}/////////////////////// 얘가 3D여서 그렇구나...!

int inspectTriangle(double* inputBuffer, int intercept1, int intercept2, int intercept3)	// for inspection
{
	if (((inputBuffer[1] - inputBuffer[0] - intercept1) < 0) &&
		((inputBuffer[1] + inputBuffer[0] - intercept2) < 0) &&
		((inputBuffer[1] - intercept3) > 0))	// 특정한 삼각형 안에 있으면...
		return 1;	// target = 1

	else	// 특정한 삼각형 밖에 있으면...
		return 0;	// target = 0
}

int gridTriangle(gridData* gridBuffer, int grid_x0, int grid_x1, int intercept1, int intercept2, int intercept3)	// for grid inspection
{
	if (((gridBuffer->x[1][grid_x1] - gridBuffer->x[0][grid_x0] - intercept1) < 0) &&
		((gridBuffer->x[1][grid_x1] + gridBuffer->x[0][grid_x0] - intercept2) < 0) &&
		((gridBuffer->x[1][grid_x1] - intercept3) > 0))	// 특정한 삼각형 안에 있으면...
		return 1;	// target = 1

	else	// 특정한 삼각형 밖에 있으면...
		return 0;	// target = 0
}