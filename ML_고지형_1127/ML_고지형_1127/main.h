#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _USE_MATH_DEFINES 
#include <math.h>

#define MAX_NUERON 15
#define MIN_NUERON 1
#define MAX_LAYER 3
#define MIN_LAYER 1

#define MAX_EPOCH 1000
#define ALLOW_ERROR 0.01
#define ALLOW_TOTAL_ERROR NUMBER_OF_DATA * ALLOW_ERROR
#define ALLOW_ORDER		2
#define LEARNING_GAIN 0.5	// LEARNING_GAIN(ETHA) : (range: 0~1)

#define THRESHOLD 0.5
#define TARGET_HIGH	0.9
#define TARGET_LOW	0.1

#define X1_INTERCEPT 3 // positive: over X1 line. negative: below X1 line.
#define X2_INTERCEPT 3 // positive: over X1 line. negative: below X1 line.
#define HORIZON_INTERCEPT 0	// positive: over X1 line. negative: below X1 line.

#define NUMBER_OF_BIAS 1
#define NUMBER_OF_INPUT 15
#define NUMBER_OF_OUTPUT 3
#define NUMBER_OF_DATA 50
#define NUMBER_OF_GRID_DATA 100

#define INSPECT_TIME	10	// inspect every 100 epoch
typedef struct weight_t
{
	double weight[NUMBER_OF_OUTPUT][MAX_LAYER][MAX_NUERON + NUMBER_OF_OUTPUT][NUMBER_OF_INPUT];
	double biasWeight[NUMBER_OF_DATA];
} weight_t;

typedef struct inputData
{
	int time;
	int inputNum;
	int outputNum;
	int bias;
	int layer;
	int nueron[MAX_LAYER];
	int weightNumber[MAX_LAYER];
	double x[NUMBER_OF_INPUT][NUMBER_OF_DATA];
	double target[NUMBER_OF_DATA];
	double y[NUMBER_OF_OUTPUT][NUMBER_OF_DATA];
	double error[NUMBER_OF_OUTPUT][NUMBER_OF_DATA];
	double errorSum[NUMBER_OF_OUTPUT][MAX_EPOCH];
	double output[NUMBER_OF_OUTPUT][MAX_LAYER][MAX_NUERON + NUMBER_OF_OUTPUT];
	double weight[NUMBER_OF_OUTPUT][MAX_LAYER][MAX_NUERON + NUMBER_OF_OUTPUT][NUMBER_OF_INPUT];
	double biasWeight[NUMBER_OF_DATA];
} inputData;

typedef struct gridData
{
	double x[NUMBER_OF_INPUT][NUMBER_OF_GRID_DATA];
	int grid[NUMBER_OF_GRID_DATA * NUMBER_OF_GRID_DATA];
} gridData;

inputData inputBuffer;
inputData inspectBuffer;
weight_t weightBuffer[MAX_EPOCH / INSPECT_TIME];
gridData gridBuffer;

int enterInput(inputData* inputBuffer);
int loadData(inputData* inputBuffer, char* fileName);
int initParam(inputData* inputBuffer);
int inspectParam(inputData* inputBuffer, inputData* inspectBuffer);
int copyWeight(inputData* inputBuffer, weight_t* weightBuffer);
int pasteWeight(inputData* inspectBuffer, weight_t* weightBuffer);

int makeBoundary(inputData* inputBuffer, int order, int intercept1, int intercept2, int intercept3); 
//int inspectBoundary(double* inputBuffer, int intercept1, int intercept2, int intercept3);
int gridBoundary(gridData* gridBuffer, int grid_x1, int grid_x2, int intercept1, int intercept2, int intercept3);

int EBPCalc(inputData* inputBuffer, int order);
//int inspectResult(double* x_inspect);

int writeData(inputData* inputBuffer);
int writeError(inputData* inputBuffer);
int makeGrid2D(gridData* gridBuffer);
int initEvaluation(inputData* inputBuffer);
int writeEvaluation(inputData* inputBuffer, int epoch);

#endif

