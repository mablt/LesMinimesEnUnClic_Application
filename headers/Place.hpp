/**
 * @file Place.hpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __PLACE_HPP__
#define __PLACE_HPP__
#include "Boat.hpp"
#include <string>

class Place
{
    friend bool operator==(Place, Place);
private:
    std::string id;
    bool taken;
    Boat* boat;
    std::string type;
    float length;
public:
    Place(std::string, bool, std::string, Boat*, float);
    ~Place();
    Boat* getBoat();
    std::string getId();
    std::string getType();
    bool getTaken();
    float getLength();
    virtual bool getWater();
    virtual bool getElectricity();
    void setBoat(Boat*);
    Boat* removeBoat();
};


#endif