//
//  AdvisorMain.hpp
//  Advisorbot
//
//  Created by Ahmed Shaban on 9.06.2022.
//

#ifndef AdvisorMain_hpp
#define AdvisorMain_hpp

#include <stdio.h>
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
    void printHelpCmd();
    void printProd();
    void printMin();
    void printMax();
    void printAvg();
    void predict();
    void gotoNextTimeframe();
    
    std::string currentTime;
};

#endif /* AdvisorMain_hpp */
