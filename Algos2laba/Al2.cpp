#include <iostream>
#include "Sum.h"
#include <list>
#include <fstream>﻿
#include <string>
using namespace std;

int Program() {
	List Poly1{}, Poly2{}, ResultPoly{};
	char input;
	char variable = FindVariable();
	if (variable == '.') {
		cout << "There are no polynoms";
		return(0);
	}
		
	Poly1=ReadFile(1);
	Poly2=ReadFile(2);
	cout << "Do you want to see polynoms? [Y/n]\n";
	cin >> input;
	if (tolower(input) == 'y') {
		AddToFile(&Poly1, variable, "First polynom");
		AddToFile(&Poly2, variable, "Second polynoms");
	}
	cout << "Do you want to add polynoms? [Y/n]\n";
	cin >> input;
	if (tolower(input) == 'y') {
		ResultPoly = OperationOnPol(&Poly1, &Poly2, 1, true);
		AddToFile(&ResultPoly, variable, "Sum of polynoms");
	}

	cout << "Do you want to subtract polynoms? [Y/n]\n";
	cin >> input;
	if (tolower(input) == 'y') {
		cout << "Do you want to subtract from first polynom? [Y/n]\n";
		cin >> input;
		if (tolower(input) == 'y') {
			ResultPoly = OperationOnPol(&Poly1, &Poly2, -1, true);
			AddToFile(&ResultPoly, variable, "Subtraction of polynoms");
		}
			
		else {
			ResultPoly = OperationOnPol(&Poly1, &Poly2, -1, false);
			AddToFile(&ResultPoly, variable, "Subtraction of polynoms");
		}
			
	}
	cout << "Do you want to multiply polynoms? [Y/n]\n";
	cin >> input;
	if (tolower(input) == 'y') {
		ResultPoly = MultPol(&Poly1, &Poly2);
		AddToFile(&ResultPoly, variable, "Multiplication of polynoms");
	}
		
}

int main()
{
	Program();
	return (0);
}

