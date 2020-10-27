
#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#define ITERATIVE 1
#define DELTA 2

#define AND 3
#define OR 4

#define TRY_COUNT 100
#define LEARNING_GAIN 0.5	// LEARNING_GAIN : (0~1)
#define ETHA 0.2	// Delta rule learning Gain

#define MAXIMUM_ERR 0.0000001
typedef struct  TrainingData
{
	double x1;
	double x2;
	double w1;
	double w2;
	double theta;
	double error;	// error는 Delta Rule에서만 사용
	int logic;	// AND, OR Logic selector
	int target;
	int y;
	int mode;
} TrainingData;

TrainingData TrainingBuffer;

int solve_problem(TrainingData* Buffer, TrainingData* AND_Buffer, TrainingData* OR_Buffer);
int calc(TrainingData* Buffer);
int getOtherX(TrainingData* Buffer);
int runTraining(TrainingData* Buffer);

int getWeight(TrainingData* Buffer);
void initTraining(TrainingData* Buffer, double x1, double x2, int target);
void moreWeight(TrainingData* Buffer, int weightNum);
void lessWeight(TrainingData* Buffer, int weightNum);

int lineData(TrainingData* Buffer);
void init_dot_lineData(void);
int dot_lineData(TrainingData* Buffer, double* w1_store, double* w2_store);
#endif