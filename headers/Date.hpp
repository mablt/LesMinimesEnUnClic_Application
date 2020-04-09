/**
 * @file Date.hpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __DATE_HPP__
#define __DATE_HPP__

#include <iostream>
#include <string>

class Date
{
    friend bool operator>(const Date&, const Date&);
    friend bool operator==(const Date&, const Date&);
private:
    int month;
    int day;
    int year;
    
public:
    Date();
    Date(int, int, int);
    Date(std::string);
    Date(const Date& d);
    bool leapyr(int);
    Date* plusOneYear();
    Date* plusDurationDate(int);
    std::string getDate();
    int daysNumberOfAMonth(int, int);
    int getMonth();
    int getDay();
};

#endif