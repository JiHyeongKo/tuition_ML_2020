#include <stdio.h>
#include <string.h>
#include "main.h"

int main(void)
{
	memset(&dataBuffer, 0, sizeof(dataBuffer));
	memset(&coorBuffer, 0, sizeof(coorBuffer));

	init_manual(&dataBuffer);
	if (input_data(&dataBuffer) == SUCCESS)	// if already there is a data log file, you don't need to operate this function. this makes program slow.
		output_data(&dataBuffer);
	makeGraphic();
	classification(&coorBuffer);

	return 0;
}