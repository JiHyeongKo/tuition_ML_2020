#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#define FIRST 1
#define SECOND 2
#define SUCCESS 10
#define FAILURE -10
#define SPACE "в╦"
#define DOT "бс"

typedef struct Iterative
{
	double X1;
	double X2;
	double W1;
	double W2;
	double THETA;
	int Y;
} Iterative;

typedef struct Coordinator
{
	double X1[21];
	double X2[21];
	int Y[21];
} Coordinator;

Coordinator coorBuffer;
Iterative dataBuffer;

int init_manual(Iterative* Data);
int input_data(Iterative* Data);
int output_data(Iterative* Data);
double multiple(Iterative* Data, int MODE);
double sigma(double S1, double S2);
int compare(Iterative* Data);
int makeGraphic(void);
int classification(Coordinator* buffer);
int line_data(double m, double n);

#endif