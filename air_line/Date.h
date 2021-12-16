//
// Created by rui on 01/12/21.
//

#ifndef AIRLINE_DATE_H
#define AIRLINE_DATE_H
#include <cstdlib>
#include <string>
#include <sstream>
#include <istream>
using namespace std;
class Date {
private:
    int day{};
    int month{};
    int year{};
public:
    /**
     * Default constructor of class Date
     * Represents the day 0 of month 0 of the year 0
     */
    Date();
    /**
     * Constructor of the Date class
     * @param day integer representing a day of a month
     * @param month integer representing a month of a year
     * @param year integer representing a year
     */
    Date(int day, int month, int year);
    /**
     * Another constructor of the Date class
     * @param date string representing a date in the format dd/mm/yy
     */
    explicit Date(const string& date);
    /**
     * Method that we can use to increment a date by a number of days.
     * @param days integer representing the numbers of days we want to increment to a date. Default value is 1
     */
    void increment(int days=1);
    /**
     * Method that tells us the amount of a days in a month and takes in account whether we're in a leap year or not
     * @param m integer representing a given month of the year 1<=m<=12
     * @return returns an integer representing the amount of days in month m
     */
    int days_in_month(int m) const;
    /**
     * getter for the day attribute
     * @return returns integer representing the day of a date
     */
    int get_day() const;
    /**
     * getter for the month attribute
     * @return returns integer representing the month of a date
     */
    int get_month() const;
    /**
     * getter for the year attribute
     * @return returns integer representing the year of a date
     */
    int get_year() const;
    /**
     * setter for the day attribute
     * @param day integer representing the day of a date
     */
    void set_day(int day);
    /**
     * setter for the month attribute
     * @param month integer representing the month of a date
     */
    void set_month(int month);
    /**
     * setter for the year attribute
     * @param year integer representing the year of a date
     */
    void set_year(int year);
    /**
     * Overloading of the < operator used to compare two Dates.
     * @param d2 Object passed by reference of the same class.
     * @return returns a boolean value indicating whether this date is lesser than d2
     */
    bool operator <(Date d2) const;
    /**
     * Overloading of the >> input operator
     * @param stream istream which will be modified and then used to read from a text file.
     * @param d object of Class Date passed by reference.
     * @return returns an istream which is ready to be used on to read from a text file.
     */
    friend istream& operator>> (istream& stream, Date& d);
    /**
     * Overloading of the << output operator
     * @param stream ostream which will be modified and then used to write on a text file
     * @param d object of Class Date passed by reference.
     * @return returns an ostream which is ready to be used on to write on a text file
     */
    friend ostream& operator<< (ostream& stream, const Date& d);
};
#endif //AIRLINE_DATE_H
