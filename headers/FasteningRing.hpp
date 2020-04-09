
/**
 * @file FasteningRing.hpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __FASTENINGRING_HPP__
#define __FASTENINGRING_HPP__
#include "Place.hpp"
#include <string>

class FasteningRing : public Place
{
public:
    FasteningRing(std::string, bool, Boat*, float);
};

#endif