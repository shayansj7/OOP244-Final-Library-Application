/*/////////////////////////////////////////////////////////////////////////
                        Milestone 5
Full Name  :Shayan Shimura
Student ID#:120733225
Email      :sshimura@myseneca.ca
Section    :NRA

Authenticity Declaration:Shayan Shimura
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/
#include<iostream>
#include "Utils.h"
using namespace std;

namespace sdds {

	int getInput(int min, int max)
	{
		int result;
		bool endLoop = false;

		do {
			cin >> result;

			if (min < result && result <= max)

			{
				cin.clear();
				cin.ignore(1000, '\n');
				endLoop = true;
			}
			else if (cin && result == 0)
			{
				endLoop = true;
			}
			else
			{
				if (min == 10000)
				{
					cout << "Invalid membership number, try again: ";
				}
				else
				{
					cout << "Invalid Selection, try again: ";
				}
				cin.clear();
				cin.ignore(1000, '\n');
			}
		} while (!endLoop);

		return result;
	}
}