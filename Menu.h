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
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include<iostream>

namespace sdds {

#define MAX_MENU_ITEMS 20
	class MenuItem {
		char* m_content;

		friend class Menu;

		MenuItem();
		MenuItem(const char* title);
		MenuItem(const MenuItem& src) = delete;
		~MenuItem();

		operator bool() const;
		operator const char* () const;

		std::ostream& display(std::ostream& os = std::cout);
	};

	class Menu {
		MenuItem m_title;
		MenuItem* m_arr_title[MAX_MENU_ITEMS];
		int m_noOfPointer = 0;

	public:
		Menu();
		Menu(const char* title);
		Menu(const Menu& src) = delete;
		~Menu();

		std::ostream& displayMenuTitle(std::ostream& os);
		std::ostream& displayMenu(std::ostream& os = std::cout);

		int run();

		int operator~();
		Menu& operator<<(const char* menuitemConent);

		operator int() const;
		operator unsigned int() const;
		operator bool() const;

		const char* operator[](int index) const;
	};

	std::ostream& operator<<(std::ostream& os, Menu& menu);
}

#endif // !SDDS_MENU_H__