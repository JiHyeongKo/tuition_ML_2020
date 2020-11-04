#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _USE_MATH_DEFINES 
#include <math.h>

#define MAX_NUERON 15
#define MIN_NUERON 3
#define MAX_LAYER 5
#define MIN_LAYER 1

#define MAX_EPOCH 10
#define ALLOW_ERROR 0.01
#define ALLOW_TOTAL_ERROR NUMBER_OF_DATA * ALLOW_ERROR
#define LEARNING_GAIN 0.5	// LEARNING_GAIN(ETHA) : (0~1)
#define THRESHOLD 0.5

#define X1_INTERCEPT 3 // positive: over X1 line. negative: below X1 line.
#define X2_INTERCEPT 5 // positive: over X1 line. negative: below X1 line.
#define HORIZON_INTERCEPT -2	// positive: below X1 line. negative: over X1 line.

#define NUMBER_OF_BIAS 1
#define NUMBER_OF_INPUT 2
#define NUMBER_OF_OUTPUT 1
#define NUMBER_OF_LAYER 2
#define NUMBER_OF_DATA 10

typedef struct inputData
{
	int bias;
	int layer;
	int nueron[MAX_LAYER];
	int weightNumber[MAX_LAYER];
	double x[NUMBER_OF_INPUT][NUMBER_OF_DATA];
	double target[NUMBER_OF_DATA];
	double y[NUMBER_OF_OUTPUT][NUMBER_OF_DATA];
	double error[NUMBER_OF_OUTPUT][NUMBER_OF_DATA];
	double errorSum[NUMBER_OF_OUTPUT][MAX_EPOCH];
	double output[MAX_LAYER][MAX_NUERON + NUMBER_OF_OUTPUT];
	double weight[MAX_LAYER][MAX_NUERON + NUMBER_OF_OUTPUT][NUMBER_OF_BIAS + NUMBER_OF_INPUT];
	double biasWeight[NUMBER_OF_DATA];
} inputData;

inputData inputBuffer;

int enterInput(inputData* inputBuffer);
int initParam(inputData* inputBuffer);
int makeTriangle(inputData* inputBuffer, int order, int intercept1,int intercept2, int intercept3);
int inspectTriangle(double* inputBuffer, int intercept1, int intercept2, int intercept3);

int EBPCalc(inputData* inputBuffer, int order);
int inspectResult(double* x_inspect);
int tryInspect(inputData* inputBuffer);

int writeData(inputData* inputBuffer);
int writeError(inputData* inputBuffer);

#endif

