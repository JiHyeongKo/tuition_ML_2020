#include <stdio.h>
#include "main.h"


int AND_problem(TrainingData* Buffer)	// AND ������ ���� ����� ���� ��ȯ���� ���� �� �����ϴ� �Լ�
{
	int check = 0;
	int Epoch = 0;	// try Ƚ��

	while (1)
	{
		check = AND_calc(Buffer);

		if (check == 0)	// runTraining�� ��� 0�� ��ȯ�ϸ�
		{
			lineData(&TrainingBuffer);	// python�� �� ������ ���
			printf("AND Problem Solved: Weight1: %lf, Weight2: %lf\n\n", Buffer->w1, Buffer->w2);
			return 0;
		}

		else if (Epoch > TRY_COUNT)
		{
			printf("No answer in this situation\n");
			exit();	// ���� ���� ���.
		}

		else
		{
			Epoch++;
			continue;	// �ϳ��� 0�� ��ȯ�ϸ� �ٽ�.
		}
	}
}


int AND_calc(TrainingData* Buffer)	// AND ������ ���� �Էµ� ���� ���� �����ϴ� �Լ�
{
	int condition[4];

	memset(condition, 0, sizeof(condition));	// condition�� ����� �� �ʱ�ȭ

	initTraining(Buffer, 0, 0, 0);	// x1=0, x2=0, target=0
	condition[0] = runTraining(Buffer);

	initTraining(Buffer, 0, 1, 0);	// x1=0, x2=1, target=0
	condition[1] = runTraining(Buffer);

	initTraining(Buffer, 1, 0, 0);	// x1=1, x2=0, target=0
	condition[2] = runTraining(Buffer);

	initTraining(Buffer, 1, 1, 1);	// x1=1, x2=1, target=1
	condition[3] = runTraining(Buffer);

	if (!(condition[0] + condition[1] + condition[2] + condition[3]))	// runTraining�� ��� 0�� ��ȯ�ϸ�
		return 0;

	else	// �ϳ��� 1�� ��ȯ�ϸ�
		return -1;
}

int getOtherX(TrainingData* Buffer)	// ���ο� X1, X2�� ����ϴ� �Լ�
{
	double next_x1 = 0;
	double next_x2 = 0;
	double prev_w1 = 0;
	double prev_w2 = 0;

	prev_w1 = Buffer->w1;	//���� ���� ����
	prev_w2 = Buffer->w2;

	printf("You can put other X1, X2 bigger than the previous (X1: %lf, X2: %lf)\n", Buffer->x1, Buffer->x2);	// X1, X2�� ū ������ �ٲ㵵 �׻� AND problem�� �����.

	while (1)
	{
		scanf_s("%lf %lf", &next_x1, &next_x2);

		if (next_x1 > Buffer->x1&& next_x2 > Buffer->x2)
			initTraining(Buffer, next_x1, next_x2, Buffer->target);	// target�� ������

		else
		{
			printf("You need to put other Numbers bigger than previous numbers (X1: %lf, X2: %lf)\n", Buffer->x1, Buffer->x2);
			continue;	// �ٽ� �Է�
		}

		AND_calc(Buffer);	// �ٲ� x1, x2�� ���� �ٽ� ����

		if (prev_w1 == Buffer->w1 && prev_w2 == Buffer->w2)
			printf("Prediction Success (Weights are not changed): Weight1: %lf, Weight2: %lf\n\n", Buffer->w1, Buffer->w2);

		else
			printf("Failure\n");	// ����� �� �� ����

		return 0;
	}
}

int runTraining(TrainingData* Buffer)	// running Iterative algorithm 
{
	double s1_buffer = 0;
	double s2_buffer = 0;
	double sum_buffer = 0;
	int output_buffer = 0;

	int target = Buffer->target;
	double w1_buffer = Buffer->w1;	//�Է¹��� weight
	double w2_buffer = Buffer->w2;

	s1_buffer = (Buffer->x1) * w1_buffer;	// x1*w1
	s2_buffer = (Buffer->x2) * w2_buffer;	// x2*w2
	sum_buffer = s1_buffer + s2_buffer;	// s1+s2 �� ��

	if (sum_buffer >= Buffer->theta)	// sum�� theta���� ũ��
		output_buffer = 1;	
	
	else	// sum�� theta���� ������
		output_buffer = 0;

	if (output_buffer == target)	// �ǵ��� ��(theta)�� ������
		return 0;
	
	else if (output_buffer > target)	// �ǵ��� ��(theta)���� ũ��
	{
		if (s1_buffer == 0 && s2_buffer != 0)
			lessWeight(Buffer, 2);	// weight�� ����

		else if (s1_buffer != 0 && s2_buffer == 0)
			lessWeight(Buffer, 1); // weight�� ����

		else	// �̵� ���� �ƴ� ���� �� �� ���̸�, �ٸ����� Ư���� ���� �÷���.
		{
			lessWeight(Buffer, 1); // weight�� ����
			lessWeight(Buffer, 2);	// weight�� ����
		}

		return 1;
	}

	else if (output_buffer < target)	// �ǵ��� ��(theta)���� ������
	{
		if (s1_buffer == 0 && s2_buffer != 0)
			moreWeight(Buffer, 2); // weight�� ����

		else if (s1_buffer != 0 && s2_buffer == 0)
			moreWeight(Buffer, 1); // weight�� ����

		else	// �̵� ���� �ƴ� ���� �� �� �ø���, �ٸ����� Ư���� ���� �ٿ���.
		{
			moreWeight(Buffer, 1); // weight�� ����
			moreWeight(Buffer, 2); // weight�� ����
		}

		return 2;
	}
}