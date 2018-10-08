#include <iostream>
#include "status.h"

int main() {
    Status s(-1, "OpenError");

    std::cout << s.ToString() << std::endl;

    Status ioerr = Status::IoError("open", "TestStatus.cc");
    std::cout << ioerr.ToString() << std::endl;
}