#ifndef __AGREEMENT_HPP__
#define __AGREEMENT_HPP__

#include "Date.hpp"
#include "Boat.hpp"
#include "Place.hpp"
#include "User.hpp"
#include "Visitor.hpp"
#include "Subscriber.hpp"
// #include "FriendFunction.hpp"
#include <string>
#include <map>

class Agreement
{
    // friend float roundFloat(float);
    friend bool operator==(Agreement, Agreement);
private:
    std::string id;
    std::string type;
    Boat* boat;
    User* user;
    Place* place;
    bool water;
    bool electricity;
    Date* startDate;
    Date* stopDate;
    int duration;
    float price;
    std::map<int, std::string> receiptNumbersMap;
    bool payed;
    bool finished;
public:
    Agreement(std::string, Boat*, User*, Place*, bool, bool, Date*, std::map<int, std::string>, int, bool=false, bool=false);
    Agreement( std::string, Boat*, User*, Place*, Date*, std::map<int, std::string>, bool=false, bool=false);
    Agreement(const Agreement&);
    ~Agreement();
    std::string getId();
    std::string getType();
    User* getUser();
    Place* getPlace();
    Boat* getBoat();
    Date* getStartDate();
    Date* getStopDate();
    float getPrice();
    int getDuration();
    bool getWater();
    bool getElectricity();
    std::map<int, std::string> getReceiptNumbersMap();
    bool getPayed();
    bool getFinished();
    void setNewReceiptNumber(int, std::string);
    float priceCalculation();
    Date* stopDateCalculation();
    std::string typeCalculation();
    std::map<std::string, std::string> toString();
    void putPayed();
    void putFinished();
    std::string getNumberReceiptFromMonth(int);
    bool notExistingPreviousReceipt(int);
    

};





#endif