#include <stdio.h>
#include <string.h>
#include "main.h"

int solve_problem(TrainingData* Buffer, TrainingData* AND_Buffer, TrainingData* OR_Buffer)	// 문제에 대해 연산된 값의 반환값에 따라 논리 전개하는 함수
{
	int check_AND = 0;
	int check_OR = 0;
	int Epoch = 0;	// try 횟수

	while (1)
	{
		Buffer->logic = AND;
 		check_AND = calc(Buffer);	// 성공시 0을 반환

		if (check_AND == 0)	// runTraining이 모두 0을 반환하면
		{
			lineData(&TrainingBuffer);	// python에 쓸 데이터 출력
			printf("AND Problem Solved: Weight1: %lf, Weight2: %lf\n\n", Buffer->w1, Buffer->w2);
			memcpy(AND_Buffer, Buffer, sizeof(TrainingData));	// 다른 버퍼에 저장
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
			continue;	// 하나라도 타겟과 다른 값을 반환하면 다시.
		}
	}

	while (1)
	{
		Buffer->logic = OR;
		check_OR = calc(Buffer);	// 성공시 0을 반환

		if (check_OR == 0)	// runTraining이 모두 0을 반환하면
		{
			lineData(&TrainingBuffer);	// python에 쓸 데이터 출력
			printf("OR Problem Solved: Weight1: %lf, Weight2: %lf\n\n", Buffer->w1, Buffer->w2);
			memcpy(OR_Buffer, Buffer, sizeof(TrainingData));	// 다른 버퍼에 저장
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
			continue;	// 하나라도 타겟과 다른 값을 반환하면 다시.
		}
	}

	return (check_AND & check_OR);	// 0 을 반환하면 적어도 하나는 성공, 1을 반환하면 둘 다 실패
}


int calc(TrainingData* Buffer)	// 문제에 대해 입력된 값에 따라 연산하는 함수
{
	int condition[4];
	memset(condition, 0, sizeof(condition));	// condition에 저장된 값 초기화

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

	if (!(condition[0] + condition[1] + condition[2] + condition[3]))	// runTraining이 모두 0을 반환하면
		return 0;

	else	// 하나라도 1을 반환하면
		return 1;

}

