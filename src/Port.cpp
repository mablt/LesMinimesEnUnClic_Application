/**
 * @file Port.cpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "../headers/Port.hpp"
#include <string>
#include <list>
using namespace std;

/*      --- Constructor ---     */
Port::Port(){
    subscribersList = list<Subscriber*>();
    placesList = list<Place*>();
    usersList = list<User*>();
    boatsList = list<Boat*>();
    agreementsList = list<Agreement*>();
    receiptIdCounter = "000000";
    agreementIdCounter = "A00000";
    userIdCounter = "U00000";
    placeIdCounter = "P00000";    
}

/*  ------------------- METHODS -------------------   */
/**
 * @brief Add a subscriber to the subscribers list
 * 
 * @param s Subscriiber pointer to add to the list
 */
void Port::addSubscriber(Subscriber* s){
    subscribersList.push_back(s);
}

/**
 * @brief Add a place to the places list
 * 
 * @param p Place pointer to add to the list
 */
void Port::addPlace(Place* p){
    placesList.push_back(p);
}

/**
 * @brief Add a user to the users list
 * 
 * @param u User pointer to add to the list
 */
void Port::addUser(User* u){
    usersList.push_back(u);
}

/**
 * @brief Add a boat to the boats list
 * 
 * @param b Boat pointer to add to the lsit
 */
void Port::addBoat(Boat* b){
    boatsList.push_back(b);
}

/**
 * @brief Add an agreement to the agreements list
 * 
 * @param a Agreement pointer to add to the list
 */
void Port::addAgreement(Agreement* a){
    agreementsList.push_back(a);
}

/**
 * @brief Create a subscriber
 * 
 * @param firstName First name value of the subscriber  to create
 * @param lastName Last name value of the subscriber  to create
 * @param address Address value of the subscriber  to create
 * @param phone Phone value of the subscriber  to create
 * @param mail Mail value of the subscriber  to create
 * @param boatsList List of Boat pointer of the subscriber  to create
 * @return Subscriber pointer of the subscriber created
 */
Subscriber* Port::createSubscriber(string firstName, string lastName, string address, string phone, string mail, list<Boat*> boatsList){
    string id(idIncremente(&userIdCounter));
    return new Subscriber(id, firstName, lastName, address, phone, mail, boatsList);
}

/**
 * @brief Create a visitor
 * 
 * @param firstName First name value of the visitor to create
 * @param lastName Last name value of the visitor to create
 * @param address Adress value of the visitor to create
 * @param phone Phone value of the visitor to create
 * @param mail Mail value of the visitor to create
 * @param boatsList List of Boat pointer of the visitor to create
 * @return Visitor pointer of the visitor created
 */
Visitor* Port::createVisitor(string firstName, string lastName, string address, string phone, string mail, list<Boat*> boatsList){
    string id(idIncremente(&userIdCounter));
    return new Visitor(id, firstName, lastName, address, phone, mail, boatsList);
}

/**
 * @brief Create a place
 * 
 * @param taken Taken value of the place to create
 * @param type Type value of the place to create
 * @param boat Boat pointer of the place to create
 * @param length Length value of the place to create
 * @return Place pointer of the place created
 */
Place* Port::createPlace(bool taken, string type, Boat* boat, float length){
    string id(idIncremente(&placeIdCounter));
    return new Place(id, taken, type, boat, length);
}

/**
 * @brief Create an agreement
 * 
 * @param boat Boat pointer of the agreement to create
 * @param place Place pointer of the agreement to create
 * @param user User pointer of the agreement to create
 * @param startDate Date pointer of the agreement to create
 * @param water Water value of the agreement to create
 * @param electricity Electricity value of the agreement to create
 * @param duration Duration value of the agreement to create
 * @return Agreement pointer of the agreement created
 */
Agreement* Port::createAgreement(Boat* boat, Place* place, User* user, Date* startDate, bool water, bool electricity, int duration){
    string id(idIncremente(&agreementIdCounter));
    place->setBoat(boat);
    if(user->getType() == "Subscriber")
        return new Agreement(id, boat, user, place, startDate, map<int,string>());
    return new Agreement(id, boat, user, place, water, electricity, startDate, map<int,string>(), duration);
}

/**
 * @brief Create the receipt of an agreement given
 * 
 * @param date Date pointer of the today's date
 * @param agreement Agreement pointer of the agreement which the receipt creation is asked
 * @param folderPath Folder path which the file will be created
 * @param month Month value of the subscriber agreement of the receipt created
 * @return Receipt pointer of the receipt created
 */
