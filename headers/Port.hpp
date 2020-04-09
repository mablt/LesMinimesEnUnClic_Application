/**
 * @file Port.hpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __PORT_HPP__
#define __PORT_HPP__
#include "User.hpp"
#include "Place.hpp"
#include "Receipt.hpp"
#include "Subscriber.hpp"
#include "Agreement.hpp"
#include <list>


class Port
{
private:
    std::list<Subscriber*> subscribersList;
    std::list<Place*> placesList;
    std::list<User*> usersList;
    std::list<Boat*> boatsList;
    std::list<Agreement*> agreementsList;
    std::list<Subscriber*>::iterator itSubscribersList;
    std::list<Place*>::iterator itPlacesList;
    std::list<User*>::iterator itUsersList;
    std::list<Boat*>::iterator itBoatsList;
    std::list<Agreement*>::iterator itAgreementsList;
    std::string receiptIdCounter;
    std::string agreementIdCounter;
    std::string userIdCounter;
    std::string placeIdCounter;
public:
    Port();
    // Add
    void addSubscriber(Subscriber*);
    void addPlace(Place*);
    void addUser(User*);
    void addBoat(Boat*);
    void addAgreement(Agreement*);
    // Create
    Subscriber* createSubscriber(std::string, std::string, std::string, std::string, std::string, std::list<Boat*>);
    Visitor* createVisitor(std::string, std::string, std::string, std::string, std::string, std::list<Boat*>);
    Place* createPlace(bool, std::string, Boat*, float);
    Agreement* createAgreement( Boat*, Place*, User*, Date*, bool=NULL, bool=NULL, int=NULL);
    Receipt* createReceipt(Date*, Agreement*, std::string, int=NULL);   
    // Input
    Date* dateInput();
    // Incremente
    std::string idIncremente(std::string*);
    void receiptIdIncremente();
    //Functions
    std::list<Place*> getAvailablePlaces();
    void putBoatInPlace(Boat*, Place*);
    void putPayedAgreement(Agreement*);
    void putFinishedAgreement(Date*);
    void removeBoatofUser(Boat*);
    // Getters & Setters
    std::list<Boat*> getBoatsList();
    std::list<Place*> getPlacesList();
    std::list<User*> getUsersList();
    std::list<Agreement*> getAgreementsList();
    Boat* getBoat(std::string);
    Agreement* getAgreement(std::string);
    Agreement* getAgreement(User*);
    User* getUser(std::string);
    Place* getPlace(std::string); 
    User* getUserById(std::string);
    User* getUserOfABoat(Boat*);
    void setUserIdCounter(std::string);
    void setPlaceIdCounter(std::string);
    void setAgreementIdCounter(std::string);
    void setReceiptIdCounter(std::string);
    std::string getReceiptIdCounter();
};

#endif