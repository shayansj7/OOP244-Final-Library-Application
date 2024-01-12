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
#ifndef SDDS_PUBLICATION_H__
#define SDDS_PUBLICATION_H__
#include <ostream>
#include "Streamable.h"
#include "Lib.h"
#include "Date.h"

namespace sdds {

    class Publication : public Streamable {

        char* m_title;
        char m_shelfId[SDDS_SHELF_ID_LEN + 1];
        int m_membership;
        int m_libRef;
        Date m_date;

    public:
        Publication();
        Publication(const Publication& src);
        Publication& operator=(const Publication& src);

        ~Publication();


        void setToDefault();

        //-----------------Modifiers------------------
        virtual void set(int member_id);
        // Sets the membership attribute to either zero or a five-digit integer.

        void setRef(int value);
        // Sets the **libRef** attribute value

        void resetDate();
        // Sets the date to the current date of the system.


        //-----------------Queries------------------
        virtual char type()const;
        //Returns the character 'P' to identify this object as a "Publication object"

        bool onLoan()const;
        //Returns true is the publication is checkout (membership is non-zero)

        Date checkoutDate()const;
        //Returns the date attribute

        bool operator==(const char* title)const;
        //Returns true if the argument title appears anywhere in the title of the 
        //publication. Otherwise, it returns false; (use strstr() function in <cstring>)

        operator const char* ()const;
        //Returns the title attribute

        int getRef()const;
        //Returns the libRef attirbute. 


        bool conIO(std::ios& io)const;

        std::ostream& write(std::ostream& os) const;

        std::istream& read(std::istream& istr);

        operator bool() const;
    };

}

#endif // !SDDS_PUBLICATION_H__
