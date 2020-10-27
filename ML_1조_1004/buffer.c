#include <stdio.h>
#include "main.h"

int getWeight(TrainingData* Buffer)	//  키보드로 weight, theta 입력
{
	double w1_buffer = 0;
	double w2_buffer = 0;
	int mode = 0;

	while (1)
	{
		printf("MODE 입력 ( Iterative Algorithm: 1 ↔ Delta Rule: 2 )\t");
		scanf_s("%d", &mode);

		if (mode == ITERATIVE || mode == DELTA)
		{
			double theta = 0;
			
			if(mode == DELTA)
				init_dot_lineData();	// Delta 데이터 저장 전에 초기화
			
			while (1)
			{
				printf("Weight1 Weight2, Theta를 순서대로 입력 ( -10 <= Weight <= 10)\t");
				scanf_s("%lf %lf %lf", &w1_buffer, &w2_buffer, &theta);

				if (w1_buffer <= 10 && w1_buffer >= -10 && w2_buffer <= 10 && w2_buffer >= -10)	// weight
				{
					Buffer->w1 = w1_buffer;
					Buffer->w2 = w2_buffer;
					Buffer->mode = mode;
					Buffer->theta = theta;
					break;
				}

				else
				{
					printf("you put wrong number. Try again\n");
					continue;	// 범위와 다르면 다시
				}
			}
		}

		else
			continue;	// mode가 ITERATIVE or DELTA가 아닐 때

		return mode;	// mode를 반환 ( ITERATIVE or DELTA )
	}

}

void initTraining(TrainingData* Buffer, double x1, double x2, int target)	// Data 초기화 - x1, x2, target 값 입력하여 저장
{
	Buffer->x1 = x1;
	Buffer->x2 = x2;
	Buffer->target = target;
}

void lessWeight(TrainingData* Buffer, int weightNum) // weight을 감소
{
	if (weightNum == 1)
		Buffer->w1 = (Buffer->w1 * (1-LEARNING_GAIN));

	else
		Buffer->w2 = (Buffer->w2 * (1-LEARNING_GAIN));
}

void moreWeight(TrainingData* Buffer, int weightNum) // weight을 증가
{
	if (weightNum == 1)
		Buffer->w1 = (Buffer->w1 * (1+LEARNING_GAIN));

	else
		Buffer->w2 = (Buffer->w2 * (1+LEARNING_GAIN));
}