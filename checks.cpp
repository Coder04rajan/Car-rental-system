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

bool hasSpaces_or_empty(const std::string& str) {
    for (char c : str) {
        if (c == ' ') {
            return true;
        }
    }
    if(str.size()==0) return true;
    if(str.size()>=30) return true;
    return false;
}

bool isValidEmail(const std::string& email) {
    // Regular expression pattern for basic email validation
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    // Check if the email matches the pattern
    return std::regex_match(email, pattern);
}

bool isValidFloat(const std::string& str) {
    std::istringstream iss(str);
    float f;
    // Attempt to read a float from the stringstream
    iss >> std::noskipws >> f;
    // Check if the entire string was consumed and if there are no further characters left after parsing
    return !iss.fail() && iss.eof();
}

bool isValidInteger(const std::string& str) {
    std::istringstream iss(str);
    int n;
    // Attempt to read an integer from the stringstream
    iss >> n;
    // Check if the entire string was consumed and if there are no further characters left after parsing
    return !iss.fail() && iss.eof();
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

std::string getCurrentDateAsString() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    char buffer[80];
    std::string format = "%d/%m/%Y";
    std::strftime(buffer, 80, format.c_str(), localTime);
    return std::string(buffer);
}

bool isValidDate(const std::string& dateStr) {
    if(dateStr==getCurrentDateAsString()) return true;
    std::tm tm = {};
    std::istringstream ss(dateStr);
    int day, month, year;
    char delim;
    ss >> day >> delim >> month >> delim >> year;
    if (ss.fail() || delim != '/' || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
    tm.tm_mday = day;
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;
    std::time_t inputTime = std::mktime(&tm);
    auto currentTime = std::time(nullptr);
    int maxDaysInFeb = (isLeapYear(year)) ? 29 : 28;
    if (month == 2 && day > maxDaysInFeb) {
        return false;
    }
    if (inputTime == -1) {
        return false;
    }
    bool flag;
    flag=tm.tm_mday == day && tm.tm_mon == month - 1 && tm.tm_year == year - 1900;
    if(inputTime<currentTime && inputTime!=-1) std::cout<<"Date is lesser than the current date"<<endl;
    return (inputTime != -1 && inputTime >= currentTime && flag);
}