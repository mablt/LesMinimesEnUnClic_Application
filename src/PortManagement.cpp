/**
 * @file PortManagement.cpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "../headers/PortManagement.hpp"
#include "../headers/Sailboat1.hpp"
#include "../headers/Sailboat2.hpp"
#include "../headers/Deckboat.hpp"
#include "../headers/Agreement.hpp"
#include "../headers/Place.hpp"
#include "../headers/Mooring.hpp"
#include "../headers/FasteningRing.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*      --- Constructor ---     */
PortManagement::PortManagement(){
    portName = "Les Minimes";
    port = new Port();
    program = " \n\n\t\t### "+portName+"'s Port ###\n\n\t1.\tUser input.\n\t2.\tBoat input\t\n\t3.\tAgreement creation.\n\t4.\tGet available places.\n\t5.\tPut an agreement to payed.\n\t6.\tEdit receipts of the day.\n\t7.\tRe-edit an old receipt.\n\n\t0.\tQuit ";
    todaysDate = new Date();
}

/*      --- Destructor ---     */
PortManagement::~PortManagement(){
    port = NULL;
    todaysDate = NULL;
}


/*  ------------------- GETTERS & SETTERS -------------------   */

/**
 * @brief Display the program in the terminal
 * 
 */
void PortManagement::programDisplay(){
    bool continueDisplay = true;
    cout << " \n\n\t\t>>> "+portName+"'s Port <<<\n\n";
    cout << "Give the today's date" << endl;
    putTodaysDate();
    cout << "\t\t>>>Load Data<<<" << endl;
    bool dataLoaded = loadData();
    if(!dataLoaded)
        return;
    do
    {
        string userChoice;
        do
        {
            cout << program << endl << ">>> ";
            cin >> userChoice; 
            callFunction(userChoice);
        }while (userChoice != "0");
        string res; 
        cout << "Do you want to quit ? \nPress '0' to confirm or any key to cancel."<<endl<< ">>> ";
        cin >> res;
        if(res == "0"){
            cout << "\t\t>>>Save data<<<" << endl;
            saveData();
            cout << "Data saved." << endl;
            continueDisplay = false;
        }
        
    } while (continueDisplay);   
}

/**
 * @brief Display the available places of the port
 * 
 */
void PortManagement::placesAvailableDisplay(){
    list<Place*> placesAvailable = port->getAvailablePlaces();
    if(placesAvailable.empty()){
        cerr << "Error : No places loaded." << endl;
        return;
    }
    for(list<Place*>::iterator it=placesAvailable.begin(); it!=placesAvailable.end(); it++){
        if((*it)->getType() == "FasteningRing Place")
            cout << (*it)->getId() << " :\t" << (*it)->getType() << "\t" << (*it)->getLength() << " m." << endl;
        else
            cout << (*it)->getId() << " :\t" << (*it)->getType() << "\t" << endl;
    }
}

/**
 * @brief Do the call functions according to the user's choise
 * 
 * @param userChoice String value represents the user choice
 */
void PortManagement::callFunction(string userChoice){
    if(userChoice=="1")
        userCreation();
    else
        if(userChoice=="2")
            boatCreation();
        else
            if(userChoice=="3")
                agreementCreation();
            else
                if(userChoice=="4")
                    placesAvailableDisplay();
                else
                    if(userChoice=="5")
                        agreementPayed();
                    else
                        if(userChoice=="6")
                            editReceipts();
                        else
                            if(userChoice=="7")
                                reEditOldReceipt();
                            else
                                if(userChoice!="0")
                                    cerr << "Error : Invalid choice.";
}

/**
 * @brief Get the last agreement id counter presents in the file loaded
 * 
 * @param receiptNumbers List of the ids readed
 * @return string Value of the last agreement id counter
 */
string PortManagement::agreementIdCounterCalculator(list<string> receiptNumbers){
    string max;
    if(receiptNumbers.size() == 0)
        return "000000";
    for(list<string>::iterator it=receiptNumbers.begin(); it!=receiptNumbers.end();it++){
        if(max < (*it))
            max = *it;
    }
    return max;
}

