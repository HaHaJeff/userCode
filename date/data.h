#ifndef __DATA_H 
#define __DATA_H

#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <map>


class CDate;

std::vector<std::string> Split(const std::string& data, const std::string& delims);

bool operator == (const CDate& lref, const CDate& rref);

unsigned int operator - (const CDate& lref, const CDate& rref);


// 0000 0000 0000(year) 0000(month) 00000(day) 000 0000 0000
class CDate {
public:
    explicit CDate() : date_(0), time_(0){
    }
    explicit CDate(const std::string& sDate) :date_(0), time_(0) {
        Parse(sDate);
    }

    unsigned int GetYear() const {
        unsigned int year = (date_>>20)&0x0FFF;
        return year;
    }

    unsigned int GetMonth() const {
        unsigned int month = (date_>>16)&0x0F;
        return month;
    }

    unsigned int GetDay() const {
        unsigned int day = (date_>>8)&0x1F;
        return day;
    }

    unsigned int GetHour() const {
        unsigned int hour = (time_>>24)&0x1F;
        return hour;
    }

    unsigned int GetMinute() const {
        unsigned int minute = (time_>>16)&0x3F;
        return minute;
    }

    unsigned int GetSecond() const {
        unsigned int second = (time_>>8)&0x3F;
        return second;
    }

    void SetYear(unsigned int year) {
        date_ |= year << 20;
    }

    void SetMonth(unsigned int month) {
        date_ |= month << 16;
    }
    
    void SetDay(unsigned int day) {
        date_ |= day << 8;
    }

    void SetHour(unsigned int hour) {
        time_ |= hour << 24;
    }

    void SetMinute(unsigned int minute) {
        time_ |= minute << 16;
    }

    void SetSecond(unsigned int second) {
        time_ |= second << 8;
    }

    void SetDate(unsigned int iDate) {
        date_ = iDate;
    }

    void SetTime(unsigned int iTime) {
        time_ = iTime;
    }

    void Parse(const std::string& sDate) {
        std::vector<std::string> vecStr = Split(sDate, " -:\n");
        int year = atoi(vecStr[0].c_str());
        int month = atoi(vecStr[1].c_str());
        int day = atoi(vecStr[2].c_str());
        int hour = atoi(vecStr[3].c_str());
        int minute = atoi(vecStr[4].c_str());
        int second = atoi(vecStr[5].c_str());
        SetYear(year);
        SetMonth(month);
        SetDay(day);
        SetHour(hour);
        SetMinute(minute);
        SetSecond(second);
    }

    std::string ToString()const {
        char time[20];
        snprintf(time, 20, "%04d-%02d-%02d %02d:%02d:%02d", GetYear(), GetMonth(), GetDay(), GetHour(), GetMinute(), GetSecond() );
        return time;  
    }

    unsigned int GetDays() const {
        int year  = GetYear();
        int month = GetMonth();
        int day   = GetDay();

        if (0 >= (int)(month -= 2)) {
            month += 12;
            year -= 1;
        }

        return (year/4 - year/100 + year/400 + 367*month/12 + day) + year*365 - 719499;
    }

    unsigned GetDate() const {
        return date_;
    }

    unsigned GetTime() const {
        return time_;
    }

private:
    // year:12(0xFFF00000) month:4(0x000F0000) day:5(0x00001F00)
    unsigned int date_;   //2018-05-12
    // hour:5(0x1F000000)  minute:6(0x003F0000)  second:6(0x00003F00)
    unsigned int time_;   //23:45:36
};
#endif
