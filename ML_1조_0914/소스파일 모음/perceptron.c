// 여기서는 연산하는 식을 넣습니다.

#include <stdio.h>
#include <string.h>
#include "main.h"

int init_manual(Iterative* Data)
{
	double w1, w2, theta;
	w1 = 0;
	w2 = 0;
	theta = 0;

	while (1)
	{
		printf("enter the w1, w2, theta ( [ |w1, w2, theta| < 1 ], [ w1, w2 != 0 ] ) \n");
		scanf_s("%lf %lf %lf", &w1, &w2, &theta);

		if ((w1 != 0) && (w2 != 0) && (w1 <= 1) && (w2 <= 1) && (w1 >= -1) && (w2 >= -1) && (theta <= 1) && (theta >= -1))
		{
			Data->W1 = w1;
			Data->W2 = w2;
			Data->THETA = theta;
			printf("Initialize setting is done - W1: %lf, W2: %lf, THETA: %lf \n", Data->W1, Data->W2, Data->THETA);

			return SUCCESS;	// done
		}

		else
		{
			printf("You entered wrong number or format. Retry again\n");
			continue;
		}
	}
}

double multiple(Iterative* Data, int MODE)
{
	double S = 0;

	while (1)
	{
		if (MODE == FIRST)
		{
			S = (Data->X1) * (Data->W1); 	// x, w 값 곱하기
			return S;
		}

		else if (MODE == SECOND)
		{
			S = (Data->X2) * (Data->W2); 	// x, w 값 곱하기
			return S;
		}

		else
		{
			printf("You put number of invalid MODE. Check the number and retry");
			exit(0);	// invalid MODE
		}
	}
}

double sigma(double S1, double S2)
{
	double sum = 0;
	sum = S1 + S2;

	return sum;	// 합을 반환
}

int compare(Iterative* Data)
{
	double S1 = 0;
	double S2 = 0;
	double comp_sum = 0;
	double comp_theta = 0;

	S1 = multiple(Data, FIRST);
	S2 = multiple(Data, SECOND);
	comp_sum = sigma(S1, S2);
	comp_theta = Data->THETA;

	if (comp_sum >= comp_theta)
		return 1;

	else
		return 0;
	// theta랑 비교해서 크거나 같으면 1, 작으면 0  반환
	//연산 후 저장까지
}


