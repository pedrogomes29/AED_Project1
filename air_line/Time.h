//
// Created by pedro on 01/12/21.
//

#ifndef AIRLINE_TIME_H
#define AIRLINE_TIME_H
#include <istream>
using namespace std;
class Time {
private:
    int hour;
    int minute;
public:
    /**
     * Default constructor of Time class
     * Default hour and minute is midnight
     */
    Time();
    /**
     * Constructor of Time class
     * @param hour integer representing an hour of a day
     * @param minute int representing the minutes of an hour
     */
    Time(int hour,int minute);
    /**
     * setter for the hour attribute
     * @param hour integer representing an hour of a day
     */
    void set_hour(int hour);
    /**
     * setter for the minute attribute
     * @param minute integer representing the minutes of an hour
     */
    void set_minute (int minute);
    /**
     * getter for hour attribute
     * @return integer representing an hour of a day
     */
    int get_hour() const;
    /**
     * getter for minute attribute
     * @return int representing the minutes of an hour
     */
    int get_minute() const;
    /**
     * Overloading of the < operator used to compare two Times.
     * @param time2 Object passed by reference of the same class.
     * @return returns a boolean value indicating whether this time is lesser than time2
     */
    bool operator<(Time const &time2) const;
    /**
     * Overloading of the >> input operator
     * @param stream istream which will be modified and then used to read from a text file
     * @param t object of Class Time passed by reference
     * @return returns an istream which is ready to be used on to read from a text file
     */
    friend istream &operator>>(istream& stream,  Time& t);
    /**
     * Overloading of the << output operator
     * @param stream ostream which will be modified and then used to write on a text file
     * @param t object of Class Time passed by reference
     * @return returns an ostream which is ready to be used on to write on a text file
     */
    friend ostream &operator<< (ostream& stream, const Time& t);
    /**
     * Overloading of the + operator so it can be made possible adding two hours
     * @param t2 object of class time passed by reference.
     * @return returns an object of class Time containing the result of the adding operation between two times.
     */
    Time operator+(const Time &t2) const;
};


#endif //AIRLINE_TIME_H
