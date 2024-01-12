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
using namespace std;
#include"Streamable.h"

namespace sdds {

    istream& operator>>(istream& is, Streamable& str)
    {
        return str.read(is);
    }

    ostream& operator<<(ostream& os, const Streamable& str)
    {
        if (str)
        {
            str.write(os);
        }
        return os;
    }

}