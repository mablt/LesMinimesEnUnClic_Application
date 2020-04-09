/**
 * @file Sailboat2.hpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __SAILBOAT2_HPP__
#define __SAILBOAT2_HPP__
#include "Boat.hpp"
#include <string>

class Sailboat2 : public Boat
{
public:
    Sailboat2(std::string, std::string, std::string, Date*, float, float, int);
};


#endif