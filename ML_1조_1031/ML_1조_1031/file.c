#include "main.h"

int writeData(inputData* inputBuffer)	// 입출력 데이터 저장
{
	FILE* pFile = NULL;
	fopen_s(&pFile, ".\\python\\write_data.txt", "wt");

	if (pFile)
	{
		fprintf_s(pFile, "X1\tX2\tTARGET\tY\n");

		for (int i = 0; i < NUMBER_OF_DATA; i++)
		{
			fprintf_s(pFile, "%lf\t", inputBuffer->x[0][i]);
			fprintf_s(pFile, "%lf\t", inputBuffer->x[1][i]);
			fprintf_s(pFile, "%lf\t", inputBuffer->target[i]);
			fprintf_s(pFile, "%lf\n", inputBuffer->y[i]);	// y가 1이면 y와 타겟간의 간격이 0.5 이하..?
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
		fprintf_s(pFile, "Epoch\tERROR\n");

		for (int i = 0; i < MAX_EPOCH; i++)
		{
			fprintf_s(pFile, "%d\t", MAX_EPOCH - epoch);
			fprintf_s(pFile, "%lf\n", inputBuffer->errorSum[i]);
			epoch--;
		}

		fclose(pFile);

		return 0;	// success
	}

	printf("File open error!\n");

	return -1;	// failed
}


