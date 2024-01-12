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
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include <fstream>
#include <iomanip>
using namespace std;
#include "LibApp.h"
#include "PublicationSelector.h"
#include "Utils.h"
#include "Lib.h"

namespace sdds {

	Publication* LibApp::getPub(int libRef)
	{
		Publication* result = nullptr;

		for (int i = 0; i < m_NOLP; i++)
		{
			if (m_PPA[i]->getRef() == libRef)
			{
				result = m_PPA[i];
			}
		}

		return result;
	}

	bool LibApp::confirm(const char* message)
	{
		bool result = false;

		Menu menu(message);

		menu << "Yes";

		if (menu.run() == 1)
		{
			result = true;
		}
		return result;
	}

	void LibApp::load()
	{
		cout << "Loading Data" << endl;
		ifstream readFile(m_fileName);

		char typeOfPub;

		for (int i = 0; readFile && i < SDDS_LIBRARY_CAPACITY; i++)
		{
			readFile >> typeOfPub;

			readFile.ignore();

			if (readFile)
			{
				if (typeOfPub == 'P')
				{
					m_PPA[i] = new Publication;
				}
				else if (typeOfPub == 'B')
				{
					m_PPA[i] = new Book;
				}

				if (m_PPA[i])
				{
					readFile >> *m_PPA[i];
					m_NOLP++;
					m_LLRN = m_PPA[i]->getRef();
				}
			}
		}
	}

	void LibApp::save()
	{
		cout << "Saving Data" << endl;

		ofstream overwriteFile(m_fileName);

		for (int i = 0; i < m_NOLP; i++)
		{
			if (m_PPA[i]->getRef() != 0)
			{
				overwriteFile << *m_PPA[i] << endl;
			}
		}

		overwriteFile.close();
	}

	int LibApp::search(int searchType)
	{
		int userSelection;
		char title[256 + 1];
		char pubType;
		PublicationSelector ps("Select one of the following found matches:");
		int libRef = 0;

		userSelection = m_publicationType.run();

		if (userSelection == 1)
		{
			pubType = 'B';
		}
		else if(userSelection == 2)
		{
			pubType = 'P';
		}

		cout << "Publication Title: ";
		cin.getline(title, 256);

		if (searchType == 1)
		{
			for (int i = 0; i < m_NOLP; i++)
			{
				//All
				if (m_PPA[i]->operator==(title) && m_PPA[i]->type() == pubType && m_PPA[i]->getRef() != 0)
				{
					ps << m_PPA[i];
				}
			}
		}
		else if (searchType == 2)
		{
			for (int i = 0; i < m_NOLP; i++)
			{
				//Loan
				if (m_PPA[i]->operator==(title) && m_PPA[i]->onLoan() && m_PPA[i]->type() == pubType && m_PPA[i]->getRef() != 0)
				{
					ps << m_PPA[i];
				}
			}
		}
		else if (searchType == 3)
		{
			for (int i = 0; i < m_NOLP; i++)
			{
				//Not loan
				if (m_PPA[i]->operator==(title) && !m_PPA[i]->onLoan() && m_PPA[i]->type() == pubType && m_PPA[i]->getRef() != 0)
				{
					ps << m_PPA[i];
				}
			}
		}

		if (ps)
		{
			ps.sort();
			libRef = ps.run();

			if (libRef > 0)
			{
				cout << *getPub(libRef) << endl;
			}
			else
			{
				cout << "Aborted!" << endl;
			}

		}
		else
		{
			cout << "No matches found!" << endl;
		}

		return libRef;
	}

	void LibApp::returnPub()
	{
		bool aborted = false;
		cout << "Return publication to the library" << endl;
		cout << "Choose the type of publication:" << endl;

		int libRef = search(2);

		if (libRef == 0)
		{
			aborted = true;
		}

		if (!aborted)
		{


			if (confirm("Return Publication?"))
			{
				int exceedDays = (Date() - getPub(libRef)->checkoutDate()) - SDDS_MAX_LOAN_DAYS;

				if (exceedDays > 0)
				{
					double penalty = exceedDays * 0.5;

					cout << fixed << setprecision(2);
					cout << "Please pay $" << penalty << " penalty for being " << exceedDays << " days late!" << endl;
				}

				getPub(libRef)->set(0);
				m_changed = true;
			}
			cout << "Publication returned" << endl;
		}
		cout << endl;
	}

