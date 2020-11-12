#include <stdio.h>
#include "main.h"

int main(void)
{
	memset(&TrainingBuffer, 0, sizeof(TrainingBuffer));

	getWeight(&TrainingBuffer);
	AND_problem(&TrainingBuffer);
	getOtherX(&TrainingBuffer);
	lineData(&TrainingBuffer);

	return 0;
}
