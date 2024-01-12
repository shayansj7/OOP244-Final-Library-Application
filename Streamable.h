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
#ifndef SDDS_STREAMABLE_H__
#define SDDS_STREAMABLE_H__
#include <ostream>

namespace sdds {

    class Streamable {
    public:
        virtual std::ostream& write(std::ostream& os)const = 0;

        virtual std::istream& read(std::istream& is) = 0;

        virtual bool conIO(std::ios& io)const = 0;

        virtual operator bool() const = 0;

        virtual ~Streamable() {};
    };

    std::istream& operator>>(std::istream& is, Streamable& str);
    std::ostream& operator<<(std::ostream& os, const Streamable& str);

}

#endif // !SDDS_STREAMABLE_H__
