#include "main.h"

int main(void)
{
	int i = 0;
	int j = 0;
	double cur = 1024, pre = 0;	// �ʱⰪ�� ����� ū ��.

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
		
		pre = cur;
		cur = inputBuffer.errorSum[i];
	
		if (cur > pre)	// �׷����� �������ٰ� �ö󰡸�...
			break;
		//printf("%d %lf\n", i, inputBuffer.errorSum[i]);	// ��ü ������?
	}

	writeData(&inputBuffer);
	writeError(&inputBuffer);

	return 0;
}

/*
������ �����ؾ��ϴ°�?
0. EBP �˰��� ��� - �̰� �� ������ ����
1. ���紺�� ���� ��������(3~10��)
2. epoch�� ���� ������ error.txt ���� ����, Learning curve �׸��� - file pointer�� ���̽�
3. y�� ���� grid test(threshold: 0.5) - ���̽�
4. Bias ���� ��� �߰� - ��� ������ �߰��ϰų� ���߿� ����ü ����
*/