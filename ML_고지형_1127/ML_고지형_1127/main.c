#include "main.h"

int main(void)
{
	double x_inspect[2] = { 0, };

	while (1)
	{
		int inspectTime = 0;
		int orderBuffer = inputBuffer.time;
		memset(&inputBuffer, 0, sizeof(inputData));
		memset(&inspectBuffer, 0, sizeof(inputData));
		inputBuffer.time = orderBuffer;
		int endCnt = ALLOW_ORDER;

		enterInput(&inputBuffer);
		initParam(&inputBuffer);

		if(NUMBER_OF_DATA == 50) // only use at 50 data input for test.
		loadData(&inputBuffer, "Training_data.txt");	

		inspectParam(&inputBuffer, &inspectBuffer);
		initEvaluation(&inspectBuffer);

		for (int i = 0; i < MAX_EPOCH; i++)
		{
			for (int j = 0; j < NUMBER_OF_DATA; j++)
			{
				EBPCalc(&inputBuffer, j);

				for (int numOutput = 0; numOutput < inputBuffer.outputNum; numOutput++)
					inputBuffer.errorSum[numOutput][i] = inputBuffer.errorSum[numOutput][i] + (inputBuffer.error[numOutput][j]);
			}

			if (i % INSPECT_TIME == 0)	// every 100 times
				{
					copyWeight(&inputBuffer, &weightBuffer[inspectTime++]);
				}
		}
		
		writeData(&inputBuffer);
		writeError(&inputBuffer);
		
		// convergence inspection
		for (int i = 0; i < inspectTime; i++)
		{
			pasteWeight(&inspectBuffer, &weightBuffer[i]);
			for (int j = 0; j < NUMBER_OF_DATA; j++)
			{
				EBPCalc(&inspectBuffer, j);

				for (int numOutput = 0; numOutput < NUMBER_OF_OUTPUT; numOutput++)
					inspectBuffer.errorSum[numOutput][i* INSPECT_TIME] = inspectBuffer.errorSum[numOutput][i* INSPECT_TIME] + (inspectBuffer.error[numOutput][j]);
			}

			writeEvaluation(&inspectBuffer, i * INSPECT_TIME);
		}

		if(inputBuffer.inputNum ==2)	// 2 layers -> get grid test
			makeGrid2D(&gridBuffer);

		printf("\n");
	}

	return 0;
}
