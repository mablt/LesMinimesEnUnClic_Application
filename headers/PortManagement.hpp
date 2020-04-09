/**
 * @file PortManagement.hpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __PORTMANAGEMENT_HPP__
#define __PORTMANAGEMENT_HPP__
#include "Port.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <list>

class PortManagement
{
private:
    Port* port;
    std::string portName;
    std::string program;
    Date* todaysDate;
public:
    PortManagement();
    ~PortManagement();
    // Display
    void programDisplay();
    void placesAvailableDisplay();
    //Functions
    void callFunction(std::string);
    std::string agreementIdCounterCalculator(std::list<std::string>);
    // Modifications
    void putTodaysDate();
    bool agreementPayed();
    // Inputs
    User* userInput();
    Boat* boatInput();
    void agreementCreation();
    // Creations
    void editSubscriberReceipts(Date*, std::string);
    void editReceipts();
    void reEditOldReceipt();
    void boatCreation();
    void userCreation();
    // Load
    bool loadData();
    bool loadPlaces(std::string);
    bool loadBoats(std::string);
    bool loadUsers(std::string);
    bool loadAgreements(std::string);
    // Save
    void saveData();
    bool saveBoats(std::string);
    bool savePlaces(std::string);
    bool saveUsers(std::string);
    bool saveAgreements(std::string);
 
};

#endif
