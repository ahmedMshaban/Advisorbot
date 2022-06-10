//
//  AdvisorMain.cpp
//  Advisorbot
//
//  Created by Ahmed Shaban on 9.06.2022.
//

#include "AdvisorMain.hpp"
#include "CSVReader.hpp"
#include <iostream>

AdvisorMain::AdvisorMain() {
    
}

void AdvisorMain::init() {
    
    std::string input;
    printMenu();
    while(true) {
        input = getUserOption();
        processUserOption(input);
    }
    
}

// Lists all available commands.
void AdvisorMain::printMenu() {
    
    std::cout << "============== " << std::endl;
    // list all available commands
    std::cout << "help " << std::endl;
    // output help for the specified command
    std::cout << "help <command> " << std::endl;
    // list available products
    std::cout << "prod " << std::endl;
    // find minimum bid or ask for product in current time step
    std::cout << "min <product> <ask/bid> " << std::endl;
    // find maximum bid or ask for product in current time step
    std::cout << "max <product> <ask/bid> " << std::endl;
    // compute average ask or bid for the sent product over the sent number
    std::cout << "avg <product> <ask/bid> <steps> " << std::endl;
    // predict max or min ask or bid for the sent product for the next time
    std::cout << "predict <product> <ask/bid> " << std::endl;
    // state current time in dataset, i.e. which timeframe are we looking at
    std::cout << "time " << std::endl;
    // move to next time step
    std::cout << "step " << std::endl;
    
    std::cout << "============== " << std::endl;
}

// Get user option
std::string AdvisorMain::getUserOption() {
    
    std::string userOption;
    std::string line;
    
    std::cout << "Type in one of the commands from the menu." << std::endl;
    std::getline(std::cin, line);
    
    try {
        userOption = line;
    }
    catch(const std::exception& e) {
        std::cout << "Error with input." << std::endl;
    }
    
    std::cout << "==============" << std::endl;
    std::cout << "You chose: " << userOption << std::endl;
    
    return userOption;
}

void AdvisorMain::processUserOption(std::string userOption) {
    
    std::vector<std::string> tokens = CSVReader::tokenise(userOption, ' ');
    
    if (userOption.find("help") != std::string::npos && tokens[0] == "help") {
        if (tokens.size() == 1 && userOption == "help")
        {
            std::cout << "Here is a list of all available commands:" << std::endl;
            printMenu();
        }
        else {
            printHelpCmd();
        }
    }
    
    else if (userOption == "prod" ) {
        printProd();
    }
    
    else if (userOption == "min") {
        printMin();
    }
    
    else if (userOption == "max") {
        printMax();
    }
    
    else if (userOption == "avg") {
        printAvg();
    }
    
    else if (userOption == "predict") {
        predict();
    }
    
    else if (userOption == "time") {
        std::cout << "Current time is:  " << currentTime << std::endl;
    }
    
    else if (userOption == "step") {
        gotoNextTimeframe();
    }
    
    else { // bad input
        std::cout << "Bad input, please enter one of the command below" << std::endl;
    }
}

void AdvisorMain::printHelpCmd() {
    std::cout << "Help will be here " << std::endl;
}

void AdvisorMain::printProd() {
    std::cout << "product list will be here " << std::endl;
    
}

void AdvisorMain::printMin() {
    std::cout << "min will be here " << std::endl;
    
}

void AdvisorMain::printMax() {
    std::cout << "max will be here " << std::endl;
    
}

void AdvisorMain::printAvg() {
    std::cout << "avg will be here " << std::endl;
    
}

void AdvisorMain::predict() {
    std::cout << "predict will be here " << std::endl;
    
}

void AdvisorMain::gotoNextTimeframe() {
    std::cout << "time frame will be here " << std::endl;
    
}
