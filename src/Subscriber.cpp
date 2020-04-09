/**
 * @file Subscriber.cpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "../headers/Subscriber.hpp"
#include <string>
using namespace std;

/*      --- Constructor ---     */
Subscriber::Subscriber(string _id, string _fisrtName, string _lastName, string _adress, string _phone, string _mail, list<Boat*> _boatsList):User(_id, _fisrtName, _lastName, _adress, _phone, _mail, _boatsList, "Subscriber")
{

}
