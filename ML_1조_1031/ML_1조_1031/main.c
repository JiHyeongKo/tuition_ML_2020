#include "main.h"

int main(void)
{
	int i = 0;
	int j = 0;
	memset(&inputBuffer, 0, sizeof(inputData));

	enterInput(&inputBuffer);
	initParam(&inputBuffer);

	for (i = 0; i < MAX_EPOCH; i++)
	{
		for (j = 0; j < NUMBER_OF_DATA; j++)
		{
			EBPCalc(&inputBuffer, j);
			inputBuffer.errorSum[i] = inputBuffer.errorSum[i] + (pow(inputBuffer.error[j], 2.0) * 0.5);
		}
		printf("%d %lf\n", i, inputBuffer.errorSum[i]);	// 전체 에러합?
	}


	return 0;
}

/*
무엇을 구현해야하는가?
0. EBP 알고리즘 사용 - 이건 걍 쌩으로 구현
1. 히든뉴런 갯수 조절가능(3~10개)
2. epoch에 따른 에러를 error.txt 파일 저장, Learning curve 그리기 - file pointer랑 파이썬
3. y에 대한 grid test(threshold: 0.5) - 파이썬
4. Bias 유무 기능 추가 - 얘는 변수를 추가하거나 나중에 구조체 변경
*/