/**
 * @brief Ask the today's date to the user
 * 
 */
void PortManagement::putTodaysDate(){
    todaysDate = port->dateInput();
    port->putFinishedAgreement(todaysDate);
}

/**
 * @brief Input to put the payed flag to true of an agreement
 * 
 * @return true if the request will be done
 * @return false if the request will not be done
 */
bool PortManagement::agreementPayed(){
    string agreementId;
    bool payedResponse;
    bool finishedResponse;
    cin >> agreementId;
    Agreement* a = port->getAgreement(agreementId);
    if (a==NULL) {
        cerr << "Error : User does not exists." << endl;
        return false;
    }
    port->putPayedAgreement(a);
    cout << "Change done." << endl;
}

/**
 * @brief Input for an user creation
 * 
 * @return User pointer of the user created
 */
User* PortManagement::userInput(){
    string firstName;
    string lastName;
    string address;
    string phone;
    string mail;
    list<Boat*> userBoatsList;
    string type;
    string res;
    cout << "Fisrt Name : " << endl <<">>> ";
    cin.ignore();
    getline(cin, firstName, '\n');
    cout << "Last Name : " << endl <<">>> ";
    cin.ignore();
    getline(cin, lastName, '\n');
    cout << "Address : " << endl <<">>> ";
    cin.ignore();
    getline(cin, address, '\n');
    cout << "Phone : " << endl <<">>> ";
    cin >> phone;
    cout << "Mail : " << endl <<">>> ";
    cin >> mail;
    cout << "Type ('Subscriber' or 'Visitor'): " << endl <<">>> ";
    cin >> type;
    if(type !="Visitor" && type !="Subscriber"){
        cerr << "Error : Invalid user type." << endl;
        return false;
    }
    if (type=="Subscriber"){
        Subscriber* s = port->createSubscriber(firstName, lastName, address, phone, mail, userBoatsList);
        port->addSubscriber(s);
        port-> addUser(s);
        return s;
    }
    else {
        if(type=="Visitor"){
            Visitor* v = port->createVisitor(firstName, lastName, address, phone, mail, userBoatsList);
            port-> addUser(v);
            return v;
        }
    }   
}

/**
 * @brief Input for a boat creation
 * 
 * @return Boat pointer of the boat created
 */
Boat* PortManagement::boatInput(){
    string registration, name, motor, type;
    Date* constructionDate;
    float length;
    float sailLength = NULL;
    int cabinNumber = NULL;
    cout << "Boat Registration : " << endl <<">>> ";
    cin.ignore();
    getline(cin, registration, '\n');
    cout << "Boat Name : " << endl <<">>> ";
    cin.ignore();
    getline(cin, name, '\n');
    cout << "Boat Motor informations: " << endl <<">>> ";
    cin.ignore();
    getline(cin, motor, '\n');
    cout << "Boat Construction Date : " << endl;
    constructionDate = port->dateInput();
    cout << "Boat Type ('Deckboat', 'Sailboat1' or 'Sailboat2') : " << endl <<">>> ";
    cin >> type;
    cout << "Boat Length (in m.) : " << endl <<">>> ";
    cin >> length;
    if (length<25 && type=="Sailboat2"){
        cerr << "Error : Invalid boat length for Sailboat2." << endl;
        return NULL;
    }
    if (length>25 && type=="Sailboat1"){
        cerr << "Error : Type and length of the boat are incoherents." << endl;
        return NULL;
    }
    if(type=="Deckboat" && length > 10){
        cerr << "Error : Type and length of the boat are incoherents." << endl;
        return NULL;
    }
    if(type=="Deckboat"){
        return new Deckboat(registration, name, motor, constructionDate, length);
    }
    else {
        if(type =="Sailboat1" || type=="Sailboat2"){
            cout << "Sail length (in m.) : " << endl <<">>> ";
            cin >> sailLength;
            cout << "Cabin number : " << endl <<">>> ";
            cin >> cabinNumber;
        }
        if(type =="Sailboat1"){
            return new Sailboat1(registration, name, motor, constructionDate, length, sailLength, cabinNumber);
        }
        else{
            if (type=="Sailboat2") {
                return new Sailboat2(registration, name, motor, constructionDate, length, sailLength, cabinNumber);
            }
            else{
                cerr << "Error : Invalid type name." << endl;
                return NULL;
            } 
        }
    }

}

