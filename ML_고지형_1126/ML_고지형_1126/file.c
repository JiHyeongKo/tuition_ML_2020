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

