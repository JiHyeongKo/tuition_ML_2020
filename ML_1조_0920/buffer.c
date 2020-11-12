#include <stdio.h>
#include "main.h"

int getWeight(TrainingData* Buffer)	//  Ű����� weight, theta �Է�
{
	double w1_buffer = 0;
	double w2_buffer = 0;
	double theta = 0;

	while (1)
	{
		printf("Weight1 Weight2, Theta�� ������� �Է� ( 0 <= Weight <= 10)\n");
		scanf_s("%lf %lf %lf", &w1_buffer, &w2_buffer, &theta);

		if (w1_buffer <= 10 && w1_buffer >= 0 && w2_buffer <= 10 && w2_buffer >= 0)	// weigt
		{
			Buffer->w1 = w1_buffer;
			Buffer->w2 = w2_buffer;
			Buffer->theta = theta;

			return 0;
		}

		else
		{
			printf("you put wrong number. Try again\n");
			continue;	// ������ �ٸ��� �ٽ�
		}
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