/**
 * @file Subscriber.hpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __SUBSCRIBER_HPP__
#define __SUBSCRIBER_HPP__
#include "User.hpp"
#include "Date.hpp"
#include <string>
#include <list>

class Subscriber : public User
{
public:
    Subscriber(std::string, std::string, std::string, std::string, std::string, std::string, std::list<Boat*>);
};

#endif
