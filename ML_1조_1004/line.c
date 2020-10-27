#include <stdio.h>
#include "main.h"

int lineData(TrainingData* Buffer)	// A*x1 + B*x2 = C �� coefficient ��ȯ�Ͽ� �׷����� �׸� �� �ִ� �ڷ�� ���.
{
	FILE* pFile = NULL;
	
	if(Buffer->logic == AND)
		fopen_s(&pFile, ".\\python\\AND_line_data.txt", "wt");

	else if (Buffer->logic == OR)
		fopen_s(&pFile, ".\\python\\OR_line_data.txt", "wt");

	if (pFile)
	{
		fprintf_s(pFile, "A*x1 + B*x2 = C\n");
		fprintf_s(pFile, "%lf\n", Buffer->w1);
		fprintf_s(pFile, "%lf\n", Buffer->w2);
		fprintf_s(pFile, "%lf\n", Buffer->theta);

		fclose(pFile);

		return 0;	// success
	}

	return -1;	// failure
}

void init_dot_lineData(void)	// Delta ������ ���� ���� �ʱ�ȭ
{
	FILE* and_pFile = NULL;
	FILE* OR_pFile = NULL;

	fopen_s(&and_pFile, ".\\python\\AND_dot_line_data.txt", "wt");
	if (and_pFile)
	{
		fprintf_s(and_pFile, "W1\tW2\n");
		fclose(and_pFile);
	}

	fopen_s(&OR_pFile, ".\\python\\OR_dot_line_data.txt", "wt");
	if(OR_pFile)
	{
		fprintf_s(OR_pFile, "W1 W2\n");
		fclose(OR_pFile);
	}
}

int dot_lineData(TrainingData* Buffer, double *w1_store, double *w2_store)	// A*x1 + B*x2 = C �� coefficient ��ȯ�Ͽ� �̵��ϴ� ���� �׷����� �׸� �� �ִ� �ڷ�� ���.
{
	FILE* pFile = NULL;

	if (Buffer->mode == ITERATIVE)
		return -1;

	else if (Buffer->mode == DELTA)
	{
		if (Buffer->logic == AND)
			fopen_s(&pFile, ".\\python\\AND_dot_line_data.txt", "at");

		else if (Buffer->logic == OR)
			fopen_s(&pFile, ".\\python\\OR_dot_line_data.txt", "at");

		if (pFile)
		{
			for (int i = 0; w1_store[i] != 0; i++)	// �迭 �ȿ� ��Ұ� 0�� �ƴ� ������ ���
				fprintf_s(pFile, "%lf %lf\n", w1_store[i], w2_store[i]);

			fclose(pFile);

			return 0;	// success
		}
	}
		return -1;	// failure
}