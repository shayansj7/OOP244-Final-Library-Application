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
#ifndef SDDS_BOOK_H__
#define SDDS_BOOK_H__
#include "Publication.h"

namespace sdds {

    class Book :public Publication {
        char* m_authorName;

    public:
        Book();
        ~Book();

        Book(const Book& src);
        Book& operator=(const Book& src);

        char type()const;

        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& istr);

        void set(int member_id);

        operator bool() const;

    };
}


#endif // !SDDS_BOOK_H__
