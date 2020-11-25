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

	for (numOutput = 0; numOutput < NUMBER_OF_OUTPUT; numOutput++)
	{
		for (i = 0; i < (inputBuffer->layer); i++)
		{
			for (j = 0; j < (inputBuffer->nueron[i]); j++)
			{
				for (k = 0; k < NUMBER_OF_INPUT; k++)
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

/*
int inspectResult(double* x_inspect)
{
	printf("Enter the any input X1, X2 ( -5 < X < 5 )\n");
	printf("If they are in the boundary that you generated, the EBP function will inspect it.\n");

	double totalOutputError = 0;

	while (1)
	{
		printf("X1 X2: ");
		scanf_s("%lf", &x_inspect[0]);
		scanf_s(" %lf", &x_inspect[1]);

		if (inspectBoundary(x_inspect, X1_INTERCEPT, X2_INTERCEPT, HORIZON_INTERCEPT))
		{
			printf("You enter %lf, %lf there are inside.\n", x_inspect[0], x_inspect[1]);
			break;
		}

		else
		{
			printf("You enter %lf %lf there are outside.\n", x_inspect[0], x_inspect[1]);
			break;
		}
	}

	inputBuffer.x[0][0] = x_inspect[0];
	inputBuffer.x[1][0] = x_inspect[1];
	EBPCalc(&inputBuffer, 0);

	
	for (int numOutput = 0; numOutput < inputBuffer.outputNum; numOutput++)	// 각각의 에러의 합의 threshold인지 전체 에러 합의 threshold인지 체크 필요
	{
		printf("%d Error insepection: %lf\n", numOutput+1, inputBuffer.error[numOutput][0]);
		inputBuffer.error[numOutput][0] = (inputBuffer.error[numOutput][0] > THRESHOLD);
		totalOutputError = totalOutputError + inputBuffer.error[numOutput][0];
	}

	if (totalOutputError > 0)	// error가 많이 있으면
	{
		printf("There is fatal error\n");
		return -1;
	}

	else	// error가 거의 없으면
	{
		printf("Well Done!\n");
		return 0;
	}
}
*/