#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_NUERON 5
#define MAX_EPOCH 100
#define LEARNING_GAIN 0.5	// LEARNING_GAIN : (0~1)

typedef struct  TrainingData
{
	double x1;
	double x2;
	double weight[NUMBER_OF_NUERON];
	double error;
	double target;
	double y;
	int nueron;
	int bias;
} TrainingData;

TrainingData dataBuffer;
#endif