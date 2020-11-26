#include "main.h"

double sigmoid(double sum)
{
	return  1 / (1 + pow(M_E, (-1 * sum)));
}

double sum[NUMBER_OF_OUTPUT] = { 0, };
double sumBuffer[NUMBER_OF_OUTPUT][MAX_LAYER][MAX_NUERON] = { 0, };
double delta[NUMBER_OF_OUTPUT][MAX_LAYER][MAX_NUERON + NUMBER_OF_OUTPUT] = { 0, };
double deltaWeight[NUMBER_OF_OUTPUT][MAX_LAYER][MAX_NUERON + NUMBER_OF_OUTPUT][MAX_NUERON + NUMBER_OF_OUTPUT] = { 0, };

int EBPCalc(inputData* inputBuffer, int order)
{
	int numOutput = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int numLayer_1 = inputBuffer->layer - 1;	// number of layer - 1 : for array.
	int try = MAX_EPOCH;

	double biasDeltaWeight = 0;
	// 입력의 갯수 제외한, (히든 레이어의 뉴런 갯수 + 출력단) 만큼 필요

	memset(&sum, 0, sizeof(sum));
	memset(&sumBuffer, 0, sizeof(sumBuffer));
	memset(&delta, 0, sizeof(delta));
	memset(&deltaWeight, 0, sizeof(deltaWeight));

	for (numOutput = 0; numOutput < inputBuffer->outputNum; numOutput++)
	{
		for (i = 0; i < (inputBuffer->layer); i++)
		{
			for (j = 0; j < (inputBuffer->nueron[i]); j++)
			{
				for (k = 0; k < inputBuffer->inputNum; k++)
				{
					sumBuffer[numOutput][i][j] = sumBuffer[numOutput][i][j] + 
						(inputBuffer->x[k][order] * inputBuffer->weight[numOutput][i][j][k]);	// weight*input
				}

				sumBuffer[numOutput][i][j] = sumBuffer[numOutput][i][j] + (inputBuffer->bias * inputBuffer->biasWeight[order]);	// weight*input + bias
				inputBuffer->output[numOutput][i][j] = sigmoid(sumBuffer[numOutput][i][j]);	// hidden layer output
			}

			for (j = 0; j < (inputBuffer->nueron[i]); j++)
				sum[numOutput] = sum[numOutput] + (inputBuffer->output[numOutput][i][j] * inputBuffer->weight[numOutput][i][inputBuffer->nueron[i] + numOutput][j]);	// 전체 weight*input
			sum[numOutput] = sum[numOutput] + (inputBuffer->bias * inputBuffer->biasWeight[order]);	// 전체 weight*input + bias
		}

		inputBuffer->output[numOutput][numLayer_1][inputBuffer->nueron[numLayer_1] + numOutput] = sigmoid(sum[numOutput]);	// last output(output layer output)
		inputBuffer->y[numOutput][order] = (inputBuffer->output[numOutput][numLayer_1][inputBuffer->nueron[numLayer_1] + numOutput]);	// y = last output
		inputBuffer->error[numOutput][order] = fabs(inputBuffer->y[numOutput][order] - inputBuffer->target[order]);	// error = | last output - taget |

		//printf("%f %f %f\n", inputBuffer->output[numOutput][numLayer_1][inputBuffer->nueron[numLayer_1] + numOutput], inputBuffer->y[numOutput][order], inputBuffer->error[numOutput][order]);
	}

	////////////////// Error Back Propagation //////////////////
	for (numOutput = 0; numOutput < NUMBER_OF_OUTPUT; numOutput++)
	{
		delta[numOutput][numLayer_1][inputBuffer->nueron[numLayer_1] + numOutput] = 
			(inputBuffer->target[order] - inputBuffer->output[numOutput][numLayer_1][inputBuffer->nueron[numLayer_1] + numOutput]) *
			(inputBuffer->output[numOutput][numLayer_1][inputBuffer->nueron[numLayer_1] + numOutput]) *
			(1 - (inputBuffer->output[numOutput][numLayer_1][inputBuffer->nueron[numLayer_1] + numOutput]));

		//	last output delta

		for (i = 0; i < (inputBuffer->layer); i++)
		{
			for (j = 0; j < (inputBuffer->nueron[i] + numOutput); j++)
			{
				delta[numOutput][i][j] = (inputBuffer->output[numOutput][i][j]) *
					(1 - (inputBuffer->output[numOutput][i][j])) *
					inputBuffer->weight[numOutput][i][inputBuffer->nueron[i] + numOutput][j] *
					delta[numOutput][i][inputBuffer->nueron[i] + numOutput];
				// hidden layer delta
			}

			for (j = 0; j < (inputBuffer->nueron[i] + numOutput); j++)
				for (k = 0; k < (inputBuffer->bias + numOutput); k++)
				{
					deltaWeight[numOutput][i][j][k] = LEARNING_GAIN * delta[numOutput][i][j] * inputBuffer->output[numOutput][i][j];
					// hidden layer delta weight

					inputBuffer->weight[numOutput][i][j][k] = inputBuffer->weight[numOutput][i][j][k] + deltaWeight[numOutput][i][j][k];
					//	hidden layer weight
				}

			biasDeltaWeight = LEARNING_GAIN * delta[numOutput][i][inputBuffer->nueron[i] + numOutput] * (inputBuffer->bias);
			// bias delta weight
			inputBuffer->biasWeight[order] = inputBuffer->biasWeight[order] + biasDeltaWeight;
			//bias delta
		}
	}
	return 0;
}

