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