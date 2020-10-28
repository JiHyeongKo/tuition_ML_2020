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
	// hidden layer로 가는 weight는 bias가 있으면 4*n개, 없으면 3*n개

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
				inputBuffer->weight[i][j] = ((double)rand() / 32767.0) * 2 - 1;	// -1 ~ 1까지 값
				//printf("weight[%d][%d] = %lf\n", i, j, inputBuffer->weight[i][j]);
			}

	for (i = 0; i < NUMBER_OF_INPUT; i++)
	{
		for (j = 0; j < NUMBER_OF_DATA; j++)
		{
			inputBuffer->x[i][j] = ((double)rand() / 32767.0) * 10 - 5;	// -5 ~ 5까지 값
			inputBuffer->target[j] = ((((double)rand() / 32767.0) * 2 - 1) > 0);	// -1 ~ 1까지 값의 중간값인 0보다 크면 1, 아니면 0
			inputBuffer->biasWeight[i] = ((double)rand() / 32767.0) * 2 - 1;	// -1 ~ 1까지 값
			// biasWeight과 target은 두 번 할당된다. 그러나 나중 것을 사용. 코드 길이 줄이기 위해.
		}
	}
		
	return 0;
}