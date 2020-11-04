#include "main.h"

int main(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	double x_inspect[2] = { 0, };
	double error_inspect = 0;
	int answer = 0;

	memset(&inputBuffer, 0, sizeof(inputData));

	enterInput(&inputBuffer);
	initParam(&inputBuffer);

	for (k = 0; k < NUMBER_OF_OUTPUT; k++)
	{
		for (i = 0; i < MAX_EPOCH; i++)
		{
			for (j = 0; j < NUMBER_OF_DATA; j++)
			{

				EBPCalc(&inputBuffer, j);
				inputBuffer.errorSum[k][i] = inputBuffer.errorSum[k][i] + (inputBuffer.error[k][j]);
				printf("%d 에러 %lf\n", k, inputBuffer.errorSum[k][i]);
			}
		}

		printf("%d 에러 %lf\n", k, inputBuffer.errorSum[k][i]);

		if (inputBuffer.errorSum[k][i] < ALLOW_TOTAL_ERROR)	// 에러가 상당히 작아지면 padding 후 break
		{
			double paddingValue = inputBuffer.errorSum[k][i];

			for (i; i < MAX_EPOCH; i++)
				inputBuffer.errorSum[k][i] = paddingValue;

			printf("%lf\n", inputBuffer.errorSum[k][i]);

			break;
		}
	}

	//writeData(&inputBuffer);
	//writeError(&inputBuffer);

	////////////// weight 검증시간!, 기존에 만든 특정한 삼각형 내부에 있는 아무 숫자나 넣어서 에러 검출 //////////////
	printf("Enter the any input X1, X2 ( -5 < X < 5 )\n");
	printf("If they are in the triangle that you generated, the EBP function will inspect it.\n");
	
	inspectResult(x_inspect);
}