	void LibApp::newPublication()
	{
		bool aborted = false;

		if (m_NOLP != SDDS_LIBRARY_CAPACITY)
		{
			int userSelection;

			cout << "Adding new publication to the library" << endl;
			cout << "Choose the type of publication:" << endl;

			userSelection = m_publicationType.run();

			Publication* tmpPub = nullptr;

			if (userSelection == 0)
			{
				cout << "Aborted!" << endl;
				aborted = true;
			}
			else if (userSelection == 1)
			{
				tmpPub = new Book;
				cin >> *tmpPub;
			}
			else if (userSelection == 2)
			{
				tmpPub = new Publication;
				cin >> *tmpPub;
			}

			if (cin)
			{
				if (!aborted && confirm("Add this publication to the library?"))
				{
					if (*tmpPub)
					{
						m_LLRN++;
						//Store reference number to the temporary object
						tmpPub->setRef(m_LLRN);

						//Store temporary object to the last index of the m_PPA
						m_PPA[m_NOLP] = tmpPub;
						m_NOLP++;

						m_changed = true;
						cout << "Publication added" << endl;

					}
					else
					{
						cout << "Failed to add publication!" << endl;
						delete tmpPub;
					}
				}
			}
			else
			{
				cin.ignore(1000, '\n');
				cin.clear();
				cout << "Aborted!" << endl;
				exit(0);
			}
		}
		else
		{
			cout << "Library is at its maximum capacity!" << endl;
		}

		cout << endl;
	}

	void LibApp::removePublication()
	{
		cout << "Removing publication from the library" << endl;
		cout << "Choose the type of publication:" << endl;

		int libRef = search(1);

		if (libRef)
		{
			if (confirm("Remove this publication from the library?"))
			{
				getPub(libRef)->setRef(0);
				m_changed = true;
				cout << "Publication removed" << endl;
			}
		}
		cout << endl;
	}

	void LibApp::checkOutPub()
	{
		cout << "Checkout publication from the library" << endl;
		cout << "Choose the type of publication:" << endl;

		int libRef = search(3);

		if (libRef > 0)
		{
			if (confirm("Check out publication?"))
			{
				
				cout << "Enter Membership number: ";
				int memberShip = getInput(10000, 99999);

				getPub(libRef)->set(memberShip);
				
				m_changed = true;
				cout << "Publication checked out" << endl;
			}
		}

		cout << endl;
	}

	LibApp::LibApp(const char* filename) : m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?")
	{
		m_changed = false;
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";

		if (filename)
		{
			strcpy(m_fileName, filename);
		}

		m_publicationType << "Book" << "Publication";

		m_NOLP = 0;

		load();
	}

	LibApp::~LibApp()
	{
		for (int i = 0; i < m_NOLP; i++)
		{
			delete m_PPA[i];
		}
	}

	void LibApp::run()
	{
		int userInput;

		do {
			userInput = m_mainMenu.run();

			switch (userInput)
			{
			case 0:
				if (m_changed)
				{
					int exit;
					exit = m_exitMenu.run();

					switch (exit)
					{
					case 0:
						if (confirm("This will discard all the changes are you sure?"))
						{
							m_changed = false;
						}
						break;
					case 1:
						save();
						break;
					case 2:
						userInput = 1;
						break;
					}
				}
				cout << endl;
				break;
			case 1:
				newPublication();
				break;
			case 2:
				removePublication();
				break;
			case 3:
				checkOutPub();
				break;
			case 4:
				returnPub();
				break;
			}

		} while (userInput != 0);

		cout << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
	}

}
