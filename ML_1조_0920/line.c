#include <stdio.h>
#include "main.h"

int lineData(TrainingData* Buffer)	// A*x1 + B*x2 = C 의 coefficient 반환하여 그래프로 그릴 수 있는 자료로 사용.
{
	FILE* pFile;
	fopen_s(&pFile, ".\\python\\line_data.txt", "wt");

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