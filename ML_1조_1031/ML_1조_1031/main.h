#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _USE_MATH_DEFINES 
#include <math.h>

#define MAX_NUERON 10
#define MAX_EPOCH 10000
#define LEARNING_GAIN 0.5	// LEARNING_GAIN(ETHA) : (0~1)
#define THRESHOLD 0.5

#define NUMBER_OF_BIAS 1
#define NUMBER_OF_INPUT 2
#define NUMBER_OF_OUTPUT 1
#define NUMBER_OF_DATA 50

#define ABS(x)	((x) < 0 ? (-(x)) : (x))

typedef struct inputData
{
	int bias;
	double x[NUMBER_OF_INPUT][NUMBER_OF_DATA];
	double target[NUMBER_OF_DATA];
	double error[NUMBER_OF_DATA];
	double errorSum[MAX_EPOCH];
	int nueron;
	int weightNumber;
	double output[MAX_NUERON + NUMBER_OF_OUTPUT];
	double weight[MAX_NUERON + NUMBER_OF_OUTPUT][NUMBER_OF_BIAS + NUMBER_OF_INPUT];
	double biasWeight[NUMBER_OF_DATA];
} inputData;

inputData inputBuffer;
#endif

int enterInput(inputData* inputBuffer);
int initParam(inputData* inputBuffer);
int EBPCalc(inputData* inputBuffer, int order);
/*
EBP -> x1, x2, target, output(y or u), the number of nuerons(n), weight[3*n](without bias), weight[4*n](bias)
delta[n+1], delatWeight[same as weight], 학습데이터(랜덤하게 1,0 섞어서 각 25개씩), etha=0.5
*/