int getOtherX(TrainingData* Buffer)	// 새로운 X1, X2로 계산하는 함수
{
	double next_x1 = 0;
	double next_x2 = 0;
	double prev_w1 = 0;
	double prev_w2 = 0;

	prev_w1 = Buffer->w1;	//이전 값을 저장
	prev_w2 = Buffer->w2;

	if (Buffer->logic == AND)
		printf("AND Logic: You can put other X1, X2 bigger than the previous (X1: %lf, X2: %lf)\t", Buffer->x1, Buffer->x2);	// X1, X2를 큰 값으로 바꿔도 항상 식이 성사됨.

	else if (Buffer->logic == OR)
		printf("OR Logic: You can put other X1, X2 bigger than the previous (X1: %lf, X2: %lf)\t", Buffer->x1, Buffer->x2);	// X1, X2를 큰 값으로 바꿔도 항상 식이 성사됨.

	else	// 조건에 맞는 weight 값을 구하지 못 했을 때.
		return -1;

	while (1)
	{
		scanf_s("%lf %lf", &next_x1, &next_x2);

		if (next_x1 > Buffer->x1&& next_x2 > Buffer->x2)
			initTraining(Buffer, next_x1, next_x2, Buffer->target);	// target은 기존값

		else
		{
			printf("You need to put other Numbers bigger than previous numbers (X1: %lf, X2: %lf)\t", Buffer->x1, Buffer->x2);
			continue;	// 다시 입력
		}

		calc(Buffer);	// 바뀐 x1, x2에 대해 다시 연산

		if (prev_w1 == Buffer->w1 && prev_w2 == Buffer->w2 || ( Buffer->error < MAXIMUM_ERR && Buffer->error > -1* MAXIMUM_ERR))
		{
			if (Buffer->logic == AND)
				printf("Your AND Logic Prediction Success (Weights are not changed): Weight1: %lf, Weight2: %lf\n\n", Buffer->w1, Buffer->w2);

			else if (Buffer->logic == OR)
				printf("Your OR Logic Prediction Success (Weights are not changed): Weight1: %lf, Weight2: %lf\n\n", Buffer->w1, Buffer->w2);
		}

		else
		{
			printf("Failure\n");	// 여기로 올 일 거의 없음

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
	double w1_buffer = Buffer->w1;	//입력받은 weight
	double w2_buffer = Buffer->w2;

	if (Buffer->mode == ITERATIVE)
	{
		s1_buffer = (Buffer->x1) * w1_buffer;	// x1*w1
		s2_buffer = (Buffer->x2) * w2_buffer;	// x2*w2
		sum_buffer = s1_buffer + s2_buffer;	// s1+s2 후 비교

		if (sum_buffer >= Buffer->theta)	// sum이 theta보다 크면
			output_buffer = 1;

		else	// sum이 theta보다 작으면
			output_buffer = 0;

		if (output_buffer == target)	// 의도한 값(theta)과 같으면
			return 0;

		else if (output_buffer > target)	// 의도한 값(theta)보다 크면
		{
			if (s1_buffer == 0 && s2_buffer != 0)
				lessWeight(Buffer, 2);	// weight을 감소

			else if (s1_buffer != 0 && s2_buffer == 0)
				lessWeight(Buffer, 1); // weight을 감소

			else	// 이도 저도 아닐 때는 둘 다 줄이면, 다른데서 특정한 것은 늘려줌.
			{
				lessWeight(Buffer, 1); // weight을 감소
				lessWeight(Buffer, 2);	// weight을 감소
			}

			return 1;
		}

		else if (output_buffer < target)	// 의도한 값(theta)보다 작으면
		{
			if (s1_buffer == 0 && s2_buffer != 0)
				moreWeight(Buffer, 2); // weight을 증가

			else if (s1_buffer != 0 && s2_buffer == 0)
				moreWeight(Buffer, 1); // weight을 증가

			else	// 이도 저도 아닐 때는 둘 다 늘리면, 다른데서 특정한 것은 줄여줌.
			{
				moreWeight(Buffer, 1); // weight을 증가
				moreWeight(Buffer, 2); // weight을 증가
			}

			return 2;
		}
	}

	else if (Buffer->mode == DELTA)
	{
		double error = 0xff;	// 초기값은 크게 잡아준다.
		int tryCount = TRY_COUNT;
		int target = 0;
		double w1_store[TRY_COUNT];
		double w2_store[TRY_COUNT];
		memset(w1_store, 0, sizeof(w1_store));
		memset(w2_store, 0, sizeof(w2_store));

		while (error > MAXIMUM_ERR || error < -1* MAXIMUM_ERR)	// 정확한 0은 못 만듦... 충분히 작은값
		{
			target = Buffer->target;
			w1_buffer = Buffer->w1;	//입력받은 weight
			w2_buffer = Buffer->w2;
			w1_store[TRY_COUNT - tryCount] = w1_buffer;	// 기존값 저장
			w2_store[TRY_COUNT - tryCount] = w2_buffer;	// 기존값 저장

			s1_buffer = (Buffer->x1) * w1_buffer;	// x1*w1
			s2_buffer = (Buffer->x2) * w2_buffer;	// x2*w2
			sum_buffer = s1_buffer + s2_buffer;	// s1+s2 후 비교. 
			
			error = (target - sum_buffer + Buffer->theta);	// 원하는 타겟 값과 실제 값(여기서 theta는 절편)과의 차를 에러로 사용

			if (sum_buffer >= Buffer->theta)	// sum이 theta보다 크면
				output_buffer = 1;

			else	// sum이 theta보다 작으면
				output_buffer = 0;

			if (output_buffer == target)	// 의도한 값(theta)과 같으면
				break;

			else	// 의도한 값과 다르면
			{
				Buffer->w1 = w1_buffer + (ETHA * error * (Buffer->x1));
				Buffer->w2 = w2_buffer + (ETHA * error * (Buffer->x2));

				tryCount--;

				if (!tryCount)
					return 1;	// 실패

				else if ((Buffer->w1 < MAXIMUM_ERR && Buffer->w1 > -1 * MAXIMUM_ERR) && (Buffer->w2 < MAXIMUM_ERR && Buffer->w2 > -1 * MAXIMUM_ERR))
					return 2;	// 실패. weight이 굉장히 작아진 경우에, 답이 없는데 답이 있다고 하는 경우.
			}
		}

		dot_lineData(Buffer, w1_store, w2_store);	// weight 점 데이터로 출력
		return 0;
	}

	return -1;	
}