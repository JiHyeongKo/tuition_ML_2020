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

	for (i = 0; i < NUMBER_OF_INPUT; i++)
	{
		for (j = 0; j < NUMBER_OF_DATA; j++)
		{
			inputBuffer->x[i][j] = ((double)rand() / 32767.0) * 10 - 5;	// -5 ~ 5���� ��
			inputBuffer->target[j] = ((((double)rand() / 32767.0) * 2 - 1) > 0);	// -1 ~ 1���� ���� �߰����� 0���� ũ�� 1, �ƴϸ� 0
			inputBuffer->biasWeight[i] = ((double)rand() / 32767.0) * 2 - 1;	// -1 ~ 1���� ��
			// biasWeight�� target�� �� �� �Ҵ�ȴ�. �׷��� ���� ���� ���. �ڵ� ���� ���̱� ����.
		}
	}
		
	return 0;
}