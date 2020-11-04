#include "main.h"

int EBPCalc(inputData* inputBuffer, int order)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int numLayer_1 = inputBuffer->layer - 1;	// number of layer - 1 : for array.
	int try = MAX_EPOCH;
	double sum[NUMBER_OF_OUTPUT] = { 0, };
	double sumBuffer[MAX_LAYER][MAX_NUERON] = { 0, };
	double delta[MAX_LAYER][MAX_NUERON + NUMBER_OF_OUTPUT] = { 0, };
	double deltaWeight[MAX_LAYER][MAX_NUERON + NUMBER_OF_OUTPUT][MAX_NUERON + NUMBER_OF_OUTPUT] = { 0, };
	double biasDeltaWeight = 0;
	// 입력의 갯수 제외한, (히든 레이어의 뉴런 갯수 + 출력단) 만큼 필요

	for (i = 0; i < (inputBuffer->layer); i++)
	{
		for (j = 0; j < (inputBuffer->nueron[i]); j++)
		{
			for (k = 0; k < NUMBER_OF_INPUT; k++)
			{
				sumBuffer[i][j] = sumBuffer[i][j] + (inputBuffer->x[j][order] * inputBuffer->weight[i][j][k]);	// weight*input
			}

			sumBuffer[i][j] = sumBuffer[i][j] + (inputBuffer->bias * inputBuffer->biasWeight[order]);	// weight*input + bias
			inputBuffer->output[i][j] = 1 / (1 + pow(M_E, (-1 * sumBuffer[i][j])));	// hidden layer output
		}

		for (k = 0; k < NUMBER_OF_OUTPUT; k++)
		{
			for (j = 0; j < (inputBuffer->nueron[i]); j++)
				sum[k] = sum[k] + (inputBuffer->output[i][j] * inputBuffer->weight[i][(inputBuffer->nueron[i] + k)][j]);	// 전체 weight*input
			sum[k] = sum[k] + (inputBuffer->bias * inputBuffer->biasWeight[order]);	// 전체 weight*input + bias

		}
	}

	for (i = 0; i < NUMBER_OF_OUTPUT; i++)
	{
		inputBuffer->output[numLayer_1][inputBuffer->nueron[numLayer_1] + i] = 1 / (1 + pow(M_E, (-1 * sum[i])));	// last output(output layer output)
		inputBuffer->y[i][order] = (inputBuffer->output[numLayer_1][inputBuffer->nueron[numLayer_1] + i]);	//y = last output
		inputBuffer->error[i][order] = fabs(inputBuffer->y[i][order] - inputBuffer->target[order]);	// error = | last output - taget |
	
		////////////////// Error Back Propagation //////////////////
		delta[numLayer_1][inputBuffer->nueron[numLayer_1] + i] = (inputBuffer->target[order] - inputBuffer->output[numLayer_1][inputBuffer->nueron[numLayer_1] + i]) *
			(inputBuffer->output[numLayer_1][inputBuffer->nueron[numLayer_1] + i]) *
			(1 - (inputBuffer->output[numLayer_1][inputBuffer->nueron[numLayer_1] + i]));
	}
	//	last output delta

	for (i = 0; i < (inputBuffer->layer); i++)
	{
		for (j = 0; j < (inputBuffer->nueron[i] + NUMBER_OF_OUTPUT - 1); j++)
		{
			delta[i][j] = (inputBuffer->output[i][j]) *
				(1 - (inputBuffer->output[i][j])) *
				inputBuffer->weight[i][(inputBuffer->nueron[i] + NUMBER_OF_OUTPUT) - 1][j] *
				delta[i][(inputBuffer->nueron[i] + NUMBER_OF_OUTPUT) - 1];
			// hidden layer delta
		}

		for (j = 0; j < (inputBuffer->nueron[i] + NUMBER_OF_OUTPUT); j++)
			for (k = 0; k < (inputBuffer->bias + NUMBER_OF_INPUT); k++)
			{
				deltaWeight[i][j][k] = LEARNING_GAIN * delta[i][j] * inputBuffer->output[i][j];
				// hidden layer delta weight

				inputBuffer->weight[i][j][k] = inputBuffer->weight[i][j][k] + deltaWeight[i][j][k];
				//	hidden layer weight
			}


		biasDeltaWeight = LEARNING_GAIN * delta[i][(inputBuffer->nueron[i] + NUMBER_OF_OUTPUT) - 1] * (inputBuffer->bias);
		// bias delta weight
		inputBuffer->biasWeight[order] = inputBuffer->biasWeight[order] + biasDeltaWeight;
		//bias delta
	}
	
	return 0;
}

int inspectResult(double* x_inspect)
{
	int errorSum = 0;
	int i = 0;
	while (1)
	{
		printf("X1 X2: ");
		scanf_s("%lf", &x_inspect[0]);
		scanf_s(" %lf", &x_inspect[1]);
		
		if (inspectTriangle(x_inspect, X1_INTERCEPT, X2_INTERCEPT, HORIZON_INTERCEPT))
		{
			printf("You enter %lf, %lf\n", x_inspect[0], x_inspect[1]);
			break;
		}

		else
		{
			printf("You need to enter other numbers.\n");
			continue;
		}
	}

	inputBuffer.x[0][0] = x_inspect[0];
	inputBuffer.x[1][0] = x_inspect[1];
	EBPCalc(&inputBuffer, 0);
	
	for(i= 0; i<NUMBER_OF_OUTPUT; i++)
		inputBuffer.error[i][0] = (inputBuffer.error[i][0] > THRESHOLD);

	for (i = 0; i < NUMBER_OF_OUTPUT; i++)
		errorSum = errorSum + inputBuffer.error[i][0];

		if (errorSum > 0)	// error가 많이 있으면
		{
			printf("There is fatal error\n");
			return -1;
		}

		else if (errorSum == 0)	// error가 거의 없으면
		{
			printf("Well Done!\n");
			return 0;
		}
}