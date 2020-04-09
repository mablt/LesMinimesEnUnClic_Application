/**
 * @file User.cpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "../headers/User.hpp"
#include <string>
#include <list>
using namespace std;


/*      --- Constructor ---     */
User::User(string _id, string _firstName, string _lastName, string _address, string _phone, string _mail, list<Boat*> _boatsList, string _type){
    id = _id;
    firstName = _firstName;
    lastName = _lastName;
    address = _address;
    phone = _phone;
    mail = _mail;
    boatsList = _boatsList;
    type = _type;
}

/*      --- Operator overloading ---     */
bool operator==(User u1, User u2){
    if(u1.id==u2.id && u1.firstName==u2.firstName && u1.lastName==u2.lastName && u1.address==u2.address && u1.phone==u2.phone && u1.mail==u2.mail && u1.boatsList==u2.boatsList && u1.type==u2.type)
        return true;
    else
        return false;
    
}

/*  ------------------- GETTERS & SETTERS -------------------   */
string User::getId(){
    return id;
}

list<Boat*> User::getBoatsList(){
    return boatsList;
}

string User::getFirstName(){
    return firstName;
}

string User::getLastName(){
    return lastName;
}

string User::getAddress(){
    return address;
}

string User::getPhone(){
    return phone;
}

string User::getMail(){
    return mail;
}

string User::getType(){
    return type;
}

void User::addBoat(Boat* b){
    boatsList.push_back(b);
}
