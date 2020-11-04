#include "main.h"

int main(void)
{
	int i = 0;
	int j = 0;
	double x_inspect[2] = { 0, };
	double error_inspect = 0;

	memset(&inputBuffer, 0, sizeof(inputData));

	enterInput(&inputBuffer);
	initParam(&inputBuffer);

	for (i = 0; i < MAX_EPOCH; i++)
	{
		for (j = 0; j < NUMBER_OF_DATA; j++)
		{
			EBPCalc(&inputBuffer, j);
			inputBuffer.errorSum[i] = inputBuffer.errorSum[i] + (inputBuffer.error[j]);
		}

		printf("%lf\n", inputBuffer.errorSum[i]);

		if (inputBuffer.errorSum[i] < ALLOW_TOTAL_ERROR)	// 에러가 상당히 작아지면 padding 후 break
		{
			double paddingValue = inputBuffer.errorSum[i];

			for (i; i < MAX_EPOCH; i++)
				inputBuffer.errorSum[i] = paddingValue;

			break;
		}
}

	//writeData(&inputBuffer);
	//writeError(&inputBuffer);

	////////////// weight 검증시간!, 기존에 만든 특정한 삼각형 내부에 있는 아무 숫자나 넣어서 에러 검출 //////////////
	printf("Enter the any input X1, X2 ( -5 < X < 5 )\n");
	printf("If they are in the triangle that you generated, the EBP function will inspect it.\n");
	
	while (1)
	{
		printf("X1 X2: ");
		scanf_s("%lf", &x_inspect[0]);
		scanf_s(" %lf", &x_inspect[1]);

		if (inspectTriangle(x_inspect, POSITIVE_INTERCEPT, POSITIVE_INTERCEPT, POSITIVE_INTERCEPT))
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
	inputBuffer.error[0] = (inputBuffer.error[0] > THRESHOLD);

	if (inputBuffer.error[0] == 1)	// error가 많이 있으면
	{
		printf("There is fatal error\n");
		return -1;
	}

	else if (inputBuffer.error[0] == 0)	// error가 거의 없으면
	{
		printf("Well Done!\n");
		return 0;
	}
}
