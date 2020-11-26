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

		//loadData(&inputBuffer, "Training_data(1126).txt");	// 학습데이터를 외부에서 불러옴.

		for (int i = 0; i < MAX_EPOCH; i++)
		{
			for (int j = 0; j < NUMBER_OF_DATA; j++)
			{
				EBPCalc(&inputBuffer, j);

				for (int numOutput = 0; numOutput < inputBuffer.outputNum; numOutput++)
					inputBuffer.errorSum[numOutput][i] = inputBuffer.errorSum[numOutput][i] + (inputBuffer.error[numOutput][j]);
			}

			if (i % INSPECT_TIME == 0)	// every 10 times
				{
					copyWeight(&inputBuffer, &weightBuffer[inspectTime++]);
				}
		}
		
		writeData(&inputBuffer);
		writeError(&inputBuffer);

		// inspection //

		inspectParam(&inputBuffer, &inspectBuffer);
		inspectParamByFile(&inspectBuffer, "test_data(1126).txt");	// 테스트 데이터를 외부에서 불러옴.
		pasteWeight(&inspectBuffer, &weightBuffer[inspectTime-1]);	// 보통은 나중것이 제일 작으니...

		for (int j = 0; j < NUMBER_OF_TEST_DATA; j++)
		{
			EBPInspect(&inspectBuffer, j);

			for (int numOutput = 0; numOutput < NUMBER_OF_OUTPUT; numOutput++)
				inspectBuffer.errorSum[numOutput][(inspectTime - 1) *INSPECT_TIME] = inspectBuffer.errorSum[numOutput][(inspectTime - 1) * INSPECT_TIME] + (inspectBuffer.error[numOutput][j]);
		}

		initEvaluation(&inspectBuffer);
		writeEvaluation(&inspectBuffer, (inspectTime - 1) * INSPECT_TIME);

		if(inputBuffer.inputNum ==2)	// 2 layers -> get grid test
			makeGrid2D(&gridBuffer);

		printf("\n");
	}

	return 0;
}
