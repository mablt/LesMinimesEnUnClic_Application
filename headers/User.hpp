/**
 * @file User.hpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __USER_HPP__
#define __USER_HPP__
#include "Boat.hpp"
#include <string>
#include <list>

class User
{
    friend bool operator==(User, User);
private:
    std::string id;
    std::string firstName;
    std::string lastName;
    std::string address;
    std::string phone;
    std::string mail;
    std::list<Boat*> boatsList;
    std::string type;
public:
    User(std::string, std::string, std::string, std::string, std::string, std::string, std::list<Boat*>, std::string);
    std::string getId();
    std::string getFirstName();
    std::string getLastName();
    std::string getAddress();
    std::string getPhone();
    std::string getMail();
    std::list<Boat*> getBoatsList();
    std::string getType();
    void addBoat(Boat*);
};


#endif  