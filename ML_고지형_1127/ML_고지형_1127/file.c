#include "main.h"
#include <time.h>
struct tm* t;
time_t tnow;

int loadData(inputData* inputBuffer, char *fileName)	// �ؽ�Ʈ ���� ������ �о���� �Լ�
{
	FILE* pFile = NULL;
	fopen_s(&pFile, fileName, "rt");

	if (pFile)
	{
		for (int j = 0; j < NUMBER_OF_DATA; j++)
		{
			int i = 8;
			fscanf_s(pFile, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
				&inputBuffer->x[i--][j], &inputBuffer->x[i--][j], &inputBuffer->x[i--][j],
				&inputBuffer->x[i--][j], &inputBuffer->x[i--][j], &inputBuffer->x[i--][j],
				&inputBuffer->x[i--][j], &inputBuffer->x[i--][j], &inputBuffer->x[i--][j],
				&inputBuffer->target[j]);
			// �Ųٷ� �д´�;
		}

		fclose(pFile);
	}
	else
		printf("error\n");
	return 0;
}

int writeData(inputData* inputBuffer)	// ����� ������ ����
{
	FILE* pFile = NULL;
	char fileName[128] = ".\\python\\write_data";
	char time[10];
	sprintf(time, "%d", inputBuffer->time);
	strcat(fileName, time);
	strcat(fileName, ".txt");
	fopen_s(&pFile, fileName, "wt");

	if (pFile)
	{
		for (int i = 0; i < inputBuffer->inputNum; i++)
			fprintf_s(pFile, "X%d\t", i + 1);

		fprintf_s(pFile, "TARGET\t");

		for (int i = 0; i < inputBuffer->outputNum; i++)
			fprintf_s(pFile, "Y%d\t", i + 1);

		fprintf_s(pFile, "\n");

		for (int j = 0; j < NUMBER_OF_DATA; j++)
		{
			for (int i = 0; i < inputBuffer->inputNum; i++)
				fprintf_s(pFile, "%+lf\t", inputBuffer->x[i][j]);

			fprintf_s(pFile, "%+lf\t", inputBuffer->target[j]);

			for (int i = 0; i < inputBuffer->outputNum; i++)
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
	char fileName[128] = ".\\python\\write_error";
	char order[10];
	sprintf(order, "%d", inputBuffer->time);
	strcat(fileName, order);
	strcat(fileName, ".txt");
	fopen_s(&pFile, fileName, "wt");
	double errorSum = 0;

	if (pFile)
	{
		fprintf_s(pFile, "Epoch\t");
		
		if(inputBuffer->outputNum > 1)
			fprintf_s(pFile, "ERRORSUM\t");


		for (int i = 0; i < inputBuffer->outputNum; i++)
			fprintf_s(pFile, "ERROR%d\t", i+1);
		
		fprintf_s(pFile, "\n");


		for (int j = 0; j < MAX_EPOCH; j++)
		{
			errorSum = 0;

			fprintf_s(pFile, "%08d\t", MAX_EPOCH - epoch);
			
			if (inputBuffer->outputNum > 1)
			{
				for (int i = 0; i < inputBuffer->outputNum; i++)
					errorSum = errorSum + inputBuffer->errorSum[i][j];

				fprintf_s(pFile, "%lf\t", errorSum);
			}

			for (int i = 0; i < inputBuffer->outputNum; i++)
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

int initEvaluation(inputData* inputBuffer)	// evaluation data �����ϱ� ���� ������ ����� �Լ�
{
	FILE* pFile = NULL;
	char fileName[128] = ".\\python\\write_evaluate";
	char order[10];;
	sprintf(order, "%d", inputBuffer->time);
	strcat(fileName, order);
	strcat(fileName, ".txt");
	fopen_s(&pFile, fileName, "wt");

	if (pFile)
	{
		fprintf_s(pFile, "Epoch\t");

		fprintf_s(pFile, "ERROR\t");

		fprintf_s(pFile, "TIME\t");

		fprintf_s(pFile, "\n");
		fclose(pFile);

		return 0;	// success
	}

	printf("File open error!\n");
	return -1;	// failed
}

int writeEvaluation(inputData* inputBuffer, int epoch)
{
	FILE* pFile = NULL;
	char fileName[128] = ".\\python\\write_evaluate";
	char order[10];
	sprintf(order, "%d", inputBuffer->time);
	strcat(fileName, order);
	strcat(fileName, ".txt");
	fopen_s(&pFile, fileName, "at");
	double errorSum = 0;

	if (pFile)
	{
		fprintf_s(pFile, "%08d\t", epoch);

		for (int i = 0; i < NUMBER_OF_OUTPUT; i++)
			errorSum = errorSum + inputBuffer->errorSum[i][epoch];

		fprintf_s(pFile, "%08lf\t", errorSum);

		time(&tnow);
		t = (struct tm*) localtime(&tnow);

		fprintf_s(pFile, "%04d/", t->tm_year + 1900);	// �Է� �ð� ��Ÿ���� �κ�
		fprintf_s(pFile, "%02d/", t->tm_mon);
		fprintf_s(pFile, "%02d ", t->tm_mday);
		fprintf_s(pFile, "%02d:", t->tm_hour);
		fprintf_s(pFile, "%02d:", t->tm_min);
		fprintf_s(pFile, "%02d\r\n", t->tm_sec);

		fclose(pFile);
		return 0;	// success
	}

	printf("File open error!\n");
	return -1;	// failed
}