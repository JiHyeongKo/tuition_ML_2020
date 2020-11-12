#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#define TRY_COUNT 100
#define LEARNING_GAIN 0.5	// LEARNING_GAIN : (0~1)
typedef struct  TrainingData
{
	double x1;
	double x2;
	double w1;
	double w2;
	double theta;
	int target;
	int y;
} TrainingData;

TrainingData TrainingBuffer;

int AND_problem(TrainingData* Buffer);
int AND_calc(TrainingData* Buffer);
int getOtherX(TrainingData* Buffer);
int runTraining(TrainingData* Buffer);

int getWeight(TrainingData* Buffer);
void initTraining(TrainingData* Buffer, double x1, double x2, int target);
void moreWeight(TrainingData* Buffer, int weightNum);
void lessWeight(TrainingData* Buffer, int weightNum);

int lineData(TrainingData* Buffer);
#endif