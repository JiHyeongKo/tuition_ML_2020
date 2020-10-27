#include <stdio.h>
#include <string.h>
#include "main.h"

int main(void)
{
	TrainingData AND_Buffer;
	TrainingData OR_Buffer;

	memset(&TrainingBuffer, 0, sizeof(TrainingBuffer));
	memset(&AND_Buffer, 0, sizeof(AND_Buffer));
	memset(&OR_Buffer, 0, sizeof(OR_Buffer));

	getWeight(&TrainingBuffer);

	if (solve_problem(&TrainingBuffer, &AND_Buffer, &OR_Buffer))	// 1�� ��ȯ�ϸ�
		return -1;	// �� ���� ��� ���������Ƿ� ����

	getOtherX(&AND_Buffer);
	getOtherX(&OR_Buffer);

	return 0;
}