/**
 * @brief Input for an agreement creation
 * 
 */
void PortManagement::agreementCreation(){
    Agreement* a;
    Boat* boat;
    User* user;
    Place* place;
    Date* startDate;
    int duration;
    string boatRegistration, userId, placeId, waterResponse, electricityResponse;
    bool water;
    bool electricity;
    cout << "Start date of the agreement : " << endl;
    startDate = port->dateInput();
    cout << "Boat Registration : " << endl <<">>> ";
    cin.ignore();
    getline(cin,boatRegistration);
    boat = port->getBoat(boatRegistration);
    if(boat==NULL){
        cerr << "Error : Invalid boat registration." << endl;
        return;
    }
    cout << "Place Id : " << endl <<">>> ";
    cin >> placeId;
    place = port->getPlace(placeId);
    if(place==NULL){
        cerr << "Error : Invalid place id." << endl;
        return;
    }
    if(place->getType()=="FasteningRing" && place->getLength()<boat->getLength()){
        cerr << "Error : Boat length and place length are incoherent." << endl;
    }
    if(place->getTaken()){
        cerr << "Error : Place taken." << endl;
        return;
    }    
    cout << "User Id : " << endl <<">>> ";
    cin >> userId;
    user = port->getUser(userId);
    if(user==NULL){
        cerr << "Error : Invalid user id." << endl;
        return;
    }
    if(user->getType()=="Visitor"){
        if(place->getType()=="FasteningRing Place"){
            cout << "Water desired : ('yes' or 'no)" << endl <<">>> ";
            cin >> waterResponse;
            if(waterResponse == "yes")
                water = true;
            else{
                if(waterResponse == "no")
                    water = false;
                else {
                    cerr << "Error : invalid water flag." << endl;
                    return;
                }
            }
            cout << "Electricity desired : ('yes' or 'no)" << endl <<">>> ";
            cin >> electricityResponse;
            if(electricityResponse == "yes")
                electricity = true;
            else{
                if(electricityResponse == "no")
                    electricity = false;
                else {
                    cerr << "Error : invalid electricity flag." << endl;
                    return;
                }
            }
        }
        cout << "Duration of the stay : " << endl <<">>> ";
        cin >> duration;
        a = port->createAgreement(boat, place, user, startDate, water, electricity, duration);
    }
    else{
        // If the day is not the fisrt of the month : error
        if(startDate->getDay() != 1){
            cerr << "Error : Invalid day." << endl;
            return;
        }
        a = port->createAgreement(boat, place, user, startDate);
    }
    port->addAgreement(a);
}

/**
 * @brief Edit the subscriber receipt for all finished agreements
 * 
 * @param todaysDate Today's date value
 * @param folderPath Folder path which the file will be created
 */
void PortManagement::editSubscriberReceipts(Date* todaysDate, string folderPath){
    int actualMonth = todaysDate->getMonth();
    list<Agreement*> agreementsList = port->getAgreementsList();
    for(list<Agreement*>::iterator it = agreementsList.begin(); it!=agreementsList.end(); it++){
        if((*it)->getType() == "Subscriber Agreement" && !((*it)->getFinished())){
            Receipt* r = port->createReceipt(todaysDate, (*it), folderPath, actualMonth);
            delete r;
        }
    }
}

/**
 * @brief Edit all the receipts for agreements which finished today
 * 
 */
void PortManagement::editReceipts(){
    string folderPath;
    cout << "Please, give the foler's path to stock the receipts." << endl << ">>> ";
    cin >> folderPath;
    list<Agreement*> agreementsList = port->getAgreementsList();
    for(list<Agreement*>::iterator it = agreementsList.begin(); it!=agreementsList.end(); it++){
        if(((*it)->getType()=="Visitor Agreement") && (*todaysDate == (*(*it)->getStopDate())) && (!(*it)->getFinished())){
            Receipt* r = port->createReceipt(todaysDate, (*it), folderPath);
            delete r;
        }
    }
    // If it is the first day of the month, edit the subscriber receipts
    if(todaysDate->getDay() == 1)
        editSubscriberReceipts(todaysDate, folderPath);
    cout << "Receipts creation done." << endl;
}

