/**
 * @file Place.cpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "../headers/Place.hpp"
#include <string>
using namespace std;

/*      --- Constructor ---     */
Place::Place(string _id, bool _taken, string _type, Boat* _boat, float _length)
{
    id = _id;
    taken = _taken;
    boat = _boat;
    type = _type;
    length = _length;
}

/*      --- Destructor ---     */
Place::~Place(){
    boat = NULL;
}

/*  ------------------- METHODS -------------------   */
/**
 * @brief Remove the boat present in the place
 * 
 * @return Boat object which represents the removed boat 
 */
Boat* Place::removeBoat(){
    taken = false;
    Boat* temp = boat;
    boat = NULL;
    return temp;
}

/*      --- Operator overloading ---     */
bool operator==(Place p1, Place p2){
    return (p1.id==p2.id && p1.taken==p2.taken && p1.boat==p2.boat && p1.type==p2.type);
}

/*  ------------------- GETTERS & SETTERS -------------------   */
Boat* Place::getBoat(){
    return boat;
}

string Place::getId(){
    return id;
}

string Place::getType(){
    return type;
}

bool Place::getTaken(){
    return taken;
}

float Place::getLength(){
    return length;
}
bool Place::getWater(){
    return NULL;
}
bool Place::getElectricity(){
    return NULL;
}

void Place::setBoat(Boat* b){
    boat = b;
    taken = true;
}
