/**
 * @file Deckboat.hpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __DECKBOAT_HPP__
#define __DECKBOAT_HPP__
#include "Boat.hpp"
#include "Date.hpp"
#include <string>

class Deckboat : public Boat
{
public:
    Deckboat(std::string, std::string, std::string, Date*, float);
};


#endif