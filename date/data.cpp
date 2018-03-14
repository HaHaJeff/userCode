#include "data.h"

std::vector<std::string> Split(const std::string& data, const std::string& delims) {
    std::vector<std::string> ret;
    char pData[80];
    strncpy(pData, data.c_str(), data.size());
    char* result = strtok(pData, delims.c_str());
    while (result != NULL) {
        ret.push_back(result);
        result = strtok(NULL, delims.c_str());
    }
    return ret;
}

bool operator == (const CDate& lref, const CDate& rref) {
    return lref.GetDate() ==  rref.GetDate();
}

//Return days
unsigned int operator - (const CDate& lref, const CDate& rref) {
    unsigned days = lref.GetDays() - rref.GetDays();
    return days;
}

