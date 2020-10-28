#include "main.h"

int EBPCalc(inputData* inputBuffer, int order)
{
	int i = 0;
	int j = 0;
	int try = MAX_EPOCH;
	double y = 0;
	double sum = 0;
	double sumBuffer[MAX_NUERON] = { 0, };
	double delta[MAX_NUERON + NUMBER_OF_OUTPUT] = { 0, };
	double deltaWeight[MAX_NUERON + NUMBER_OF_OUTPUT][MAX_NUERON + NUMBER_OF_OUTPUT] = { 0, };
	// 입력의 갯수 제외한, (히든 레이어의 뉴런 갯수 + 출력단) 만큼 필요

	int numberNueron = inputBuffer->nueron;

	for (i = 0; i < (inputBuffer->nueron); i++)
	{
		for (j = 0; j < NUMBER_OF_INPUT; j++)
		{
			sumBuffer[i] = sumBuffer[i] + (inputBuffer->x[j][order] * inputBuffer->weight[i][j]);
		}
		
		sumBuffer[i] = sumBuffer[i] + (inputBuffer->bias * inputBuffer->biasWeight[order]);
		inputBuffer->output[i] = 1 / (1 + pow(M_E, (-1 * sumBuffer[i])));
	}

	for (i = 0; i < (inputBuffer->nueron); i++)
		sum = sum + (inputBuffer->output[i] * inputBuffer->weight[((inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1)][i]);
	sum = sum + (inputBuffer->bias * inputBuffer->biasWeight[order]);
	//printf("sum: %lf\n", sum);

	inputBuffer->output[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1] = 1 / (1 + pow(M_E, (-1 * sum)));
	y = (inputBuffer->output[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1]);// > THRESHOLD);	/////////////////////////////////////////////////////////////
	inputBuffer->error[order] = ABS(y - inputBuffer->target[order]);	///////////////////////////////////////////////
	//printf("inputBuffer->error[order]: %lf\n", inputBuffer->error[order]);
	////// Error Back Propagation //////
		
	delta[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1] = (inputBuffer->target[order] - inputBuffer->output[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1]) * (inputBuffer->output[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1]) * (1 - (inputBuffer->output[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1]));
	//	마지막 아웃풋 delta
	for (i = 0; i < (inputBuffer->nueron + NUMBER_OF_OUTPUT - 1); i++)
	{
		delta[i] = (inputBuffer->output[i]) * 
		(1 - (inputBuffer->output[i])) * 
		inputBuffer->weight[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1][i] * 
		delta[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1];
		// hidden layer delta
	}

	for (i = 0; i < (inputBuffer->nueron + NUMBER_OF_OUTPUT); i++)
		for (j = 0; j < (inputBuffer->bias + NUMBER_OF_INPUT); j++)
		{
			deltaWeight[i][j] = LEARNING_GAIN * delta[i] * inputBuffer->output[j];
			// deltaWeight
			inputBuffer->weight[i][j] = inputBuffer->weight[i][j] + deltaWeight[i][j];
			//printf("new weight[%d][%d] %lf\n",i,j, inputBuffer->weight[i][j]);
		}

	return 0;
}