int EBPInspect(inputData* inputBuffer, int order)
{
	int numOutput = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int numLayer_1 = inputBuffer->layer - 1;	// number of layer - 1 : for array.
	int try = MAX_EPOCH;

	double biasDeltaWeight = 0;
	// 입력의 갯수 제외한, (히든 레이어의 뉴런 갯수 + 출력단) 만큼 필요

	memset(&sum, 0, sizeof(sum));
	memset(&sumBuffer, 0, sizeof(sumBuffer));
	memset(&delta, 0, sizeof(delta));
	memset(&deltaWeight, 0, sizeof(deltaWeight));

	for (numOutput = 0; numOutput < NUMBER_OF_OUTPUT; numOutput++)
	{
		for (i = 0; i < (inputBuffer->layer); i++)
		{
			for (j = 0; j < (inputBuffer->nueron[i]); j++)
			{
				for (k = 0; k < inputBuffer->inputNum; k++)
				{
					sumBuffer[numOutput][i][j] = sumBuffer[numOutput][i][j] +
						(inputBuffer->x[k][order] * inputBuffer->weight[numOutput][i][j][k]);	// weight*input
				}

				sumBuffer[numOutput][i][j] = sumBuffer[numOutput][i][j] + (inputBuffer->bias * inputBuffer->biasWeight[order]);	// weight*input + bias
				inputBuffer->output[numOutput][i][j] = sigmoid(sumBuffer[numOutput][i][j]);	// hidden layer output
			}

			for (j = 0; j < (inputBuffer->nueron[i]); j++)
				sum[numOutput] = sum[numOutput] + (inputBuffer->output[numOutput][i][j] * inputBuffer->weight[numOutput][i][inputBuffer->nueron[i] + numOutput][j]);	// 전체 weight*input
			sum[numOutput] = sum[numOutput] + (inputBuffer->bias * inputBuffer->biasWeight[order]);	// 전체 weight*input + bias
		}

		inputBuffer->output[numOutput][numLayer_1][inputBuffer->nueron[numLayer_1] + numOutput] = sigmoid(sum[numOutput]);	// last output(output layer output)
		inputBuffer->y[numOutput][order] = (inputBuffer->output[numOutput][numLayer_1][inputBuffer->nueron[numLayer_1] + numOutput]);	// y = last output
		inputBuffer->error[numOutput][order] = fabs(inputBuffer->y[numOutput][order]);
	}
	return 0;
}