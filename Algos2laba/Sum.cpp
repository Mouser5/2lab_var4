
#include "Sum.h"
#include <fstream>﻿
#include <iostream>
#include <string>
using namespace std;

char FindVariable() {
	char variable = 0, power = 0;
	int count = 0;
	ifstream inFile("input.txt", ios::in);
	inFile >> variable;
	do {
		inFile.seekg(-1, ios::cur);
		inFile >> variable;
		count++;
		inFile >> power;
		if ((power == ';') || (power == ','))
			if (((variable >= '9') || (variable <= '0')) && (variable != ';') && (variable != '-'))
				power = '+';
	} while ((power != '^') && (power != '+') && ((power != '-') || (variable == ';')) && (power != ','));
	inFile.seekg(-count, ios::cur);
	if (power == ',')
	{
		variable = '.';
	}
	return(variable);
}

List* FillPoly(List* list, double coef, int power) {
	List* q = list;
	List* temp;
	while (q != NULL)
	{
		q = q->next;
	}
	if (q == NULL)
		q = (List*)malloc(sizeof(List));
	q->coef = coef;
	q->power = power;
	q->next = list;
	list = q;
	return (list);
}



List ReadFile(int Numb) {
	List* poly = nullptr;
	char variable = 0, tempchar = 0, sign = 0;
	int power;
	double coef;
	ifstream inFile("input.txt", ios::in);
	if (Numb == 2)
		do
			inFile >> tempchar;
	while (tempchar != ';');
	inFile >> tempchar;
	while ((tempchar != ';') && (tempchar != ','))
	{
		if ((tempchar <= '9') && (tempchar >= '1'))
		{
			inFile.seekg(-1, ios::cur);
			inFile >> coef;
		}
		else
		{
			sign = tempchar;
			inFile >> tempchar;
			if ((tempchar <= '9') && (tempchar >= '1'))
			{
				inFile.seekg(-2, ios::cur);
				inFile >> coef;
			}
			else
			{
				if (sign == '-')
				{
					coef = -1;
					inFile.seekg(-1, ios::cur);
				}
				else
				{
					if (sign == '+')
					{
						coef = 1;
						inFile.seekg(-1, ios::cur);
					}
					else
					{
						coef = 1;
						inFile.seekg(-2, ios::cur);
					}
				}

			}
		}
		variable = 't';
		inFile >> variable;
		inFile.seekg(-1, ios::cur);
		inFile >> variable;
		if ((variable != ';') && (variable != ','))
		{
			inFile >> tempchar;
			if (tempchar != '^')
			{
				inFile.seekg(-1, ios::cur);
				power = 1;
			}
			else
			{
				inFile >> power;
			}
			inFile >> tempchar;
		}
		else
		{
			tempchar = variable;
			power = 0;
		}
		poly = FillPoly(poly, coef, power);
	}
	return(*poly);
}

List OperationOnPol(List* poly1, List* poly2, int sign, bool FirstMinusSecond) {
	List* Res = nullptr;
	if (FirstMinusSecond != true)
	{
		List* temp = poly1;
		poly1 = poly2;
		poly2 = temp;
	}
	while (poly1 != NULL && poly2 != NULL) {
		if (poly1->power > poly2->power)
		{
			Res = FillPoly(Res, poly1->coef, poly1->power);
			poly1 = poly1->next;
		}
		else
		{
			if (poly1->power < poly2->power)
			{
				Res = FillPoly(Res, (sign)*poly2->coef, poly2->power);
				poly2 = poly2->next;
			}
			else
			{
				Res = FillPoly(Res, poly1->coef + poly2->coef * (sign), poly1->power);
				poly1 = poly1->next;
				poly2 = poly2->next;
			}
		}
	}
	while (poly1 != NULL)
	{
		Res = FillPoly(Res, poly1->coef, poly1->power);
		poly1 = poly1->next;
	}
	while (poly2 != NULL)
	{
		Res = FillPoly(Res, (-1) * poly2->coef, poly2->power);
		poly2 = poly2->next;
	}
	return(*Res);
}

List* Add(List* poly, int pow, double coef) {
	List* temp = poly;
	while (temp != NULL)
	{
		if (temp->power == pow) {
			temp->coef += coef;
			return poly;
		}

		else
			temp = temp->next;
	}
	if (temp == NULL)
		temp = (List*)malloc(sizeof(List));
	temp->coef = coef;
	temp->power = pow;
	temp->next = poly;
	poly = temp;
	return poly;
}

List MultPol(List* poly1, List* poly2) {
	List* Res = nullptr;
	List* Temp = poly2;
	for (; poly1 != NULL; poly1 = poly1->next)
	{
		for (; poly2 != NULL; poly2 = poly2->next) {
			Res = Add(Res, poly1->power + poly2->power, poly1->coef * poly2->coef);
		}
		poly2 = Temp;
	}
	return (*Res);
}


void AddToFile(List* poly, char variable, const char* operation) {
	ofstream outFile("output.txt", ios_base::app);
	int count = 0;
	if (!outFile.is_open())
	{
		cout << "File didn't open\n";
	}
	else
	{
		outFile << operation << endl;
		for (; poly != NULL; poly = poly->next) {
			if (poly->coef != 0)
			{
				if (poly->coef > 0)
				{
					if (poly->coef == 1)
					{
						if (count != 0)
							outFile << "+";
					}
					else
					{
						if (count != 0)
							outFile << "+";
						outFile << poly->coef;
					}
				}
				else
				{
					if (abs(poly->coef) == 1)
					{
						outFile << "-";
					}
					else
						outFile << poly->coef;
				}
				if (poly->power != 0) {
					outFile << variable;
				}
				else
					if (abs(poly->coef) == 1)
						outFile << 1;

				if (poly->power > 1)
				{
					outFile << "^" << poly->power;
				}
			}
			count++;
		}
		outFile << endl;
	}
}