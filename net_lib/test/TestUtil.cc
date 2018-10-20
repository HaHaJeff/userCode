#include "util.h"
#include <iostream>

void TestUtil()
{
    time_t t;
    t = time(&t);
    std::cout << "Util::Atoi " << Util::Atoi("1234567890") << std::endl;
    std::cout << "ReadableTime" << Util::ReadableTime(t) << std::endl;
}

int main()
{
    TestUtil();
}
