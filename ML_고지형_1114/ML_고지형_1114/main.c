#include "main.h"

int main(void)
{
	int i = 0;
	int j = 0;
	double x_inspect[2] = { 0, };
	double error_inspect = 0;
	int answer = 0;
	int numOutput = 0;
	memset(&inputBuffer, 0, sizeof(inputData));

	enterInput(&inputBuffer);
	initParam(&inputBuffer);

	for (i = 0; i < MAX_EPOCH; i++)
	{
		for (j = 0; j < NUMBER_OF_DATA; j++)
		{
			EBPCalc(&inputBuffer, j);

			for (numOutput = 0; numOutput < NUMBER_OF_OUTPUT; numOutput++)
				inputBuffer.errorSum[numOutput][i] = inputBuffer.errorSum[numOutput][i] + (inputBuffer.error[numOutput][j]);
		}
		
		//for (numOutput = 0; numOutput < NUMBER_OF_OUTPUT; numOutput++)
			//printf("%d %d: %lf\n", i, numOutput, inputBuffer.errorSum[numOutput][i]);		
	}

	writeData(&inputBuffer);
	writeError(&inputBuffer);
	makeGrid(&gridBuffer);

	////////////// weight 검증시간!, 기존에 만든 특정한 삼각형 내부에 있는 아무 숫자나 넣어서 에러 검출 //////////////

	printf("Enter the any input X1, X2 ( -5 < X < 5 )\n");
	printf("If they are in the triangle that you generated, the EBP function will inspect it.\n");
	printf("Your trinagle range: (X2 < X1 + %d) && (X2 < -X1 + %d < 0) && (X1 > %+d)\n", X1_INTERCEPT, X2_INTERCEPT, -1*HORIZON_INTERCEPT);

	inspectResult(x_inspect);
}
