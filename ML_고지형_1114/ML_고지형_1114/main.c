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
				printf("%d ���� %lf\n", k, inputBuffer.errorSum[k][i]);
			}
		}

		printf("%d ���� %lf\n", k, inputBuffer.errorSum[k][i]);

		if (inputBuffer.errorSum[k][i] < ALLOW_TOTAL_ERROR)	// ������ ����� �۾����� padding �� break
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

	////////////// weight �����ð�!, ������ ���� Ư���� �ﰢ�� ���ο� �ִ� �ƹ� ���ڳ� �־ ���� ���� //////////////
	printf("Enter the any input X1, X2 ( -5 < X < 5 )\n");
	printf("If they are in the triangle that you generated, the EBP function will inspect it.\n");
	
	inspectResult(x_inspect);
}
