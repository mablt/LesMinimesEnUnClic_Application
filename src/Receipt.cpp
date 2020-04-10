/**
 * @file Receipt.cpp
 * @author Mathieu BOLTEAU (mathieu.bolteau1@gmail.com)
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "../headers/Receipt.hpp"
#include <string>
using namespace std;

static float ANNUAL_SUBSCRIBER_PRICE = 500;
static float DAY_VISTOR_PRICE = 20;
static float WATER_PRICE = 5;
static float ELECTRICITY_PRICE = 5;

/*      --- Constructor ---     */
Receipt::Receipt(string _number, Date* _date, Agreement* _agreement, int _month)
{
    number = _number;
    date = _date;
    agreement = _agreement;
    month = _month;
}

/*      --- Destructor ---     */
Receipt::~Receipt(){
    date = NULL;
    agreement = NULL;
}

/*  ------------------- METHODS -------------------   */
/**
 * @brief Generate the receipt and create a file which contains all informations of this one
 * 
 * @param folderPath Folder path which the file will be created
 */
void Receipt::generateReceipt(string folderPath){
    string nameFile = "Receipt_"+number+".txt";
    ofstream file(folderPath+nameFile, ios::out | ios::trunc);
    if(file){
        map<string, string> stringAgreement = agreement->toString();
        string quantityType;
        string quantityNumber;
        float totalPrice = agreement->getPrice();
        float dayOrMonthPrice = totalPrice;
        bool supplementaryFacts = false;
        bool waterSupplementary = false;
        bool electricitySuppementary = false;
        string duration = stringAgreement["duration"];

        if(stringAgreement["agreementType"] == "Subscriber Agreement"){
            quantityType = "Price /month";
            totalPrice /=12;
        }
        else{
            dayOrMonthPrice /= stof(duration);
            quantityType = "Price /day";
            quantityNumber = "Quantity";
            if(stringAgreement["placeType"] == "FasteningRing Place"){
                if(stringAgreement["agreementWater"] == "1"){
                    waterSupplementary = true;
                    dayOrMonthPrice -= WATER_PRICE;
                }
                if(stringAgreement["agreementElectricity"] == "1"){
                    electricitySuppementary = true;
                    dayOrMonthPrice -= ELECTRICITY_PRICE;
                }
                if(waterSupplementary || electricitySuppementary){
                    supplementaryFacts = true;
                }
            }
        }

        Date d = *date;
        file << string(81, '#') << endl;
        file << "#"+string(20, '\t')+"#" << endl;
        file << "#"+string(9, '\t')+"RECEIPT "+number+string(8, '\t')+"#" << endl;
        file << "#"+string(20, '\t')+"#" << endl;
        file << string(81, '#') << endl;
        file << "\n\n"+string(12, '\t')+d.getDate() << endl;
        file << "\n\n"+string(12, '\t')+stringAgreement["userFirstName"] << " " << stringAgreement["userLastName"] << endl;
        file << string(12, '\t') << stringAgreement["userAddress"] << endl;

        file << "\n\n" << string(81, '-') << endl;
        file << "\tUser ID : " << stringAgreement["userId"] << endl;
        file << "\tAgreement ID : " << stringAgreement["agreementId"] << endl;
        file << "\tAgreement type : " << stringAgreement["agreementType"] << endl;
        

        if(stringAgreement["agreementType"] == "Subscriber Agreement"){
            if((month-1)==0)
                file << "\tMonth : " << "12" << endl;
            else
                file << "\tMonth : " << month-1 << endl;
            file << string(81, '-') << endl;
            file << string(10, '\t') << quantityType <<string(3, '\t') << quantityNumber << endl;
            file << "\t*Place informations*\t" << endl;
            file << "\tId : " << stringAgreement["placeId"] << endl;
            file << "\tType : " << stringAgreement["placeType"] << endl;
            file << "\n\n" << endl;
            file << "\t*Boat informations*\t" << endl;
            file << "\t" << stringAgreement["boatRegistration"] << endl;
            file << "\t" << stringAgreement["boatName"] << endl;
            file << "\t" << stringAgreement["boatPropulsion"] << " - "<< stoi(stringAgreement["boatLength"]) << " m." << endl;
            file << string(10, '\t') << totalPrice << " €" << endl;
        }
        else {
            file << string(81, '-') << endl;
            file << string(10, '\t') << quantityType <<string(3, '\t') << quantityNumber << endl;
            if(stringAgreement["placeType"] == "Mooring Place"){
                file << "\t*Place informations*\t" << endl;
                file << "\tId : " << stringAgreement["placeId"] << endl;
                file << "\tType : " << stringAgreement["placeType"] << endl;
                file << "\n\n" << endl;
                file << "\t*Boat informations*\t" << endl;
                file << "\t" << stringAgreement["boatRegistration"] << endl;
                file << "\t" << stringAgreement["boatName"] << endl;
                file << "\t" << stringAgreement["boatPropulsion"] << " - "<< stoi(stringAgreement["boatLength"]) << " m." << endl;
                file << string(10, '\t') << dayOrMonthPrice << " €" << string(4, '\t') << duration << endl;
            }
            else{
                
                file << "\t*Place informations*\t" << endl;
                file << "\tId : " << stringAgreement["placeId"] << endl;
                file << "\tType : " << stringAgreement["placeType"] << endl;
                file << "\n\n" << endl;
                file << "\t*Boat informations*\t" << endl;
                file << "\t" << stringAgreement["boatRegistration"] << endl;
                file << "\t" << stringAgreement["boatName"] << endl;
                file << "\t" << stringAgreement["boatPropulsion"] << " - "<< stoi(stringAgreement["boatLength"]) << " m." << endl;
                file << string(10, '\t') << dayOrMonthPrice << " €" << string(4, '\t') << duration << endl;
                if(supplementaryFacts){
                    file << "\t*Supplementary*\t" << endl;
                    if(waterSupplementary)
                        file << "\tWater" << string(8, '\t') << to_string(WATER_PRICE) << " €" << string(5, '\t') << duration << endl;
                    if(electricitySuppementary)
                        file << "\tElectricity" << string(7, '\t') << to_string(ELECTRICITY_PRICE) << " €" << string(5, '\t') << duration << endl;
                }

            }
            
        }

    
        file << "\n\n\n" << endl;
        file << string(81, '-') << endl;
        file << string(12, '\t') << "TOTAL : " << totalPrice<< " €" << endl;

        file.close();
    }
    else
        cerr << "Creation of '"+nameFile+ "' file impossible. " << endl;
}
