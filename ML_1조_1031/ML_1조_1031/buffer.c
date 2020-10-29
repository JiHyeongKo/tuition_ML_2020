#define _CRT_SECURE_NO_WARNINGS 
#include "main.h"
#include <time.h>

int enterInput(inputData* inputBuffer)
{
	while (1)
	{
		printf("Enter number of nuerons(3~10): ");
		scanf_s("%d", &(inputBuffer->nueron));

		if (inputBuffer->nueron < 3 || inputBuffer->nueron > 10)
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

	inputBuffer->weightNumber = (inputBuffer->nueron + inputBuffer->bias) * inputBuffer->nueron;
	// hidden layer�� ���� weight�� bias�� ������ 4*n��, ������ 3*n��

	return 0;
}

int initParam(inputData* inputBuffer)
{
	srand((unsigned int)time(NULL));

	int i = 0;
	int j = 0;

	for (i = 0; i < (inputBuffer->nueron + NUMBER_OF_OUTPUT); i++)
		for (j = 0; j < (inputBuffer->bias + NUMBER_OF_INPUT); j++)
			{
				inputBuffer->weight[i][j] = ((double)rand() / 32767.0) * 2 - 1;	// -1 ~ 1���� ��
				//printf("weight[%d][%d] = %lf\n", i, j, inputBuffer->weight[i][j]);
			}

	
	for (j = 0; j < NUMBER_OF_DATA; j++)
		{
			for (i = 0; i < NUMBER_OF_INPUT; i++)
				inputBuffer->x[i][j] = ((double)rand() / 32767.0) * 10 - 5;	// -5 ~ 5���� ��

			inputBuffer->target[j] = makeTriangle(inputBuffer, j, POSITIVE_INTERCEPT, POSITIVE_INTERCEPT, POSITIVE_INTERCEPT);	// intercept�� ����̸鼭 5���� ���� ������..
			inputBuffer->biasWeight[j] = ((double)rand() / 32767.0) * 2 - 1;	// -1 ~ 1���� ��
				// biasWeight, target are allocated twice. but we use later one. just for reducing code lines.
		}

	return 0;
}

int makeTriangle(inputData* inputBuffer, int order, signed int intercept1, signed int intercept2, signed int intercept3)
{
	if (((inputBuffer->x[0][order] + (inputBuffer->x[1][order] - intercept1)) < 0) &&
		((inputBuffer->x[0][order] - (inputBuffer->x[1][order] - intercept2)) > 0) &&
		((inputBuffer->x[1][order] + intercept3) > 0))	// Ư���� �ﰢ�� �ȿ� ������...
		return 1;	// target = 1

	else	// Ư���� �ﰢ�� �ۿ� ������...
		return 0;	// target = 0
}

int inspectTriangle(double* inputBuffer, signed int intercept1, signed int intercept2, signed int intercept3)
{
	if (((inputBuffer[0] + (inputBuffer[1] - intercept1)) < 0) &&
		((inputBuffer[0] - (inputBuffer[1] - intercept1)) > 0) &&
		((inputBuffer[1] + intercept1) > 0))	// Ư���� �ﰢ�� �ȿ� ������...
		return 1;	// target = 1

	else	// Ư���� �ﰢ�� �ۿ� ������...
		return 0;	// target = 0
}