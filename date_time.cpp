#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
#include<ctime>
#include<cmath>
#include<sstream>
#include<iomanip>
#include<regex>
using namespace std;
std::string format = "%d/%m/%Y";

std::time_t stringToTime(const std::string& dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    int day, month, year;
    char delim;
    ss >> day >> delim >> month >> delim >> year;
    if (ss.fail() || delim != '/' || month < 1 || month > 12 || day < 1 || day > 31) {
        return -1;
    }
    tm.tm_mday = day;
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;
    return std::mktime(&tm);
}

int dateDifferenceInDays(const std::string& date1Str, const std::string& date2Str) {
    std::time_t date1 = stringToTime(date1Str);
    std::time_t date2 = stringToTime(date2Str);
    if (date1 == -1 || date2 == -1) {
        return -1;
    }
    std::time_t difference = std::abs(date1 - date2);
    if(date1<date2){
        std::cout<<"Can't compute the difference\n";
        return -1;
    }
    int days = difference / (24 * 60 * 60);
    return days;
}