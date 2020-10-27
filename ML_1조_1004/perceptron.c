#include <stdio.h>
#include <string.h>
#include "main.h"

int solve_problem(TrainingData* Buffer, TrainingData* AND_Buffer, TrainingData* OR_Buffer)	// ������ ���� ����� ���� ��ȯ���� ���� �� �����ϴ� �Լ�
{
	int check_AND = 0;
	int check_OR = 0;
	int Epoch = 0;	// try Ƚ��

	while (1)
	{
		Buffer->logic = AND;
 		check_AND = calc(Buffer);	// ������ 0�� ��ȯ

		if (check_AND == 0)	// runTraining�� ��� 0�� ��ȯ�ϸ�
		{
			lineData(&TrainingBuffer);	// python�� �� ������ ���
			printf("AND Problem Solved: Weight1: %lf, Weight2: %lf\n\n", Buffer->w1, Buffer->w2);
			memcpy(AND_Buffer, Buffer, sizeof(TrainingData));	// �ٸ� ���ۿ� ����
			break;
		}

		else if (Epoch > TRY_COUNT)
		{
			printf("No answer in this situation at AND Logic\n");
			break;
		}

		else
		{
			Epoch++;
			continue;	// �ϳ��� Ÿ�ٰ� �ٸ� ���� ��ȯ�ϸ� �ٽ�.
		}
	}

	while (1)
	{
		Buffer->logic = OR;
		check_OR = calc(Buffer);	// ������ 0�� ��ȯ

		if (check_OR == 0)	// runTraining�� ��� 0�� ��ȯ�ϸ�
		{
			lineData(&TrainingBuffer);	// python�� �� ������ ���
			printf("OR Problem Solved: Weight1: %lf, Weight2: %lf\n\n", Buffer->w1, Buffer->w2);
			memcpy(OR_Buffer, Buffer, sizeof(TrainingData));	// �ٸ� ���ۿ� ����
			break;
		}

		else if (Epoch > TRY_COUNT)
		{
			printf("No answer in this situation at OR Logic\n");
			break;
		}

		else
		{
			Epoch++;
			continue;	// �ϳ��� Ÿ�ٰ� �ٸ� ���� ��ȯ�ϸ� �ٽ�.
		}
	}

	return (check_AND & check_OR);	// 0 �� ��ȯ�ϸ� ��� �ϳ��� ����, 1�� ��ȯ�ϸ� �� �� ����
}


int calc(TrainingData* Buffer)	// ������ ���� �Էµ� ���� ���� �����ϴ� �Լ�
{
	int condition[4];
	memset(condition, 0, sizeof(condition));	// condition�� ����� �� �ʱ�ȭ

	if (Buffer->logic == AND)
	{
		initTraining(Buffer, 0, 0, 0);	// x1=0, x2=0, target=0
		condition[0] = runTraining(Buffer);

		initTraining(Buffer, 0, 1, 0);	// x1=0, x2=1, target=0
		condition[1] = runTraining(Buffer);

		initTraining(Buffer, 1, 0, 0);	// x1=1, x2=0, target=0
		condition[2] = runTraining(Buffer);

		initTraining(Buffer, 1, 1, 1);	// x1=1, x2=1, target=1
		condition[3] = runTraining(Buffer);
	}

	else if (Buffer->logic == OR)
	{
		initTraining(Buffer, 0, 0, 0);	// x1=0, x2=0, target=0
		condition[0] = runTraining(Buffer);

		initTraining(Buffer, 0, 1, 1);	// x1=0, x2=1, target=0
		condition[1] = runTraining(Buffer);

		initTraining(Buffer, 1, 0, 1);	// x1=1, x2=0, target=0
		condition[2] = runTraining(Buffer);

		initTraining(Buffer, 1, 1, 1);	// x1=1, x2=1, target=1
		condition[3] = runTraining(Buffer);
	}

	if (!(condition[0] + condition[1] + condition[2] + condition[3]))	// runTraining�� ��� 0�� ��ȯ�ϸ�
		return 0;

	else	// �ϳ��� 1�� ��ȯ�ϸ�
		return 1;

}

