#include <iostream>
#include "timestamp.h"

int main()
{
    TimeStamp t(TimeStamp::Now());
    std::cout << t.ToString() << std::endl;
    std::cout << t.ToFormattedString() << std::endl;
}