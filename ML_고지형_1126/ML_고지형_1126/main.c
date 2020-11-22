#include "main.h"

int main(void)
{
	double x_inspect[2] = { 0, };

	memset(&inputBuffer, 0, sizeof(inputData));

	while (1)
	{
		double convergenceMinima = 99999999;
		int endCnt = ALLOW_ORDER;

		enterInput(&inputBuffer);
		initParam(&inputBuffer);
		initEvaluation(&inputBuffer);

		for (int i = 0; i < MAX_EPOCH; i++)
		{
			for (int j = 0; j < NUMBER_OF_DATA; j++)
			{
				EBPCalc(&inputBuffer, j);

				for (int numOutput = 0; numOutput < NUMBER_OF_OUTPUT; numOutput++)
					inputBuffer.errorSum[numOutput][i] = inputBuffer.errorSum[numOutput][i] + (inputBuffer.error[numOutput][j]);
			}
			
			if (i % 100 == 0)	// every 100 times
			{
				double errorSumBuffer = 0;

				writeEvaluation(&inputBuffer, i);
				
				for (int numOutput = 0; numOutput < NUMBER_OF_OUTPUT; numOutput++)
					errorSumBuffer = errorSumBuffer + inputBuffer.errorSum[numOutput][i];

				if (convergenceMinima > errorSumBuffer)
				{
					convergenceMinima = errorSumBuffer;
					endCnt = ALLOW_ORDER;
				}

				else if (convergenceMinima == errorSumBuffer)
				{
					endCnt--;

					if (endCnt == 0)
					{
						printf("Your error does not change and might be stopped.\n");
						break;
					}
				}

				else
				{
					int runMore = 0;
					printf("(Error: %lf) Your error being big. do you want to run more? (Yes: 1 /No: 0): ", convergenceMinima);
					scanf_s("%d", &runMore);

					if (runMore == 1)
						continue;

					else
						break;
				}
				/*
				else	// if sum of errors being bigger, or equal
				{
					endCnt--;

					if(endCnt == 0)	// count five times.
						break;	// escape!
					//////////////////////////////////////////////////////////////////////////////////////////
					// 만약에 여기서 이 부분 다음에 바로 수직으로 떨어질 정도라면? 여기서 버리는 기회비용은?//
					//////////////////////////////////////////////////////////////////////////////////////////
				}
				*/
			}
		}

		writeData(&inputBuffer);
		writeError(&inputBuffer);
		
		if(NUMBER_OF_INPUT==2)	// 2 layers -> get grid test
			makeGrid2D(&gridBuffer);

		printf("\n");
	}

	return 0;
}
