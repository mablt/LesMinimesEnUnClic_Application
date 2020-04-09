/**
 * @file Mooring.hpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __MOORING_HPP__
#define __MOORING_HPP__
#include "Place.hpp"
#include <string>

class Mooring : public Place
{
public:
    Mooring(std::string, bool, Boat*);
};

#endif