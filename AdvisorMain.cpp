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

/** */
void AdvisorMain::init() {
    
    std::string input;
    currentTime = orderBook.getEarliestTime();
    currentTimeIndex = 0;
    printMenu();
    
    while(true) {
        input = getUserOption();
        processUserOption(input);
        std::cout << "==============" << std::endl;
    }
    
}

/** Lists all available commands. */
void AdvisorMain::printMenu() {
    
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
    
    std::cout << "==============" << std::endl;
    
}

/** Perform a basic check on user input and return it */
std::string AdvisorMain::getUserOption() {
    
    // A default value in case something went wrong
    std::string userOption = "Error with input.";
    std::string line;
    
    std::cout << "Type in one of the commands from the menu." << std::endl;
    
    if(std::getline(std::cin, line)) {
        
        if(line == "")  {
            userOption = "Pressed enter without typing anything";
        }
        
        else {
            // Go through all avaliable commands
            for (std::string const& command : avaliableCommands) {
                // Check if the user input contains any of the available commands
                if(line.find(command) != std::string::npos) {
                    userOption = line;
                    break;
                }
            }
        }
    }
    
    std::cout << "==============" << std::endl;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

/** Figurout the user input related to which command. */
void AdvisorMain::processUserOption(std::string userOption) {
    
    std::vector<std::string> tokens = CSVReader::tokenise(userOption, ' ');
    // Command Name refer to first index of the user option help, min, max, etc..
    std::string commandName = tokens[0];
    
    if (userOption.find("help") != std::string::npos && commandName == "help") {
        
        if (tokens.size() == 1 && userOption == "help")
        {
            std::cout << "Here is a list of available commands:" << std::endl;
            std::cout << "============== " << std::endl;
            printMenu();
        }
        
        else {
            printHelpCmd(tokens);
        }
        
    }
    
    else if (userOption == "prod" ) {
        printProd();
    }
    
    else if (commandName == "min") {
        printMin(tokens);
    }
    
    else if (commandName == "max") {
        printMax(tokens);
    }
    
    else if (commandName == "avg") {
        printAvg(tokens);
    }
    
    else if (userOption.find("predict") != std::string::npos) {
        predict(tokens);
    }
    
    else if (userOption == "time") {
        std::cout << "Current time at:  " << currentTime << std::endl;
    }
    
    else if (userOption == "step") {
        gotoNextTimeframe();
    }
    
    else { // bad input
        std::cout << "Bad input, please enter a valid command use help <command> to see valid uses." << std::endl;
    }

}

/** Print more info about each of the available commands and how to use them. */
void AdvisorMain::printHelpCmd(const std::vector<std::string>& tokens) {
    // One of the available commands help, time, etc..
    std::string commandName = tokens[1];

    
    if(tokens.size() == 2 && commanNameIsValid(commandName, avaliableCommands)) {
        if(commandName == "help") {
            std::cout << "Purpose: list all available commands" << std::endl;
            std::cout << "Example: help" << std::endl;
        }
        
        else if(commandName == "prod") {
            std::cout << "Purpose: list available products" << std::endl;
            std::cout << "Example: prod" << std::endl;
        }
        
        else if(commandName == "min") {
            std::cout << "Purpose: find minimum bid or ask for product in current time step" << std::endl;
            std::cout << "parameters: <product> , <bid/ask>" << std::endl;
            std::cout << "Example: min ETH/BTC ask" << std::endl;
        }
        
        else if(commandName == "max") {
            std::cout << "Purpose: find maximum bid or ask for product in current time step" << std::endl;
            std::cout << "parameters: <product> , <bid/ask>" << std::endl;
            std::cout << "Example: max ETH/BTC bid" << std::endl;
        }
        
        else if(commandName == "avg") {
            std::cout << "Purpose: compute average ask or bid for the sent product  from the last N time steps." << std::endl;
            std::cout << "parameters: <product> , <bid/ask> , <steps>" << std::endl;
            std::cout << "Example: avg ETH/BTC ask 10" << std::endl;
        }
        
        else if(commandName == "predict") {
            std::cout << "Purpose: predict max or min ask or bid for the sent product for the next time step" << std::endl;
            std::cout << "parameters: <max/min> , <product> , <bid/ask>" << std::endl;
            std::cout << "Example: predict max ETH/BTC bid" << std::endl;
        }
        
        else if(commandName == "time") {
            std::cout << "Purpose: state current time in dataset, i.e. which timeframe are we looking at" << std::endl;
            std::cout << "Example: time" << std::endl;
        }
        
        else if(commandName == "step") {
            std::cout << "Purpose: move to next time step" << std::endl;
            std::cout << "Example: step" << std::endl;
        }
    }
    
    else { // bad input
        std::cout << "Invalid input, use 'help <command>' for more inforamtion." << std::endl;
    }
}

/** Print all available products */
void AdvisorMain::printProd() {
    
    std::cout << "Here is a list of available products: " <<  std::endl;
    
    // p is the product name
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::cout << "Product: " << p << std::endl;
    }
    
}

