//
// Created by rui on 01/12/21.
//

#ifndef AIRLINE_DATE_H
#define AIRLINE_DATE_H
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;
class Date {
private:
    int day;
    int month;
    int year;
public:
    Date();
    Date(int day, int month, int year);

    explicit Date(const string& date);

    int get_day() const;

    int get_month() const;

    int get_year() const;

    void set_day(int day);

    void set_month(int month);

    void set_year(int year);

    bool operator <(Date d2) const;
    }
};
#endif //AIRLINE_DATE_H
