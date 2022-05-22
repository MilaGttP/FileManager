
#include <iostream>
#include "Entering.h";
using namespace std;

int EnterNumber(const char* prompt)
{
	while (true)
	{
		int number;
		cout << "\n" << prompt << " : ";
		cin >> number;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "ќшибка ввода целого числа! \n";
		}
		else
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return number;
		}
	}
}

int EnterNumber(const char* prompt, int min, int max)
{
	while (true)
	{
		int value = EnterNumber(prompt);
		if (value >= min && value <= max)
			return value;
		cerr << "¬ведите значение от " << min << " до " << max << endl;
	}
}