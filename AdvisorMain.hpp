//
//  AdvisorMain.hpp
//  Advisorbot
//
//  Created by Ahmed Shaban on 9.06.2022.
//

#ifndef AdvisorMain_hpp
#define AdvisorMain_hpp

#include <stdio.h>
#include "OrderBook.hpp"
#include <string>
#include <vector>

class AdvisorMain {
public:
    AdvisorMain();
    /** Call this to start the sim */
    void init();
private:
    void printMenu();
    std::string getUserOption();
    void processUserOption(std::string userOption);
    void printHelpCmd(const std::vector<std::string>& tokens);
    void printProd();
    void printMin(const std::vector<std::string>& tokens);
    void printMax(const std::vector<std::string>& tokens);
    void printAvg(const std::vector<std::string>& tokens);
    void predict(const std::vector<std::string>& tokens);
    void gotoNextTimeframe();
    bool commandValidator(const std::vector<std::string>& tokens);
    
    OrderBook orderBook{"20200601.csv"};
    std::string currentTime;
};

#endif /* AdvisorMain_hpp */
