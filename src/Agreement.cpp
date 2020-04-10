/**
 * @file Agreement.cpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "./../headers/Agreement.hpp"
// #include "FriendFunction.hpp"
#include <string>
#include <map>
using namespace std;

static float ANNUAL_SUBSCRIBER_PRICE = 500;
static float DAY_VISTOR_PRICE = 20;
static float WATER_PRICE = 5;
static float ELECTRICITY_PRICE = 5;




/*      --- Constructor ---     */
Agreement::Agreement(string _id, Boat* _boat, User* _user, Place* _place, bool _water, bool _electricity, Date* _startDate, map<int, string> _receiptNumbersMap, int _duration, bool _payed, bool _finished)
{
    id = _id;
    type = "Visitor Agreement";
    boat = _boat;
    user = _user;
    place = _place;
    water = _water;
    electricity = _electricity;
    startDate = _startDate;
    duration = _duration;
    stopDate = stopDateCalculation();
    price = priceCalculation();
    receiptNumbersMap = _receiptNumbersMap;
    payed = _payed;
    finished = _finished;
}

/*      --- Constructor ---     */
Agreement::Agreement(string _id, Boat* _boat, User* _user, Place* _place, Date* _startDate, map<int,string> _receiptNumbersMap, bool _payed, bool _finished){
    id = _id;
    type = "Subscriber Agreement";
    boat = _boat;
    user = _user;
    place = _place;
    water = false;
    electricity = false;
    startDate = _startDate;
    stopDate = stopDateCalculation();
    duration = NULL;
    price = priceCalculation();
    receiptNumbersMap = _receiptNumbersMap;
    payed = _payed;
    finished = _finished;
    
}

/*      --- Constructor ---     */
Agreement::Agreement(const Agreement& a){
    this->id = a.id;
    this->type = a.type;
    this->boat = a.boat;
    this->user = a.user;
    this->place = a.place;
    this->startDate = a.startDate;
    this->stopDate = a.stopDate;
    if(a.type == "Visitor"){
        this->duration = a.duration;
        this->water = a.water;
        this->electricity = a.electricity;
    }
}

/*      --- Destructor ---     */
Agreement::~Agreement()
{
    boat = NULL;
    user = NULL;
    place = NULL; 
    startDate = NULL;
    stopDate = NULL;
}

/*      --- Operator overloading ---     */
bool operator==(Agreement a1, Agreement a2){
    return(a1.id==a2.id && a1.type==a2.type && a1.boat==a2.boat 
            && a1.user==a2.user && a1.place==a2.place && a1.water==a2.water 
            && a1.electricity==a2.electricity && a1.startDate==a2.startDate 
            && a1.stopDate==a2.stopDate && a1.duration==a2.duration && 
            a1.price==a2.price);
}

/*  ------------------- METHODS -------------------   */
/**
 * @brief Get the receipt number of a month given in argument
 * 
 * @param month Month number which the receipt number is asked
 * @return string which contains the receipt numver value
 */
string Agreement::getNumberReceiptFromMonth(int month){
    return receiptNumbersMap[month];
}

/**
 * @brief Put to finished the agreement and remove the boat of the place
 * 
 */
void Agreement::putFinished(){
    finished = true;
    place->removeBoat();
}

/**
 * @brief Calculates the price of the agreement
 * 
 * @return float which represents the price of the agreement
 */
float Agreement::priceCalculation(){
    float price;
    if (type == "Subscriber Agreement"){
        price = ANNUAL_SUBSCRIBER_PRICE;
        
        // return price/12; // Return the price for one month
    }
    else{
        price = DAY_VISTOR_PRICE;
        price *= duration;
    }
    if(place->getType() == "Mooring Place"){
            price /= 2;
    }
    
    if (boat->getType() == "Sailboat1"){
        price += price*0.3;   // Increase of 30% for type 1 sailboat
    }
    else {
        if (boat->getType() == "Sailboat2"){
            price += price*0.6; // Increase of 60% for type 2 sailboat
        }
    }
    if(type == "Visitor Agreement" && place->getType() == "FasteningRing Place"){
            if(water){
                price += WATER_PRICE*duration;
            }
            if(electricity){
                price += ELECTRICITY_PRICE*duration;
            }
    }
    return price;
    
}

/**
 * @brief Calculates the stop date of the agreement
 * 
 * @return Date object contains the stop date of the agreement
 */
Date* Agreement::stopDateCalculation(){
    if(getType() == "Subscriber Agreement")
        return startDate->plusOneYear();
    else
        return startDate->plusDurationDate(duration);
}

/**
 * @brief Get a string map with the representation of values
 * 
 * @return map<string, string> Map contains the values. First represent the name of the argument. Second the value.
 */
map<string, string> Agreement::toString(){
    map<string, string> result;
    result["agreementId"] = id;
    result["agreementType"] = type;
    result["duration"] = to_string(duration);
    result["agreementDuration"] = to_string(duration);
    result["agreementWater"] = to_string(water);
    result["agreementElectricity"] = to_string(electricity);
    result["placeId"] = place->getId();
    result["placeType"] = place->getType();
    result["boatRegistration"] = boat->getRegistration();
    result["boatName"] = boat->getName();
    result["boatPropulsion"] = boat->getPropulsion();
    result["boatLength"] = to_string(boat->getLength());
    result["userId"] = user->getId();
    result["userFirstName"] = user->getFirstName();
    result["userLastName"] = user->getLastName();  
    result["userAddress"] = user->getAddress();
    return result;
}

/**
 * @brief Say if no previous receipt exist for a month given
 * 
 * @param month Month number
 * @return true if no previous receipt exist
 * @return false if a previous receipt exist
 */
bool Agreement::notExistingPreviousReceipt(int month){
    if(receiptNumbersMap.empty())
        return true;
    // If there is the key number with the name 'month' is greater than 0    
    if(receiptNumbersMap.count(month) > 0)
        return false; // The month exist in the map
    return true;
}

/*  ------------------- GETTERS & SETTERS -------------------   */
string Agreement::getId(){
    return id;
}

string Agreement::getType(){
    return type;
}

User* Agreement::getUser(){
    return user;
}

Place* Agreement::getPlace(){
    return place;
}

Boat* Agreement::getBoat(){
    return boat;
}

Date* Agreement::getStartDate(){
    return startDate;
}

int Agreement::getDuration(){
    return duration;
}

bool Agreement::getWater(){
    return water;
}

bool Agreement::getElectricity(){
    return electricity;
}


float Agreement::getPrice(){
    return price;
}

Date* Agreement::getStopDate(){
    return stopDate;
}

map<int, string> Agreement::getReceiptNumbersMap(){
    return receiptNumbersMap;
}

void Agreement::setNewReceiptNumber(int month, string number){
    receiptNumbersMap[month] = number;
}

void Agreement::putPayed(){
    payed = true;
}

bool Agreement::getFinished(){
    return finished;
}

bool Agreement::getPayed(){
    return payed;
}
