#include "main.h"

int makeGrid2D(gridData* gridBuffer)	// use only in 2 dimesion
{
	FILE* pFile = NULL;
	char fileName[128] = ".\\python\\grid_test";
	char time[10];
	sprintf(time, "%d", inputBuffer.time);
	strcat(fileName, time);
	strcat(fileName, ".txt");
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
				if (gridBoundary(gridBuffer, k, i, X1_INTERCEPT, X2_INTERCEPT, HORIZON_INTERCEPT))
					gridBuffer->grid[NUMBER_OF_GRID_DATA * k + i] = 1;

				else
					gridBuffer->grid[NUMBER_OF_GRID_DATA * k + i] = 0;
			}

			else
			{
				gridBuffer->grid[NUMBER_OF_GRID_DATA * k + i] = 0;
				printf("Problem: %lf %lf\n", inputBuffer.x[0][0], inputBuffer.x[1][0]);
			}
		}

	fopen_s(&pFile, fileName, "wt");

	if (pFile)
	{
		for (int i = 0; i < NUMBER_OF_INPUT; i++)
			fprintf_s(pFile, "X%d\t", i + 1);

		fprintf_s(pFile, "GRID\n");

		for (int j = 0; j < NUMBER_OF_GRID_DATA; j++)
		{
			for (int k = 0; k < NUMBER_OF_GRID_DATA; k++)
			{
				fprintf_s(pFile, "%+lf\t", gridBuffer->x[0][j]);
				fprintf_s(pFile, "%+lf\t", gridBuffer->x[1][k]);
				fprintf_s(pFile, "%d\t", gridBuffer->grid[NUMBER_OF_GRID_DATA * j + k]);
				fprintf_s(pFile, "\n");
			}
		}

		fclose(pFile);
	}

	return 0;
}