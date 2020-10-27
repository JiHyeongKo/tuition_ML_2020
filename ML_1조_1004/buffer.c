#include <stdio.h>
#include "main.h"

int getWeight(TrainingData* Buffer)	//  Ű����� weight, theta �Է�
{
	double w1_buffer = 0;
	double w2_buffer = 0;
	int mode = 0;

	while (1)
	{
		printf("MODE �Է� ( Iterative Algorithm: 1 �� Delta Rule: 2 )\t");
		scanf_s("%d", &mode);

		if (mode == ITERATIVE || mode == DELTA)
		{
			double theta = 0;
			
			if(mode == DELTA)
				init_dot_lineData();	// Delta ������ ���� ���� �ʱ�ȭ
			
			while (1)
			{
				printf("Weight1 Weight2, Theta�� ������� �Է� ( -10 <= Weight <= 10)\t");
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
					continue;	// ������ �ٸ��� �ٽ�
				}
			}
		}

		else
			continue;	// mode�� ITERATIVE or DELTA�� �ƴ� ��

		return mode;	// mode�� ��ȯ ( ITERATIVE or DELTA )
	}

}

void initTraining(TrainingData* Buffer, double x1, double x2, int target)	// Data �ʱ�ȭ - x1, x2, target �� �Է��Ͽ� ����
{
	Buffer->x1 = x1;
	Buffer->x2 = x2;
	Buffer->target = target;
}

void lessWeight(TrainingData* Buffer, int weightNum) // weight�� ����
{
	if (weightNum == 1)
		Buffer->w1 = (Buffer->w1 * (1-LEARNING_GAIN));

	else
		Buffer->w2 = (Buffer->w2 * (1-LEARNING_GAIN));
}

void moreWeight(TrainingData* Buffer, int weightNum) // weight�� ����
{
	if (weightNum == 1)
		Buffer->w1 = (Buffer->w1 * (1+LEARNING_GAIN));

	else
		Buffer->w2 = (Buffer->w2 * (1+LEARNING_GAIN));
}