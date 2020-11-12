// 데이터가 될 파일을 만들고 입출력 하겠습니다.

#include <stdio.h>
#include <string.h>
#include "main.h"

int input_data(Iterative *Data)
{
	double x1, x2;

	x1 = 0;
	x2 = 0;

	FILE* pFile;
	fopen_s(&pFile, ".\\input_data.txt", "w");

	if (pFile) 
	{
		fprintf_s(pFile, "X1(DYNAMIC)\tX2(DYNAMIC)\tW1(STATIC)\tW2(STATIC)\tTHETA(STATIC)\n");

		for (x2 = 1; x2 >= -1; x2 -= 0.1)
		{
			for (x1 = -1; x1 <= 1; x1 += 0.1)
			{
				fprintf_s(pFile, "%lf\t%lf\t%lf\t%lf\t%lf\n", x1, x2, Data->W1, Data->W2, Data->THETA);		
			}
		}

		fclose(pFile);
		printf("input data done\n");

		return SUCCESS;	// success
	}
	
	return FAILURE;	// failure
}

int output_data(Iterative *Data)
{
	char str_buf[100];
	memset(str_buf, 0, sizeof(str_buf));

	FILE* pFile;
	FILE* yFile;

	fopen_s(&pFile, ".\\input_data.txt", "r");
	fopen_s(&yFile, ".\\output_data.txt", "w");

	if (pFile && yFile) 
	{
		fprintf_s(yFile, "Y(OUTPUT)\tX1(DYNAMIC)\tX2(DYNAMIC)\tW1(STATIC)\tW2(STATIC)\tTHETA(STATIC)\n");
		fgets(str_buf, sizeof(str_buf), pFile);	// 초반 line 처리

			while (!feof(pFile))
			{
				fgets(str_buf, sizeof(str_buf), pFile);
				if (feof(pFile))
					break;	// 중복현상 방지

				sscanf_s(str_buf, "%lf\t%lf\t%lf\t%lf\t%lf", &Data->X1, &Data->X2, &Data->W1, &Data->W2, &Data->THETA);
				
				Data->Y = compare(Data); //여기서 연산하는 함수 호출
				fprintf_s(yFile, "%d\t%lf\t%lf\t%lf\t%lf\t%lf\n", Data->Y, Data->X1, Data->X2, Data->W1, Data->W2, Data->THETA);
			}

			fclose(pFile);
			fclose(yFile);

			//printf("output data done %lf %lf %lf %lf %lf %d\n", Data->X1, Data->X2, Data->W1, Data->W2, Data->THETA, Data->Y);	// to test
			printf("output data done\n");

			return SUCCESS;	// success
	}

	return FAILURE;	// fail
}

int line_data(double m, double n)
{
	FILE* pFile;
	fopen_s(&pFile, ".\\python\\line_data.txt", "w");

	if (pFile)
	{
		fprintf_s(pFile, "x2 = (m)*x1 + n (1st row: m , 2nd row: n)\n");
		fprintf_s(pFile, "%lf\n", m);
		fprintf_s(pFile, "%lf\n", n);

		fclose(pFile);

		return SUCCESS;	// success
	}

	return FAILURE;	// failure
}