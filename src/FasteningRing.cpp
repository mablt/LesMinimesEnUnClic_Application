/**
 * @file FasteningRing.cpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "../headers/FasteningRing.hpp"
#include <string>
using namespace std;

/*      --- Constructor ---     */
FasteningRing::FasteningRing(string _id, bool _taken, Boat* _boat, float _length):Place(_id, _taken, "FasteningRing Place", _boat, _length)
{}
