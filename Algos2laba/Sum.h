#pragma once
#include <string>

struct List {
	double coef;
	int power;
	List* next;
};

List ReadFile(int);
List OperationOnPol(List*, List*, int, bool);
List MultPol(List*, List*);
void AddToFile(List*,char,const char*);
char FindVariable();