Receipt* Port::createReceipt(Date* date, Agreement* agreement, string folderPath, int month){
    Receipt* r;
    string receiptNumber;
    if(agreement->notExistingPreviousReceipt(month)){
        receiptIdIncremente();
        if(agreement->getType()=="Subscriber Agreement")
            agreement->setNewReceiptNumber(month, receiptIdCounter);
        else
            agreement->setNewReceiptNumber(1, receiptIdCounter);
        r = new Receipt(receiptIdCounter, date, agreement, month);
    }
    else{
        if(agreement->getType()=="Subscriber Agreement")
            receiptNumber = agreement->getNumberReceiptFromMonth(month);
        else
            receiptNumber = agreement->getNumberReceiptFromMonth(0);
        r = new Receipt(receiptNumber, date, agreement, month);
    }
    r->generateReceipt(folderPath);
    return r;
}

/**
 * @brief Input of a date
 * 
 * @return Date pointer of the date created
 */
Date* Port::dateInput(){
    string date;
    cout << "Indicate the date (mmddyyyy or mm/dd/yyyy)" << endl << ">>> ";
    cin >> date;
    return new Date(date);
}

/**
 * @brief Incremente the id given 
 * 
 * @param id Id pointer of the id value to increment
 * @return string Id incremented value
 */
string Port::idIncremente(string* id){
    int number = stoi((*id).substr(1, (*id).size()-1));
    if(number == 99999){
        cerr << "Error : Generation of an other ID impossible." << endl;
        return string("PROBLEM_ID");
    }
    else{
        int idLength;
        number ++;
        (*id) = (*id).substr(0,1)+to_string(number);
        idLength = (*id).size();
        if(idLength != 6){
            string begining((*id).substr(0,1));
            string end((*id).substr(1, idLength-1));
            string leadingZero(5-end.size(), '0');
            (*id) = begining+leadingZero+end;
        }
        return (*id);
    }
}

/**
 * @brief Incremente the receipt id counter
 * 
 */
void Port::receiptIdIncremente(){
    int number = stoi(receiptIdCounter);
    if(number == 999999){
        cout << "Generation of an other receipt ID impossible." << endl;
    }
    else{
        number ++;
        receiptIdCounter = to_string(number);
        int idLength = receiptIdCounter.size();
        if(idLength != 6){
            string end = receiptIdCounter;
            string leadingZero(6-end.size(), '0');
            receiptIdCounter = leadingZero+end;
        }
    }
}

/**
 * @brief Get the available places
 * 
 * @return list<Place*> List of place pointers of available places
 */
list<Place*> Port::getAvailablePlaces(){
    list<Place*> availablePlaces;
    for(itPlacesList=placesList.begin(); itPlacesList!=placesList.end(); itPlacesList++){
        if(!((*itPlacesList)->getTaken()))
            availablePlaces.push_back((*itPlacesList));
    }
    return availablePlaces;
}

/**
 * @brief Put a boat in a place
 * 
 * @param b Boat pointer to put in the place
 * @param p Place pointer of the place which the boat is put
 */
void Port::putBoatInPlace(Boat* b, Place* p){
    // If the place is not available, boat instantiation impossible
    if(p->getTaken()){
        cerr << "Error : The place is taken." << endl;
        return;
    }
    // If the boat is a sailboat2, specific fasteningRing place is required
    if(b->getType()=="Sailboat2" && p->getLength()<25 && p->getType()=="FasteningRing Place"){
        cerr << "Error : Impossible to put the boat in the place." << endl;
        return;
    }
    p->setBoat(b);
    cout << "Request done." << endl;
}

/**
 * @brief Put to true the payed flag of the agreement
 * 
 * @param a Agreement pointer of the agreement which the payed flag will be changed
 */
void Port::putPayedAgreement(Agreement* a){
    a->putPayed();
}

/**
 * @brief Put to true the finished flag of all agreement finished
 * 
 * @param todaysDate Date pointer of the today's date
 */
void Port::putFinishedAgreement(Date* todaysDate){
    for(itAgreementsList = agreementsList.begin(); itAgreementsList!=agreementsList.end(); itAgreementsList++){
        if(*todaysDate > *(*itAgreementsList)->getStopDate() && (!(*itAgreementsList)->getFinished())){
            (*itAgreementsList)->putFinished();
        }
    }
}

/**
 * @brief Remove a boat of an user
 * 
 * @param b Boat pointer which is removed 
 */
void Port::removeBoatofUser(Boat* b){
    (getUserOfABoat(b)->getBoatsList()).remove(b);
}

/*  ------------------- GETTERS & SETTERS -------------------   */