/**
 * @brief Re-edit an old receipt 
 * 
 */
void PortManagement::reEditOldReceipt(){
    string folderPath;
    string userId;
    int month=1;
    string receiptNumber;
    Receipt* r;
    cout << "Give the foler's path to stock the receipts." << endl << ">>> ";
    cin >> folderPath;
    cout << "Give the user Id." << endl << ">>> ";
    cin >> userId;
    User* u = port->getUserById(userId);
    if(u==NULL){
        cerr << "Error : Invalid user id." << endl;
        return;
    }
    if(u->getType()=="Subscriber"){
        cout << "Give the month of the receipt." << endl << ">>> ";
        cin >> month;
        
    }
    Agreement* a = port->getAgreement(u);
    receiptNumber =  a->getNumberReceiptFromMonth(month);
    if(receiptNumber == ""){
        cerr << "Error : Month invalid. No old receipt for this month." << endl;
        return;
    }
    cout << "Receipt nb recupr : "<<receiptNumber<<endl;
    r = new Receipt(receiptNumber,todaysDate, a, month);
    r->generateReceipt(folderPath);
    delete r;
    cout << "Receipt creation done." << endl;
}

/**
 * @brief Input for the data loading
 * 
 */
bool PortManagement::loadData(){
    string boatsFile, placesFile, usersFile, agreementFile;
    bool boatsFileLoaded, placesFileLoaded, usersFileLoaded, agreementsFileLoaded;
    cout << "Give the file contains Boats' data : " << endl << ">>> ";
    cin >> boatsFile;
    boatsFileLoaded = loadBoats(boatsFile);
    if(!boatsFileLoaded)
        return false;
    cout << "Give the file contains Places' data : " << endl << ">>> ";
    cin >> placesFile;
    placesFileLoaded = loadPlaces(placesFile);
    if(!placesFileLoaded)
        return false;
    cout << "Give the file contains Users' data : " << endl << ">>> ";
    cin >> usersFile;
    usersFileLoaded = loadUsers(usersFile);
    if(!usersFileLoaded)
        return false;
    cout << "Give the file contains Agreements' data : " << endl << ">>> ";
    cin >> agreementFile;
    agreementsFileLoaded = loadAgreements(agreementFile);
    if(!agreementsFileLoaded)
        return false;
    return true;
}

/**
 * @brief Load the file contains the places' data
 * 
 * @param fileName Name of the file
 * @return true if the loading will be effectued
 * @return false if the loading failed
 */
bool PortManagement::loadPlaces(string fileName){
    ifstream file(fileName);
    if(file.eof()){
        port->setPlaceIdCounter("P00000");
        cout << "File loaded."<<endl;
        return true;
    }
    if(file){
        string line, lastPlaceId;
        while(getline(file, line)){
            vector<string> data;
            string info;
            stringstream ss(line);
            string placeId, type;
            bool taken;
            float length;
            Boat* boat;
            while(getline(ss, info, ';')){
                data.push_back(info);
            }
            placeId = data.at(0);
            lastPlaceId = placeId;
            type = data.at(1);
            if(data.at(3) == "1"){
                taken = true;
                boat = port->getBoat(data.at(4));
            }
            else
                taken = false;            
            if(type == "Mooring Place")
                port->addPlace(new Mooring(placeId, taken, boat));
            else{
                length = stof(data.at(2));
                FasteningRing* f = new FasteningRing(placeId, taken, boat, length);
                port->addPlace(f);
            }
        }
        // Incremente the placeIdCounter by the last Id presents in the file
        port->setPlaceIdCounter(lastPlaceId);
    }
    else{
        cerr << "Error : Invalid file." << endl;
        return false;
    }
    cout << "File loaded." << endl;
    return true;
}



