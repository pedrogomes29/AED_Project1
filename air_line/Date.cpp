//
// Created by rui on 01/12/21.
//

#include "Date.h"

Date::Date(int day, int month, int year){
    this->day = day;
    this->month = month;
    this->year = year;
}
int Date::get_day() const {
    return day;
}
int Date::get_month() const {
    return month;
}
int Date::get_year() const {
    return year;
}
void Date::set_day(int day) {
    this->day = day;
}
void Date::set_month(int month) {
    this->month = month;
}
void Date::set_year(int year) {
    this->year = year;
}

Date::Date(const string& date) {
    char sep;
    stringstream s(date);
    s>> this->day >> sep >> this->month >>sep>>this->year;

}

Date::Date() {
day = 0;
month = 0;
year = 0;
}

bool Date::operator<(Date d2) const {
    if (this->year > d2.year) return false;
    else if(this->year  == d2.year){
        if(this->month > d2.month) return false;
        else if(this->month == d2.month){
            if(this->day>=d2.day) return false;
            else return true;
        }
        else return true;
    }
    else return true;
}

bool is_leap_year(int y){
    if(y%4==0)
        if(y%100==0)
            if(y%400==0)
                return true;
            else
                return false;
        else
            return true;
    else
        return false;
}

int Date::days_in_month(int m) const {
    switch(m){
        case 1:
            return 31;
        case 2:
            if (is_leap_year(year))
                return 29;
            else
                return 28;
        case 3:
            return 31;
        case 4:
            return 30;
        case 5:
            return 31;
        case 6:
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;
    }
}

void Date::increment(int days) {
    while(days>0) {
        if (day + days <= days_in_month(month)) {
            day += days;
            days -= days;
        }
        else {
            days -= (days_in_month(month) - day + 1);
            day = 1;
            month++;
            if(month>12){
                month = 1;
                year++;
            }
        }
    }
}
istream& operator>> (istream& stream, Date& d){
    char aux_char;
    stream>> d.day>>aux_char>>d.month>>aux_char>>d.year;
    return stream;
}

ostream& operator<<(ostream& stream, const Date& d){
    stream << d.get_day() << '/' << d.get_month() << '/' << d.get_year();
    return stream;
}