/**
 * @file Boat.cpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "../headers/Boat.hpp"
#include<math.h>
#include <string>
using namespace std;


/*      --- Constructor ---     */
Boat::Boat(string _registration, string _name, string _propulsion, string _motor, Date* _constructionDate, float _length, string _type, float _sailLength, int _cabinNumber){
    registration = _registration;
    name = _name;
    propulsion = _propulsion;
    motor = _motor;
    constructionDate = _constructionDate;
    length = _length;
    type = _type;
    sailLength = _sailLength;
    cabinNumber = _cabinNumber;
}

/*      --- Destructor ---     */
Boat::~Boat(){ 
    delete constructionDate;
}

/*      --- Operator overloading ---     */
bool operator==(Boat b1, Boat b2){
    if(b1.registration == b2.registration && b1.propulsion==b2.propulsion 
        && b1.name==b2.name && b1.motor==b2.motor && b1.length==b2.length)
        return true;
    else
        return false;
    
}

/*  ------------------- GETTERS & SETTERS -------------------   */
string Boat::getRegistration(){
    return registration;
}

string Boat::getName(){
    return name;
}

string Boat::getPropulsion(){
    return propulsion;
}

float Boat::getLength(){
    return length;
}

string Boat::getType(){
    return type;
}

string Boat::getMotor(){
    return motor;
}

Date* Boat::getConstructionDate(){
    return constructionDate;
}

float Boat::getSailLength(){
    return sailLength;
}

int Boat::getCabinNumber(){
    return cabinNumber;
}
