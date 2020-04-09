/**
 * @file Deckboat.cpp
 * @author Mathieu BOLTEAU (mathieu.bolteau1@gmail.com)
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "../headers/Deckboat.hpp"
#include <string>
using namespace std;

/*      --- Constructor ---     */
Deckboat::Deckboat(string _registration, string _name, string _motor, Date* _constructionDate, float _length) : Boat(_registration, _name, string("Motorized Propulsion"), _motor, _constructionDate,  _length, string("Deckboat"))
{}