/**
 * @brief Load the file contains the boats' data
 * 
 * @param fileName Name of the file
 * @return true if the loading will be effectued
 * @return false if the loading failed
 */
bool PortManagement::loadBoats(string fileName){
    ifstream file(fileName);
    if(file){
        string line;
        while(getline(file, line)){
            vector<string> data;
            string info;
            stringstream ss(line);
            string registration, type, name, motor;
            Date* constructionDate;
            float boatLength, sailLength;
            int cabinNumber;
            while(getline(ss, info, ';')){
                data.push_back(info);
            }
            registration = data.at(0);
            type = data.at(1);
            name = data.at(2);
            motor = data.at(4);
            constructionDate = new Date(data.at(5));
            boatLength = stof(data.at(6));
            if(type != "Deckboat"){
                sailLength = stof(data.at(7));
                cabinNumber = stoi(data.at(8));
                if(type == "Sailboat1")
                    port->addBoat(new Sailboat1(registration, name, motor, constructionDate, boatLength, sailLength, cabinNumber));
                else
                    port->addBoat(new Sailboat2(registration, name, motor, constructionDate, boatLength, sailLength, cabinNumber));
            }
            else
                port->addBoat(new Deckboat(registration, name, motor, constructionDate, boatLength));
        }
    }
    else{
        cerr << "Error : Invalid file." << endl;
        return false;
    }
    cout << "File loaded." << endl;
    return true;
}

/**
 * @brief Load the file contains the users' data
 * 
 * @param fileName Name of the file
 * @return true if the loading will be effectued
 * @return false if the loading failed
 */
bool PortManagement::loadUsers(string fileName){
    ifstream file(fileName);
    if(file.eof()){
        port->setUserIdCounter("U00000");
        cout << "File loaded."<<endl;
        return true;
    }
    if(file){
        string line;
        string lastUserId;
        while(getline(file, line)){
            vector<string> data;
            string info;
            stringstream ss(line);
            string userId, type, firstName, lastName, address, phone, mail;
            int boatsNumber;
            string nb;
            list<Boat*> boatsList;
            while(getline(ss, info, ';')){
                data.push_back(info);
            }
            userId = data.at(0);
            lastUserId = userId;
            type = data.at(1);
            firstName = data.at(2);
            lastName = data.at(3);
            address = data.at(4);
            phone = data.at(5);
            mail = data.at(6);
            boatsNumber = stoi(data.at(7));
            for(int i=1; i<=boatsNumber; i++){
                string registration = data.at((7+i));
                boatsList.push_back(port->getBoat(registration));
            }
            Boat* gg = boatsList.front();
            if(type == "Subscriber"){
                port->addSubscriber(new Subscriber(userId, firstName, lastName, address, phone, mail, boatsList));
                port->addUser(new Subscriber(userId, firstName, lastName, address, phone, mail, boatsList));
            } 
            else
                port->addUser(new Visitor(userId, firstName, lastName, address, phone, mail, boatsList));
        }
        // Incremente the userIdCounter by the last Id presents in the file
        port->setUserIdCounter(lastUserId); 
    }
    else{
        cerr << "Error : Invalid file." << endl;
        return false;
    }
    cout << "File loaded." << endl;
    return true;
}


/**
 * @brief Load the file contains the agreements' data
 * 
 * @param fileName Name of the file
 * @return true if the loading will be effectued
 * @return false if the loading failed
 */
