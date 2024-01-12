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
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
#include"Book.h"
#include "Lib.h"

namespace sdds {

    Book::Book() : Publication()
    {
        m_authorName = nullptr;
    }

    Book::~Book()
    {
        delete[] m_authorName;
    }

    Book::Book(const Book& src)
    {
        *this = src;
    }

    Book& Book::operator=(const Book& src)
    {
        Publication::operator=(src);

        if (m_authorName)
        {
            delete[] m_authorName;
            m_authorName = nullptr;
        }

        if (src.m_authorName)
        {
            m_authorName = new char[strlen(src.m_authorName) + 1];
            strcpy(m_authorName, src.m_authorName);
        }
        else
        {
            m_authorName = nullptr;
        }
        return *this;
    }

    char Book::type()const
    {
        return 'B';
    }

    ostream& Book::write(ostream& os) const
    {
        Publication::write(os);

        if (conIO(os))
        {
            char tmpAuthorName[SDDS_AUTHOR_WIDTH + 1] = { 0 };
            strncpy(tmpAuthorName, m_authorName, SDDS_AUTHOR_WIDTH);
            os << " ";
            os << setw(SDDS_AUTHOR_WIDTH) << left << setfill(' ') << tmpAuthorName << " |";
        }
        else
        {
            os << "\t" << m_authorName;
        }

        return os;
    }

    istream& Book::read(istream& istr)
    {
        char tmpAuthorName[200] = { 0 };
        Publication::read(istr);

        if (m_authorName)
        {
            delete[] m_authorName;
            m_authorName = nullptr;
        }

        if (conIO(istr))
        {
            istr.ignore();
            cout << "Author: ";
        }
        else
        {
            istr.ignore(1000, '\t');
        }

        istr.get(tmpAuthorName, 200);

        if (istr)
        {
            m_authorName = new char[strlen(tmpAuthorName) + 1];
            strcpy(m_authorName, tmpAuthorName);
        }

        return istr;
    }

    void Book::set(int member_id)
    {
        Publication::set(member_id);
        Publication::resetDate();
    }

    Book::operator bool() const
    {
        return m_authorName && m_authorName[0] != '\0' && Publication::operator bool();
    }
}