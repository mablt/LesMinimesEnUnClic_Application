/**
 * @file Sailboat2.cpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "../headers/Sailboat2.hpp"
#include <string>
using namespace std;

/*      --- Constructor ---     */
Sailboat2::Sailboat2(string _registration, string _name, string _motor, Date* _constructionDate, float _length, float _sailLength, int _cabinNumber) : Boat(_registration, _name, "Sail Propulsion", _motor, _constructionDate, _length, "Sailboat2", _sailLength, _cabinNumber){

}
