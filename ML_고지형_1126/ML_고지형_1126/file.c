#include "main.h"

int writeData(inputData* inputBuffer)	// 입출력 데이터 저장
{
	FILE* pFile = NULL;
	fopen_s(&pFile, ".\\python\\write_data.txt", "wt");

	if (pFile)
	{
		for (int i = 0; i < NUMBER_OF_INPUT; i++)
			fprintf_s(pFile, "X%d\t", i + 1);

		fprintf_s(pFile, "TARGET\t");

		for (int i = 0; i < NUMBER_OF_OUTPUT; i++)
			fprintf_s(pFile, "Y%d\t", i + 1);

		fprintf_s(pFile, "\n");

		for (int j = 0; j < NUMBER_OF_DATA; j++)
		{
			for (int i = 0; i < NUMBER_OF_INPUT; i++)
				fprintf_s(pFile, "%+lf\t", inputBuffer->x[i][j]);

			fprintf_s(pFile, "%+lf\t", inputBuffer->target[j]);

			for (int i = 0; i < NUMBER_OF_OUTPUT; i++)
				fprintf_s(pFile, "%+lf\t", inputBuffer->y[i][j]);	// y가 1이면 y와 타겟간의 간격이 0.5 이하..?

			fprintf_s(pFile, "\n");
		}

		fclose(pFile);

		return 0;	// success
	}

	printf("File open error!\n");

	return -1;	// failed
}

int writeError(inputData* inputBuffer)	// Epoch마다 Error 저장
{
	int epoch = MAX_EPOCH;
	FILE* pFile = NULL;

	fopen_s(&pFile, ".\\python\\write_error.txt", "wt");

	if (pFile)
	{
		fprintf_s(pFile, "Epoch\t");
		
		for (int i = 0; i < NUMBER_OF_OUTPUT; i++)
			fprintf_s(pFile, "ERROR%d\t", i+1);
		
		fprintf_s(pFile, "\n");


		for (int j = 0; j < MAX_EPOCH; j++)
		{
			fprintf_s(pFile, "%08d\t", MAX_EPOCH - epoch);
		
			for (int i = 0; i < NUMBER_OF_OUTPUT; i++)
			fprintf_s(pFile, "%lf\t", inputBuffer->errorSum[i][j]);
			
			fprintf_s(pFile, "\n");

			epoch--;
		}

		fclose(pFile);

		return 0;	// success
	}

	printf("File open error!\n");

	return -1;	// failed
}

int makeGrid(gridData* gridBuffer)
{
	FILE* pFile = NULL;
	double grid;
	double totalOutputError = 0;

	for (int i = 0; i < NUMBER_OF_INPUT; i++)
	{
		grid = -5;
	
		for (int j = 0; j < NUMBER_OF_GRID_DATA; j++)
		{
			gridBuffer->x[i][j] = grid;
			grid = grid + 0.1;	// grid는 -5부터 5까지.
		}
	}

	for (int k = 0; k < NUMBER_OF_GRID_DATA; k++)
		for (int i = 0; i < NUMBER_OF_GRID_DATA; i++)
		{
			totalOutputError = 0;

			inputBuffer.x[0][0] = gridBuffer->x[0][k];
			inputBuffer.x[1][0] = gridBuffer->x[1][i];
			EBPCalc(&inputBuffer, 0);

			for (int numOutput = 0; numOutput < NUMBER_OF_OUTPUT; numOutput++)	// 각각의 에러의 합의 threshold인지 전체 에러 합의 threshold인지 체크 필요
			{
				inputBuffer.error[numOutput][i] = (inputBuffer.error[numOutput][i] > THRESHOLD);
				totalOutputError = totalOutputError + inputBuffer.error[numOutput][i];
			}

			if (totalOutputError == 0)
			{		
				if (gridTriangle(gridBuffer, k, i, X1_INTERCEPT, X2_INTERCEPT, HORIZON_INTERCEPT))
					gridBuffer->grid[NUMBER_OF_DATA * k + i] = 1;

				else
					gridBuffer->grid[NUMBER_OF_DATA * k + i] = 0;
			}

			else
				gridBuffer->grid[NUMBER_OF_DATA * k + i] = 0;
		}

	fopen_s(&pFile, ".\\python\\grid_test.txt", "wt");

	if (pFile)
	{
		for (int i = 0; i < NUMBER_OF_INPUT; i++)
			fprintf_s(pFile, "X%d\t", i + 1);

			fprintf_s(pFile, "GRID\n");

			for (int j = 0; j < NUMBER_OF_GRID_DATA;j++)
			{
				for (int k = 0; k < NUMBER_OF_GRID_DATA; k++)
				{
					fprintf_s(pFile, "%+lf\t", gridBuffer->x[0][j]);
					fprintf_s(pFile, "%+lf\t", gridBuffer->x[1][k]);
					fprintf_s(pFile, "%d\t", gridBuffer->grid[NUMBER_OF_GRID_DATA *j + k]);
					fprintf_s(pFile, "\n");
				}
			}

		fclose(pFile);
	}

	return 0;
}