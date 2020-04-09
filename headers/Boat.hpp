/**
 * @file Boat.hpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __BOAT_HPP__
#define __BOAT_HPP__
#include <string>
#include "Date.hpp"

class Boat
{
    friend bool operator==(Boat, Boat);
private:
    std::string registration;
    std::string name;
    std::string propulsion;
    std::string motor;
    Date* constructionDate;
    float length;
    std::string type;
    float sailLength;
    int cabinNumber;
public:
    Boat(std::string, std::string, std::string, std::string, Date*, float, std::string, float=NULL, int=NULL);
    ~Boat();
    std::string getRegistration();
    std::string getName();
    std::string getPropulsion();
    std::string getType();
    float getLength();
    float getSailLength();
    std::string getMotor();
    Date* getConstructionDate();
    int getCabinNumber();

};

#endif
