/**
 * @file Visitor.hpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __VISITOR_HPP__
#define __VISITOR_HPP__
#include "User.hpp"
#include "Date.hpp"
#include <string>
#include <list>

class Visitor : public User
{
public:
    Visitor(std::string, std::string, std::string, std::string, std::string, std::string, std::list<Boat*>);
};

#endif
