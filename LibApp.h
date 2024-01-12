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
#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H

#include"Publication.h"
#include"Menu.h"
#include "Streamable.h"
#include "Book.h"
#include "Lib.h"

namespace sdds {
	class LibApp {
		bool m_changed;
		Menu m_mainMenu;
		Menu m_exitMenu;


		char m_fileName[256];

		//This array will be populated with all the records of the 
		//publication data file when the LibApp is instantiated.
		Publication* m_PPA[SDDS_LIBRARY_CAPACITY];

		//Holds the number of Publications loaded into the PPA.
		int m_NOLP;

		//Holds the last library reference number read from the data file
		int m_LLRN;

		Menu m_publicationType;

		Publication* getPub(int libRef);

		bool confirm(const char* message);
		void load();
		void save();
		int search(int searchType);
		void returnPub();
		void newPublication();
		void removePublication();
		void checkOutPub();

	public:
		LibApp(const char* filename);
		~LibApp();

		void run();
	};
}
#endif // !SDDS_LIBAPP_H