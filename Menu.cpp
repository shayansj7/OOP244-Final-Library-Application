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
#include <iomanip>
#include <iostream>
#include<cstring>
using namespace std;
#include "Menu.h"
#include "Utils.h"

namespace sdds {
	//-----------------MenuItem Module-----------------------------
	MenuItem::MenuItem()
	{
		m_content = nullptr;
	}

	MenuItem::MenuItem(const char* title)
	{
		if (title)
		{
			m_content = new char[strlen(title) + 1];
			strcpy(m_content, title);
		}
		else
		{
			m_content = nullptr;
		}
	}

	MenuItem::~MenuItem()
	{
		delete[] m_content;

	}

	MenuItem::operator bool() const
	{
		bool result = true;

		if (!m_content || !(m_content[0]))
		{
			result = false;
		}
		return result;
	}

	MenuItem::operator const char* () const
	{
		return m_content;
	}

	std::ostream& MenuItem::display(std::ostream& os)
	{
		if (*this)
		{
			os << m_content;
		}
		return os;
	}

	//-------------Menu Module-------------------
	Menu::Menu()
	{
		m_noOfPointer = 0;
	}

	Menu::Menu(const char* title) : m_title(title) {}

	Menu::~Menu()
	{
		for (int i = 0; i < m_noOfPointer; i++)
		{
			delete m_arr_title[i];
		}

	}

	std::ostream& Menu::displayMenuTitle(std::ostream& os)
	{
		if (m_title || m_noOfPointer != 0)
		{
			m_title.display();
		}
		return os;
	}

	std::ostream& Menu::displayMenu(std::ostream& os)
	{
		if (m_title)
		{
			m_title.display();
			os << endl;
		}

		int i;
		for (i = 0; i < m_noOfPointer; i++)
		{
			os.width(2);
			os.setf(ios::right);
			os.fill(' ');

			os << i + 1 << "- ";
			os.unsetf(ios::right);
			m_arr_title[i]->display(os);
			os << endl;
		}
		os << " 0- Exit" << endl;
		os << "> ";

		return os;
	}

	int Menu::run()
	{
		int result;
		displayMenu();
		result = getInput(0, m_noOfPointer);
		return result;
	}

	int Menu::operator~()
	{
		return run();
	}

	Menu& Menu::operator<<(const char* menuitemConent)
	{
		if (m_noOfPointer < MAX_MENU_ITEMS)
		{
			MenuItem* mItem = new MenuItem(menuitemConent);
			m_arr_title[m_noOfPointer] = mItem;
			m_noOfPointer++;
		}
		return *this;
	}

	Menu::operator int() const
	{
		return m_noOfPointer;
	}

	Menu::operator unsigned int() const
	{
		return m_noOfPointer;
	}

	Menu::operator bool() const
	{
		return m_noOfPointer > 0;
	}

	ostream& operator<<(ostream& os, Menu& menu)
	{
		return menu.displayMenuTitle(os);
	}

	const char* Menu::operator[](int index) const
	{
		if (index > m_noOfPointer)
		{
			return m_arr_title[index %= m_noOfPointer]->m_content;
		}
		else
		{
			return m_arr_title[index]->m_content;
		}
	}
}