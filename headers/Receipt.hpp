/**
 * @file Receipt.hpp
 * @author Mathieu BOLTEAU | mathieu.bolteau1@gmail.com | GitHub @mablt
 * @brief "Les Minimes en un clic" application
 * @version 0.1
 * @date 2020-04-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __RECEIPT_HPP__
#define __RECEIPT_HPP__
#include "Date.hpp"
#include "Agreement.hpp"
#include <string>
#include <iostream>
#include <fstream>

class Receipt
{
private:
    std::string number;
    Date* date;
    Agreement* agreement;
    int month;
public:
    Receipt(std::string, Date*, Agreement*, int=NULL);
    ~Receipt();
    void generateReceipt(std::string);
};

#endif