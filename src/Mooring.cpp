/**
 * @file Mooring.cpp
 * @author Mathieu BOLTEAU (mathieu.bolteau1@gmail.com)
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "../headers/Mooring.hpp"
#include <string>
using namespace std;

/*      --- Constructor ---     */
Mooring::Mooring(string _id, bool _taken, Boat* _boat):Place(_id, _taken, "Mooring Place", _boat, NULL)
{}