bool PortManagement::loadAgreements(string fileName){
    ifstream file(fileName);
    //If the file is empty
    if(file.eof()){
        port->setAgreementIdCounter("A00000");
        cout << "File loaded."<<endl;
        return true;
    }
    if(file){
        string line, lastAgreementId;
        int lineNumber = 0;
        list<string> receiptNumbers;
        while(getline(file, line)){
            cout << "AGGG +++++++++++++++++++++++++++++++++++++++++++++\n";
            if (lineNumber == 1){
                port->setReceiptIdCounter(line);
                continue;
            }
            vector<string> data;
            string info;
            stringstream ss(line);
            string agreementId, type, boatRegistration, userId, placeId, startDateString, inforNumberReceipt;
            int numberOfReceipt, duration;
            bool water = false;
            bool electricity = false;
            bool payed = false;
            bool finished = false;
            map<int, string> numberReceiptMap;
            
            
            while(getline(ss, info, ';')){
                data.push_back(info);
            }
            agreementId = data.at(0);
            lastAgreementId = agreementId;
            type = data.at(1);
            boatRegistration = data.at(2);
            userId = data.at(3);
            placeId = data.at(4);
            startDateString = data.at(5);
            numberOfReceipt = stoi(data.at(6));
            inforNumberReceipt = data.at(7);
            if(data.at(8) == "1")
                payed = true;
            if(data.at(9) == "1")
                finished = true;
            if(numberOfReceipt > 0 ){
                vector<string> allMonths;
                string monthInfo;
                stringstream strStream(inforNumberReceipt);
                while(getline(strStream, monthInfo, ',')){
                    allMonths.push_back(monthInfo);
                }
                               
                for (string monthI : allMonths){
                    string monthNumber;
                    string receiptNumber; 
                    vector<string> data;
                    stringstream strStream2(monthI);
                    string info;

                    while(getline(strStream2, info, ':')){
                        data.push_back(info);
                    }
                    monthNumber = data.at(0);
                    receiptNumber = data.at(1);
                    cout << "RECIPT NUMBER ADDDED TO THE MAP :: "<<receiptNumber<<endl;
                    numberReceiptMap[stoi(monthNumber)] = receiptNumber;
                    if(receiptNumber != "")
                        receiptNumbers.push_back(receiptNumber);
                }
            }
            if(type == "Visitor Agreement"){
                string s = data.at(10);
                duration = stoi(s);
                if(data.at(11) == "1")
                    water = true;
                if(data.at(12) == "1")
                    electricity = true;
                port->addAgreement(new Agreement(agreementId, port->getBoat(boatRegistration), port->getUser(userId), port->getPlace(placeId), water, electricity, new Date(startDateString), numberReceiptMap, duration, payed, finished));
            }
            else
                port->addAgreement(new Agreement(agreementId, port->getBoat(boatRegistration), port->getUser(userId), port->getPlace(placeId), new Date(startDateString), numberReceiptMap, payed, finished));
        }
        // Put Ids of the last agreement created and the last receipt created
        port->setAgreementIdCounter(lastAgreementId);
        port->setReceiptIdCounter(agreementIdCounterCalculator(receiptNumbers));
    }
    else{
        cerr << "Error : Invalid file." << endl;
        return false;
    }
    cout << "File loaded." << endl;
    return true;
}        



/**
 * @brief Input for the data saving
 * 
 */
void PortManagement::saveData(){
    string boatsFile, placesFile, usersFile, agreementsFile;
    bool boatsFileSaved, placesFileSaved, usersFileSaved, agreementsFileSaved;
    cout << "Give the file name to save Boats' data : " << endl << ">>> ";
    cin >> boatsFile;
    boatsFileSaved = saveBoats(boatsFile);
    if(!boatsFileSaved)
        return;
    cout << "Give the file name to save Places' data : " << endl << ">>> ";
    cin >> placesFile;
    placesFileSaved = savePlaces(placesFile);
    if(!placesFileSaved)
        return;
    cout << "Give the file name to save Users' data : " << endl << ">>> ";
    cin >> usersFile;
    usersFileSaved = saveUsers(usersFile);
    if(!usersFileSaved)
        return;
    cout << "Give the file name to save Agreements' data : " << endl << ">>> ";
    cin >> agreementsFile;
    agreementsFileSaved = saveAgreements(agreementsFile);
    if(!agreementsFileSaved)
        return;
}

/**
 * @brief Save the boats' data in a file
 * 
 * @param nameFile Name file to create
 * @return true if the saving will be done
 * @return false if the saving failed
 */
