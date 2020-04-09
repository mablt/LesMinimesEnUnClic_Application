/**
 * @file main.cpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "../headers/Date.hpp"
#include "../headers/../headers/Boat.hpp"
#include "../headers/Deckboat.hpp"
#include "../headers/Sailboat1.hpp"
#include "../headers/Sailboat2.hpp"
#include "../headers/User.hpp"
#include "../headers/Subscriber.hpp"
#include "../headers/Visitor.hpp"
#include "../headers/Place.hpp"
#include "../headers/Mooring.hpp"
#include "../headers/FasteningRing.hpp"
#include "../headers/Receipt.hpp"
#include "../headers/Agreement.hpp"
#include "../headers/Port.hpp"
#include "../headers/PortManagement.hpp"

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <math.h>
using namespace std;

int main(){
    PortManagement* port = new PortManagement();
    port->programDisplay();

    return 0;
}