int getOtherX(TrainingData* Buffer)	// ���ο� X1, X2�� ����ϴ� �Լ�
{
	double next_x1 = 0;
	double next_x2 = 0;
	double prev_w1 = 0;
	double prev_w2 = 0;

	prev_w1 = Buffer->w1;	//���� ���� ����
	prev_w2 = Buffer->w2;

	if (Buffer->logic == AND)
		printf("AND Logic: You can put other X1, X2 bigger than the previous (X1: %lf, X2: %lf)\t", Buffer->x1, Buffer->x2);	// X1, X2�� ū ������ �ٲ㵵 �׻� ���� �����.

	else if (Buffer->logic == OR)
		printf("OR Logic: You can put other X1, X2 bigger than the previous (X1: %lf, X2: %lf)\t", Buffer->x1, Buffer->x2);	// X1, X2�� ū ������ �ٲ㵵 �׻� ���� �����.

	else	// ���ǿ� �´� weight ���� ������ �� ���� ��.
		return -1;

	while (1)
	{
		scanf_s("%lf %lf", &next_x1, &next_x2);

		if (next_x1 > Buffer->x1&& next_x2 > Buffer->x2)
			initTraining(Buffer, next_x1, next_x2, Buffer->target);	// target�� ������

		else
		{
			printf("You need to put other Numbers bigger than previous numbers (X1: %lf, X2: %lf)\t", Buffer->x1, Buffer->x2);
			continue;	// �ٽ� �Է�
		}

		calc(Buffer);	// �ٲ� x1, x2�� ���� �ٽ� ����

		if (prev_w1 == Buffer->w1 && prev_w2 == Buffer->w2 || ( Buffer->error < MAXIMUM_ERR && Buffer->error > -1* MAXIMUM_ERR))
		{
			if (Buffer->logic == AND)
				printf("Your AND Logic Prediction Success (Weights are not changed): Weight1: %lf, Weight2: %lf\n\n", Buffer->w1, Buffer->w2);

			else if (Buffer->logic == OR)
				printf("Your OR Logic Prediction Success (Weights are not changed): Weight1: %lf, Weight2: %lf\n\n", Buffer->w1, Buffer->w2);
		}

		else
		{
			printf("Failure\n");	// ����� �� �� ���� ����

			if (Buffer->logic == AND)
				printf("Your AND Logic Prediction Fail (Weights are not changed): Weight1: %lf, Weight2: %lf\n\n", Buffer->w1, Buffer->w2);

			else if (Buffer->logic == OR)
				printf("Your OR Logic Prediction Fail (Weights are not changed): Weight1: %lf, Weight2: %lf\n\n", Buffer->w1, Buffer->w2);
				
		}

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

	if (Buffer->mode == ITERATIVE)
	{
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

	else if (Buffer->mode == DELTA)
	{
		double error = 0xff;	// �ʱⰪ�� ũ�� ����ش�.
		int tryCount = TRY_COUNT;
		int target = 0;
		double w1_store[TRY_COUNT];
		double w2_store[TRY_COUNT];
		memset(w1_store, 0, sizeof(w1_store));
		memset(w2_store, 0, sizeof(w2_store));

		while (error > MAXIMUM_ERR || error < -1* MAXIMUM_ERR)	// ��Ȯ�� 0�� �� ����... ����� ������
		{
			target = Buffer->target;
			w1_buffer = Buffer->w1;	//�Է¹��� weight
			w2_buffer = Buffer->w2;
			w1_store[TRY_COUNT - tryCount] = w1_buffer;	// ������ ����
			w2_store[TRY_COUNT - tryCount] = w2_buffer;	// ������ ����

			s1_buffer = (Buffer->x1) * w1_buffer;	// x1*w1
			s2_buffer = (Buffer->x2) * w2_buffer;	// x2*w2
			sum_buffer = s1_buffer + s2_buffer;	// s1+s2 �� ��. 
			
			error = (target - sum_buffer + Buffer->theta);	// ���ϴ� Ÿ�� ���� ���� ��(���⼭ theta�� ����)���� ���� ������ ���

			if (sum_buffer >= Buffer->theta)	// sum�� theta���� ũ��
				output_buffer = 1;

			else	// sum�� theta���� ������
				output_buffer = 0;

			if (output_buffer == target)	// �ǵ��� ��(theta)�� ������
				break;

			else	// �ǵ��� ���� �ٸ���
			{
				Buffer->w1 = w1_buffer + (ETHA * error * (Buffer->x1));
				Buffer->w2 = w2_buffer + (ETHA * error * (Buffer->x2));

				tryCount--;

				if (!tryCount)
					return 1;	// ����

				else if ((Buffer->w1 < MAXIMUM_ERR && Buffer->w1 > -1 * MAXIMUM_ERR) && (Buffer->w2 < MAXIMUM_ERR && Buffer->w2 > -1 * MAXIMUM_ERR))
					return 2;	// ����. weight�� ������ �۾��� ��쿡, ���� ���µ� ���� �ִٰ� �ϴ� ���.
			}
		}

		dot_lineData(Buffer, w1_store, w2_store);	// weight �� �����ͷ� ���
		return 0;
	}

	return -1;	
}