list<Agreement*> Port::getAgreementsList(){
    return agreementsList;
}

list<Boat*> Port::getBoatsList(){
    return boatsList;
}

list<User*> Port::getUsersList(){
    return usersList;
}

list<Place*> Port::getPlacesList(){
    return placesList;
}

/**
 * @brief Get a boat by a registration
 * 
 * @param registration Registration value of the boat wanted
 * @return Boat pointer of the boat wanted
 */
Boat* Port::getBoat(string registration){
    for(itBoatsList = boatsList.begin(); itBoatsList != boatsList.end(); itBoatsList++){
        if((*itBoatsList)->getRegistration() == registration){
            return (*itBoatsList);
        }        
    }
    return NULL;
}

/**
 * @brief Get an agreement by an id given
 * 
 * @param agreementId Agreeement id value of the agreement wanted
 * @return Agreement pointer of the agreement wanted
 */
Agreement* Port::getAgreement(string agreementId){
    for(itAgreementsList = agreementsList.begin(); itAgreementsList!=agreementsList.end(); itAgreementsList++){
        if((*itAgreementsList)->getId() == agreementId){
            return (*itAgreementsList);
        }        
    }
    return NULL;
}

/**
 * @brief Get an agreement by user
 * 
 * @param user User pointer of the agreement wanted
 * @return Agreement pointer of the agreement wanted
 */
Agreement* Port::getAgreement(User* user){
    for(itAgreementsList = agreementsList.begin(); itAgreementsList!=agreementsList.end(); itAgreementsList++){
        if((*itAgreementsList)->getUser() == user){
            return (*itAgreementsList);
        }        
    }
    return NULL;
}

/**
 * @brief Get an User by id
 * 
 * @param id Id value of the user wanted
 * @return User pointer of the user wanted
 */
User* Port::getUser(string id){
    for(itUsersList = usersList.begin(); itUsersList != usersList.end(); ++itUsersList){
        if((*itUsersList)->getId() == id){
            return (*itUsersList);
        }        
    }
    return NULL;
}

/**
 * @brief Get place by id
 * 
 * @param id Id value of the place wanted
 * @return Place pointer of the place wanted
 */
Place* Port::getPlace(string id){
    for(itPlacesList = placesList.begin(); itPlacesList != placesList.end(); ++itPlacesList){
        if((*itPlacesList)->getId() == id){
            return (*itPlacesList);
        }        
    }
    return NULL;
}

/**
 * @brief Get a User by id
 * 
 * @param id Id value of the user wanted
 * @return User pointer of the user wanted
 */
User* Port::getUserById(string id){
    if(usersList.empty()){
        cerr << "Error : No users in the list.";
        return NULL;
    }
    else{
        for(itUsersList=usersList.begin(); itUsersList!=usersList.end(); itUsersList++){
            if((*itUsersList)->getId() == id){
                return (*itUsersList);
            }
        }
    }
    cerr << "Error : No user with the id '"+id+"'." << endl;
    return NULL;
}

/**
 * @brief Get User of a boat given
 * 
 * @param b Boat pointer which the user is wanted
 * @return User pointer of the user wanted
 */
User* Port::getUserOfABoat(Boat* b){
    for(itUsersList=usersList.begin(); itUsersList!=usersList.end(); itUsersList++){
        list<Boat*> boatsUserList = (*itUsersList)->getBoatsList();
        for(list<Boat*>::iterator it=boatsUserList.begin(); it!=boatsUserList.end(); it++){
            if((*it)==b)
                return (*itUsersList);
        }
    }
    return NULL;
}

/**
 * @brief Set the receipt id counter value to the id given
 * 
 * @param id Id value to put in the receipt id counter
 */
void Port::setReceiptIdCounter(string id){
    receiptIdCounter = id;
}

/**
 * @brief Set the user id counter value to the id given
 * 
 * @param id Id value to put in the user id counter
 */
void Port::setUserIdCounter(string id){
    userIdCounter = id;
}
/**
 * @brief Set the place id counter value to the id given
 * 
 * @param id Id value to put in the place id counter
 */
void Port::setPlaceIdCounter(string id){
    placeIdCounter = id;
}

/**
 * @brief Set the agreement id counter to the id given
 * 
 * @param id Id value to put in the agreement id counter
 */
void Port::setAgreementIdCounter(string id){
    agreementIdCounter = id;
}

/**
 * @brief Get the receipt Id counter
 * 
 * @return string receipt Id counter value
 */
string Port::getReceiptIdCounter(){
    return receiptIdCounter;
}