/** Find minimum bid or ask for product in current time step*/
void AdvisorMain::printMin(const std::vector<std::string>& tokens) {
    std::string productName = tokens[1];
    std::string productType = tokens[2];

    
    if(tokens.size() == 3 &&
       productNameIsValid(productName, orderBook.getKnownProducts()) &&
                         productTypeIsValid(productType) ) {
        
        std::vector<OrderBookEntry> entries;
        
        if (productType == "ask") {
            entries = orderBook.getOrders(OrderBookType::ask, tokens[1], currentTime);
            std::cout << "The min ask for " << productName << " is: " << OrderBook::getLowPrice(entries) << std::endl;
            
        }
        
        else if (productType == "bid") {
            entries = orderBook.getOrders(OrderBookType::bid, tokens[1], currentTime);
            std::cout << "The min bid for " << productName << " is: " << OrderBook::getLowPrice(entries) << std::endl;
        }
    }
        
    
    else { // Invalid input
        std::cout << "Invalid input, use 'help min' for more inforamtion." << std::endl;
    }
    
}

/** Find maximum bid or ask for product in current time step*/
void AdvisorMain::printMax(const std::vector<std::string>& tokens) {
    std::string productName = tokens[1];
    std::string productType = tokens[2];

    
    if(tokens.size() == 3 &&
       productNameIsValid(productName, orderBook.getKnownProducts()) &&
                         productTypeIsValid(productType) ) {
        
        std::vector<OrderBookEntry> entries;
        
        if (productType == "ask") {
            entries = orderBook.getOrders(OrderBookType::ask, tokens[1], currentTime);
            std::cout << "The max ask for " << productName << " is: " << OrderBook::getHighPrice(entries) << std::endl;
            
        }
        
        else if (productType == "bid") {
            entries = orderBook.getOrders(OrderBookType::bid, tokens[1], currentTime);
            std::cout << "The max bid for " << productName << " is: " << OrderBook::getHighPrice(entries) << std::endl;
        }
    }
        
    
    else { // Invalid input
        std::cout << "Invalid input, use 'help max' for more inforamtion." << std::endl;
    }
    
}

/** Compute average ask or bid for the sent product from the last N time steps*/
void AdvisorMain::printAvg(const std::vector<std::string>& tokens) {
    std::cout << "avg will be here " << std::endl;
    
}

/** Predict max or min ask or bid for the sent product for the next time step */
void AdvisorMain::predict(const std::vector<std::string>& tokens) {
    std::cout << "predict will be here " << std::endl;
    
}

/** Move to next time step */
void AdvisorMain::gotoNextTimeframe() {
    currentTime = orderBook.getNextTime(currentTime);
    ++currentTimeIndex;
    std::cout << "Current time at:  " << currentTime << std::endl;
}

/** Check if given product name is on the last of known products and return true if we find it otherwise return false  */
bool AdvisorMain::productNameIsValid(std::string productName, const std::vector<std::string>& knownProducts) {
    
    for (std::string const& p : knownProducts) {
        if (p == productName)
            return true;
    }
    
    return false;
    
}

/** Check if given product type is on the last of known type and return true if we find it otherwise return false */
bool AdvisorMain::productTypeIsValid(std::string productType) {
    
    if (productType == "ask" || productType == "bid")
        return true;
    
    return false;
    
}

/** Check if given command name is on the last of known commands and return true if we find it otherwise return false */
bool AdvisorMain::commanNameIsValid(std::string commandName, const std::vector<std::string>& knownCommands) {
    
    for (std::string const& c : knownCommands) {
        if (c == commandName)
            return true;
    }
    
    return false;
    
}