bool PortManagement::saveBoats(string nameFile){
    ofstream file(nameFile);
    if(file){
        list<Boat*> boatsList = port->getBoatsList();
        for(list<Boat*>::iterator it=boatsList.begin(); it!=boatsList.end(); it++){
            string registration = (*it)->getRegistration();
            string name = (*it)->getName();
            string type = (*it)->getType();
            string propulsion = (*it)->getPropulsion();
            string motor = (*it)->getMotor();
            string constructionDate = (*it)->getConstructionDate()->getDate();
            string length = to_string((*it)->getLength());
            string sailLength, cabinNumber;
            if(type != "Deckboat"){
                sailLength = to_string((*it)->getSailLength());
                cabinNumber = to_string((*it)->getCabinNumber());
                file << registration << ";" << type << ";" << name << ";" << propulsion << ";" << motor << ";" << constructionDate << ";" << length << ";" << sailLength << ";" << cabinNumber << endl;
            }
            else
                file << registration << ";" << type << ";" << name << ";" << propulsion << ";" << motor << ";" << constructionDate << ";" << length << endl;
        }
    }
    else{
        cerr << "Error : File creation impossible." << endl;
        return false;
    }
    cout << "Boats data saved." << endl;
    return true;
}


/**
 * @brief Save places' data in a file
 * 
 * @param nameFile Name file to create
 * @return true if the saving will be done
 * @return false if the saving failed
 */
bool PortManagement::savePlaces(string nameFile){
    ofstream file(nameFile);
    if(file){
        list<Place*> placesList = port->getPlacesList();
        for(list<Place*>::iterator it=placesList.begin(); it!=placesList.end(); it++){
            string placeId = (*it)->getId();
            string type = (*it)->getType();
            string length = to_string((*it)->getLength());
            bool taken = false;
            string boatRegistration;
            if((*it)->getTaken()){
                taken = true;
                boatRegistration = (*it)->getBoat()->getRegistration();
                file << placeId << ";" << type << ";" << length << ";" << taken << ";" << boatRegistration << endl;
            }
            else
                file << placeId << ";" << type << ";" << length << ";" << taken << endl;
        }
    }
    else{
        cerr << "Error : File creation impossible." << endl;
        return false;
    }
    cout << "Places data saved." << endl;
    return true;
}

/**
 * @brief Save the users' data in a file
 * 
 * @param nameFile Name file to create
 * @return true if the saving will be done
 * @return false if the saving failed
 */
bool PortManagement::saveUsers(string nameFile){
    ofstream file(nameFile);
    if(file){
        list<User*> usersList = port->getUsersList();
        for(list<User*>::iterator it=usersList.begin(); it!=usersList.end(); it++){
            string userId = (*it)->getId();
            string type = (*it)->getType();
            string firstName = (*it)->getFirstName();
            string lastName = (*it)->getLastName();
            string address = (*it)->getAddress();
            string phone = (*it)->getPhone();
            string mail = (*it)->getMail();
            list<Boat*> boatsList = (*it)->getBoatsList();
            int boatNumber = boatsList.size();
            string boatsRegistrations;
            Boat* gg = boatsList.front();
            for(list<Boat*>::iterator it2=boatsList.begin(); it2!=boatsList.end(); it2++){
                boatsRegistrations += string((*it2)->getRegistration());
                boatsRegistrations += ";";
            }
            // Remove the last character which contains a ';' not desired
            boatsRegistrations.pop_back();
            file << userId << ";" << type << ";" << firstName << ";" << lastName << ";" << address << ";" << phone << ";" << mail << ";" << boatNumber << ";" << boatsRegistrations << endl;
        }
    }
    else{
        cerr << "Error : File creation impossible." << endl;
        return false;
    }
    cout << "Users data saved." << endl;
    return true;
}

/**
 * @brief Save the agreements' data in a file   
 * 
 * @param nameFile Name file to create
 * @return true if the saving will be done
 * @return false if the saving failed
 */
