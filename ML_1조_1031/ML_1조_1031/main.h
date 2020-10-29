#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _USE_MATH_DEFINES 
#include <math.h>

#define MAX_NUERON 10
#define MAX_EPOCH 1000
#define ALLOW_ERROR 0.001
#define ALLOW_TOTAL_ERROR MAX_EPOCH * ALLOW_ERROR
#define LEARNING_GAIN 0.5	// LEARNING_GAIN(ETHA) : (0~1)
#define THRESHOLD 0.5
#define POSITIVE_INTERCEPT 3

#define NUMBER_OF_BIAS 1
#define NUMBER_OF_INPUT 2
#define NUMBER_OF_OUTPUT 1
#define NUMBER_OF_DATA 100

typedef struct inputData
{
	int bias;
	int nueron;
	int weightNumber;
	double x[NUMBER_OF_INPUT][NUMBER_OF_DATA];
	double target[NUMBER_OF_DATA];
	double y[NUMBER_OF_DATA];
	double error[NUMBER_OF_DATA];
	double errorSum[MAX_EPOCH];
	double output[MAX_NUERON + NUMBER_OF_OUTPUT];
	double weight[MAX_NUERON + NUMBER_OF_OUTPUT][NUMBER_OF_BIAS + NUMBER_OF_INPUT];
	double biasWeight[NUMBER_OF_DATA];
} inputData;

inputData inputBuffer;

int enterInput(inputData* inputBuffer);
int initParam(inputData* inputBuffer);
int makeTriangle(inputData* inputBuffer, int order, signed int intercept1, signed int intercept2, signed int intercept3);
int inspectTriangle(double* inputBuffer, signed int intercept1, signed int intercept2, signed int intercept3);

int EBPCalc(inputData* inputBuffer, int order);

int writeData(inputData* inputBuffer);
int writeError(inputData* inputBuffer);

#endif
/*
EBP -> x1, x2, target, output(y or u), the number of nuerons(n), weight[3*n](without bias), weight[4*n](bias)
delta[n+1], delatWeight[same as weight], 학습데이터(랜덤하게 1,0 섞어서 각 25개씩), etha=0.5
*/
