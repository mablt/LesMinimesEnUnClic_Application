/**
 * @file Date.cpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "../headers/Date.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std;

/*      --- Constructor ---     */
Date::Date(){
    month = 0;
    day = 0;
    year = 0;
}

/*      --- Constructor ---     */
Date::Date(int mm, int dd, int yyyy){
    month = mm;
    day = dd;
    year = yyyy;
}

/*      --- Constructor ---     */
Date::Date(string mmddyyyy){
    int length = mmddyyyy.size();
    if(length==8){
        year = stoi(mmddyyyy.substr(4,4));
        month = stoi(mmddyyyy.substr(0,2));
        day = stoi(mmddyyyy.substr(2,2));
    }
    else{
        year = stoi(mmddyyyy.substr(6,4));
        month = stoi(mmddyyyy.substr(0,2));
        day = stoi(mmddyyyy.substr(3,3));
    }   
}

/*      --- Constructor ---     */
Date::Date(const Date& d){
    month = d.month;
    day = d.day;
    year = d.year;

}

/*      --- Operator overloading ---     */
bool operator>(const Date& d1, const Date& d2){
    if(d1.year>d2.year)
        return true;
    else{
        if(d1.year>=d2.year && d1.month>d2.month)
            return true;
        else{
            if(d1.year>=d2.year && d1.month>=d2.month && d1.day>d2.day)
                return true;
        }
    }
    return false;
}

/*      --- Operator overloading ---     */
bool operator==(const Date& d1, const Date& d2){
    return (d1.year==d2.year && d1.month==d2.month && d1.day==d2.day);
}

/*  ------------------- METHODS -------------------   */
/**
 * @brief Say if the year given is a leap year or not
 * 
 * @param year 
 * @return true if it is a leap year
 * @return false if it is not a leap year
 */
bool Date::leapyr(int year){
    if (year % 400 == 0)  
        return true;  
    if (year % 100 == 0)  
        return false;  
    if (year % 4 == 0)  
        return true;  
    return false; 
}

/**
 * @brief Get the days number present in the month given
 * 
 * @param month Month value
 * @param year Year value
 * @return Days number present in the month given in arguments
 */
int Date::daysNumberOfAMonth(int month, int year){
    if (month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
        return 31;
    else{
        if(month==2){
            if(leapyr(year))
                return 29;
            else
                return 28;
        }
        return 30;
    }
}
    

/**
 * @brief Get the date to a string
 * 
 * @return String contains the date value
 */
string Date::getDate(){
    stringstream  res;
    res << setfill('0')
        << setw(2) << month << '/'
        << setw(2) << day  << '/'
        << setw(2) << year;
    return res.str();
}

/**
 * @brief Add one year to the actual date
 * 
 * @return Date object with a supplementary year
 */
Date* Date::plusOneYear()
{   
    int dd = this->day;
    int mm = this->month;
    int yyyy = this->year;
    dd--;
    yyyy++;
    if(dd==0){
        mm--;
        if(mm==0){
            mm=12;
            yyyy--;
        }
        dd=daysNumberOfAMonth(mm, yyyy);
    }
    return new Date(mm, dd, yyyy);
}

/**
 * @brief Add a duration to a date
 * 
 * @param duration Number of days to add
 * @return Date object with the duration added
 */
Date* Date::plusDurationDate(int duration){
    int dd = this->day;
    int mm = this->month;
    int yyyy = this->year;
    duration--; // -1 because the startDate is the first day of the agreement
    for(duration; duration>0; duration--){
        dd++;
        if(dd>daysNumberOfAMonth(mm,yyyy)){
            dd = 1;
            mm++;
            if(mm > 12){
                mm=1;
                yyyy++;
            }
        }
    }
    return new Date(mm, dd, yyyy);
}


/*  ------------------- GETTERS & SETTERS -------------------   */
int Date::getMonth(){
    return month;
}

int Date::getDay(){
    return day;
}