bool PortManagement::saveAgreements(string nameFile){
    ofstream file(nameFile);
    if(file){
        list<Agreement*> agreementsList = port->getAgreementsList();
        for(list<Agreement*>::iterator it=agreementsList.begin(); it!=agreementsList.end(); it++){
            string agreementId = (*it)->getId();
            string type = (*it)->getType();
            Boat* boat = (*it)->getBoat();
            User* user = (*it)->getUser();
            Place* place = (*it)->getPlace();
            Date* startDate = (*it)->getStartDate();
            bool payed = (*it)->getPayed();
            bool finished = (*it)->getFinished();            
            map<int, string> numbersReceiptMap = (*it)->getReceiptNumbersMap();
            string receiptsNumberInfos;
            int receiptsNumber = numbersReceiptMap.size();
            if(receiptsNumber == 0)
                receiptsNumberInfos = ";";
            for(map<int, string>::iterator it2=numbersReceiptMap.begin(); it2!=numbersReceiptMap.end(); it2++){
                receiptsNumberInfos += to_string(it2->first);
                receiptsNumberInfos += ":";
                receiptsNumberInfos += it2->second;
                receiptsNumberInfos += ",";
            }
            // Remove the last character which contains a ';' not desired
            receiptsNumberInfos.pop_back();
            if(type == "Visitor Agreement"){
                int duration = (*it)->getDuration();                
                bool water = (*it)->getWater();
                bool electricity = (*it)->getElectricity();
                file << agreementId << ";" << type << ";" << boat->getRegistration() << ";" << user->getId() << ";" << place->getId() << ";" << startDate->getDate() << ";" << receiptsNumber << ";" << receiptsNumberInfos << ";" << payed << ";" << finished << ";" << duration << ";" << water << ";" << electricity << endl;
            }
            else
                file << agreementId << ";" << type << ";" << boat->getRegistration() << ";" << user->getId() << ";" << place->getId() << ";" << startDate->getDate() << ";" << receiptsNumber << ";" << receiptsNumberInfos << ";" << payed << ";" << finished << endl;
        }
    }
    else{
        cerr << "Error : File creation impossible." << endl;
        return false;
    }
    cout << "Agreements data saved." << endl;
    return true;
}

/**
 * @brief Create a boat and check the user
 * 
 */
void PortManagement::boatCreation(){
    string alreadyExistingUser;
    User* u;
    Boat* b = boatInput();
    if(b == NULL)
        return;
    port->addBoat(b);
    cout << "Already existing user ('yes' or 'no') :" << endl << ">>> ";
    cin >> alreadyExistingUser;
    if(alreadyExistingUser!="yes" && alreadyExistingUser!="no"){
        cerr << "Error : Invalid response." << endl;
        return;
    }
    if(alreadyExistingUser == "yes"){
        string userId;
        cout << "Give the user id :" << endl << ">>> ";
        cin >> userId;
        u = port->getUserById(userId);
        if(u == NULL){
            cerr << "Error : User does not exist." << endl;
            return;
        }
        u->addBoat(b);
        cout << "Boat created." << endl;
    }
    else{
        u = userInput();
        if(u == NULL)
            return;
        u->addBoat(b);
        cout << "Boat created." << endl << "User created." << endl;
    }
}

/**
 * @brief Create an user and attribute a boat to this user
 * 
 */
void PortManagement::userCreation(){
    string alreadyExistingBoat;
    User* u = userInput();
    Boat* b;
    port->addUser(u);
    cout << "Already existing boat ('yes' or 'no') :" << endl << ">>> ";
    cin >> alreadyExistingBoat;
    if(alreadyExistingBoat!="yes" && alreadyExistingBoat!="no"){
        cerr << "Error : Invalid response." << endl;
        return;
    }
    if(alreadyExistingBoat == "yes"){
        string boatRegistration;
        cout << "Give the boat registration :" << endl << ">>> ";
        cin.ignore();
        getline(cin,boatRegistration);
        b = port->getBoat(boatRegistration);
        if(b == NULL){
            cerr << "Error : Boat does not exist." << endl;
            return;
        }
        u->addBoat(b);
        cout << "Boat added to the user." << endl;
    }
    else{
        b = boatInput();
        if(b==NULL)
            return;
        u->addBoat(b);
        cout << "Boat created and added to the user." << endl;
    }
}
