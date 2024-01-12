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
#include "Publication.h"
#include "Date.h"
#include "Lib.h"


namespace sdds {

    Publication::Publication()
    {
        setToDefault();
    }

    Publication::Publication(const Publication& src)
    {
        *this = src;
    }

    Publication& Publication::operator=(const Publication& src)
    {
        set(src.m_membership);
        setRef(src.m_libRef);
        strcpy(m_shelfId, src.m_shelfId);

        m_date = src.m_date;

        if (m_title)
        {
            delete[] m_title;
            m_title = nullptr;
        }

        if (src.m_title)
        {
            m_title = new char[strlen(src.m_title) + 1];
            strcpy(m_title, src.m_title);
        }
        else
        {
            m_title = nullptr;
        }

        return *this;
    }

    void Publication::setToDefault()
    {
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        resetDate();
    }

    void Publication::set(int member_id)
    {
        if (member_id > 9999 && member_id < 100000)
        {
            m_membership = member_id;
        }
        else
        {
            m_membership = 0;
        }
    }

    void Publication::setRef(int value)
    {
        m_libRef = value;
    }

    void Publication::resetDate()
    {
        m_date.getSetTotoday();
    }

    char Publication::type()const
    {
        return 'P';
    }

    bool Publication::onLoan()const
    {
        return m_membership != 0;
    }

    Date Publication::checkoutDate()const
    {
        return m_date;
    }

    bool Publication::operator==(const char* title)const
    {
        return strstr(m_title, title) != nullptr;
    }

    Publication::operator const char* ()const
    {
        return m_title;
    }

    int Publication::getRef()const
    {
        return m_libRef;
    }

    bool Publication::conIO(ios& io)const
    {
        return &io == &cin || &io == &cout;
    }

    ostream& Publication::write(ostream& os) const
    {
        char title[SDDS_TITLE_WIDTH + 1] = { 0 };
        strncpy(title, m_title, SDDS_TITLE_WIDTH);


        if (conIO(os))
        {
            os << "| " << m_shelfId << " | " << setw(30) << left << setfill('.') << title << " | ";

            if (m_membership != 0)
            {
                os << m_membership << " | ";
            }
            else
            {
                os << " " << "N/A  | ";
            }

            os << m_date << " |";
        }
        else
        {
            os << type();

            os << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t";

            os << m_membership;
            os << "\t" << m_date;
        }

        return os;
    }

    istream& Publication::read(istream& istr)
    {
        char tmpTitle[200];
        char tmpShelfId[SDDS_SHELF_ID_LEN + 1];
        int tmpMembership = 0;
        int tmpLibRef = -1;
        Date tmpDate;

        if (m_title)
        {
            delete[] m_title;
            m_title = nullptr;
        }

        setToDefault();

        if (conIO(istr))
        {
            cout << "Shelf No: ";
            istr.getline(tmpShelfId, SDDS_SHELF_ID_LEN + 1);

            if (strlen(tmpShelfId) != SDDS_SHELF_ID_LEN)
            {
                istr.setstate(ios::failbit);
            }

            cout << "Title: ";
            istr.getline(tmpTitle, 200);

            cout << "Date: ";
            istr >> tmpDate;
        }
        else
        {
            istr >> tmpLibRef;
            istr.ignore();

            istr.getline(tmpShelfId, SDDS_SHELF_ID_LEN + 1, '\t');

            istr.getline(tmpTitle, 200, '\t');

            istr >> tmpMembership;
            istr.ignore();

            istr >> tmpDate;
        }

        if (!tmpDate)
        {
            istr.setstate(ios::failbit);
        }

        if (istr)
        {
            strcpy(m_shelfId, tmpShelfId);

            m_title = new char[strlen(tmpTitle) + 1];
            strcpy(m_title, tmpTitle);

            m_membership = tmpMembership;
            m_date = tmpDate;
            m_libRef = tmpLibRef;
        }

        return istr;
    }

    Publication::operator bool() const
    {
        return m_title != nullptr || m_shelfId[0] != '\0';
    }

    Publication::~Publication()
    {
        delete[] m_title;
    }
}