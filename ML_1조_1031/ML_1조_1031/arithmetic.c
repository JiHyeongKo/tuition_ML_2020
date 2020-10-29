#include "main.h"

int EBPCalc(inputData* inputBuffer, int order)
{
	int i = 0;
	int j = 0;
	int try = MAX_EPOCH;
	double sum = 0;
	double sumBuffer[MAX_NUERON] = { 0, };
	double delta[MAX_NUERON + NUMBER_OF_OUTPUT] = { 0, };
	double deltaWeight[MAX_NUERON + NUMBER_OF_OUTPUT][MAX_NUERON + NUMBER_OF_OUTPUT] = { 0, };
	double biasDeltaWeight = 0;
	// �Է��� ���� ������, (���� ���̾��� ���� ���� + ��´�) ��ŭ �ʿ�

	for (i = 0; i < (inputBuffer->nueron); i++)
	{
		for (j = 0; j < NUMBER_OF_INPUT; j++)
		{
			sumBuffer[i] = sumBuffer[i] + (inputBuffer->x[j][order] * inputBuffer->weight[i][j]);	// weight*input
		}
		
		sumBuffer[i] = sumBuffer[i] + (inputBuffer->bias * inputBuffer->biasWeight[order]);	// weight*input + bias
		inputBuffer->output[i] = 1 / (1 + pow(M_E, (-1 * sumBuffer[i])));	// hidden layer output
	}

	for (i = 0; i < (inputBuffer->nueron); i++)
		sum = sum + (inputBuffer->output[i] * inputBuffer->weight[((inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1)][i]);	// ��ü weight*input
	sum = sum + (inputBuffer->bias * inputBuffer->biasWeight[order]);	// ��ü weight*input + bias
	
	inputBuffer->output[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1] = 1 / (1 + pow(M_E, (-1 * sum)));	// last output(output layer output)
	inputBuffer->y[order] = (inputBuffer->output[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1]);	//y = last output
	inputBuffer->error[order] = fabs(inputBuffer->y[order] - inputBuffer->target[order]);	// error = | last output - taget |
	
	////////////////// Error Back Propagation //////////////////	
	
	delta[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1] = (inputBuffer->target[order] - inputBuffer->output[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1]) * (inputBuffer->output[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1]) * (1 - (inputBuffer->output[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1]));
	//	last output delta
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
			// hidden layer delta weight
			inputBuffer->weight[i][j] = inputBuffer->weight[i][j] + deltaWeight[i][j];
			//	hidden layer weight
		}

	biasDeltaWeight = LEARNING_GAIN * delta[(inputBuffer->nueron + NUMBER_OF_OUTPUT) - 1] * (inputBuffer->bias);
	// bias delta weight
	inputBuffer->biasWeight[order] = inputBuffer->biasWeight[order] + biasDeltaWeight;
	//bias delta

	return 0;
}
