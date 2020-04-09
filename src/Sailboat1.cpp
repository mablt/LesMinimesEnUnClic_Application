/**
 * @file Sailboat1.cpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "../headers/Sailboat1.hpp"
#include <string>
using namespace std;

/*      --- Constructor ---     */
Sailboat1::Sailboat1(string _registration, string _name, string _motor, Date* _constructionDate, float _length, float _sailLength, int _cabinNumber) : Boat(_registration, _name, "Sail Propulsion", _motor, _constructionDate, _length, "Sailboat1", _sailLength, _cabinNumber)
{

}
