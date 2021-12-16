//
// Created by pedro on 01/12/21.
//

#ifndef AIRLINE_SCHEDULE_H
#define AIRLINE_SCHEDULE_H


#include "Date.h"
#include "Time.h"
#include <istream>
class Schedule {
private:
    Time time;
    Date date;
public:
    /**
     * Default Constructor of class Schedule
     * Represents mid night of the day 0 of month 0 of year 0
     */
    Schedule();
    /**
     * Constructor of class Schedule
     * @param time object of class time representing a given hour:minute of a day
     * @param date object of class date representing a given day of the year
     */
    Schedule(Time time,Date date);
    /**
     * getter for the time attribute
     * @return returns an object of class time representing a time of day.
     */
    Time get_time()const;
    /**
     * getter for the date attribute
     * @return returns an object of class date representing a date of a year.
     */
    Date get_date()const;
    /**
     * Overloading of the < operator used to compare two Schedules.
     * @param schedule2 Object passed by reference of the same class.
     * @return returns a boolean value indicating whether this schedule is lesser than schedule2
     */
    bool operator<(Schedule const &schedule2);
    /**
     * Overloading of the >> input operator
     * @param stream istream which will be modified and then used to read from a text file
     * @param s object of Class Schedule passed by reference
     * @return returns an istream which is ready to be used on to read from a text file
     */
    friend istream& operator>> (istream& stream, Schedule &s);
    /**
     * Overloading of the << output operator
     * @param stream ostream which will be modified and then used to write on a text file
     * @param s object of Class Time passed by reference
     * @return returns an ostream which is ready to be used on to write on a text file
     */
    friend ostream& operator<< (ostream& stream,const Schedule &s);
};


#endif //AIRLINE_SCHEDULE_H
