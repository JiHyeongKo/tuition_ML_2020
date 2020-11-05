#include "main.h"

int writeData(inputData* inputBuffer)	// ����� ������ ����
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
				fprintf_s(pFile, "%+lf\t", inputBuffer->y[i][j]);	// y�� 1�̸� y�� Ÿ�ٰ��� ������ 0.5 ����..?

			fprintf_s(pFile, "\n");
		}

		fclose(pFile);

		return 0;	// success
	}

	printf("File open error!\n");

	return -1;	// failed
}

int writeError(inputData* inputBuffer)	// Epoch���� Error ����
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
			grid = grid + 0.1;	// grid�� -5���� 5����.
		}
	}

	for (int k = 0; k < NUMBER_OF_GRID_DATA; k++)
		for (int i = 0; i < NUMBER_OF_GRID_DATA; i++)
		{
			totalOutputError = 0;

			inputBuffer.x[0][0] = gridBuffer->x[0][k];
			inputBuffer.x[1][0] = gridBuffer->x[1][i];
			EBPCalc(&inputBuffer, 0);

			for (int numOutput = 0; numOutput < NUMBER_OF_OUTPUT; numOutput++)	// ������ ������ ���� threshold���� ��ü ���� ���� threshold���� üũ �ʿ�
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