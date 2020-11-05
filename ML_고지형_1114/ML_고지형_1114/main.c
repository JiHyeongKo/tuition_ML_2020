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

	////////////// weight �����ð�!, ������ ���� Ư���� �ﰢ�� ���ο� �ִ� �ƹ� ���ڳ� �־ ���� ���� //////////////
	printf("Enter the any input X1, X2 ( -5 < X < 5 )\n");
	printf("If they are in the triangle that you generated, the EBP function will inspect it.\n");
	
	inspectResult(x_inspect);
}
