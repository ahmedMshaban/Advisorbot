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
    currentTime = orderBook.getEarliestTime();
    
    printMenu();
    while(true) {
        input = getUserOption();
        processUserOption(input);
        std::cout << "==============" << std::endl;
    }
}

// Lists all available commands.
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
    
    else if (tokens[0] == "min" && commandValidator(tokens)) {
        printMin(tokens);
    }
    
    else if (tokens[0] == "max" && commandValidator(tokens)) {
        printMax(tokens);
    }
    
    else if (userOption.find("avg") != std::string::npos) {
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
        std::cout << "Bad input, please enter a valid command you can start with 'help'" << std::endl;
    }
    
}

void AdvisorMain::printHelpCmd(const std::vector<std::string>& tokens) {
    std::cout << "Help will be here " << std::endl;
}

void AdvisorMain::printProd() {
    
    std::cout << "Here is a list of available products: " <<  std::endl;
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::cout << "Product: " << p << std::endl;
    }
    
}

void AdvisorMain::printMin(const std::vector<std::string>& tokens) {
    
    std::vector<OrderBookEntry> entries;
    if (tokens[2] == "ask") {
        entries = orderBook.getOrders(OrderBookType::ask, tokens[1], currentTime);
        std::cout << "The min ask for " << tokens[1] << " is: " << OrderBook::getLowPrice(entries) << std::endl;

    }
    else if (tokens[2] == "bid") {
        entries = orderBook.getOrders(OrderBookType::bid, tokens[1], currentTime);
        std::cout << "The min bid for " << tokens[1] << " is: " << OrderBook::getLowPrice(entries) << std::endl;
    }
    
}

void AdvisorMain::printMax(const std::vector<std::string>& tokens) {
    
    std::vector<OrderBookEntry> entries;
    if (tokens[2] == "ask") {
        entries = orderBook.getOrders(OrderBookType::ask, tokens[1], currentTime);
        std::cout << "The max ask for " << tokens[1] << " is: " << OrderBook::getHighPrice(entries) << std::endl;

    }
    else if (tokens[2] == "bid") {
        entries = orderBook.getOrders(OrderBookType::bid, tokens[1], currentTime);
        std::cout << "The max bid for " << tokens[1] << " is: " << OrderBook::getHighPrice(entries) << std::endl;
    }
    
}

void AdvisorMain::printAvg(const std::vector<std::string>& tokens) {
    std::cout << "avg will be here " << std::endl;
    
}

void AdvisorMain::predict(const std::vector<std::string>& tokens) {
    std::cout << "predict will be here " << std::endl;
    
}

void AdvisorMain::gotoNextTimeframe() {
    currentTime = orderBook.getNextTime(currentTime);
    std::cout << "Current time at:  " << currentTime << std::endl;
}

bool AdvisorMain::commandValidator(const std::vector<std::string> &tokens) {
    bool productCheck = false;
    bool typeCheck = false;
    
    if((tokens[0] == "min" || tokens[0] == "max") && tokens.size() == 3) {
        // check if product is correct
        for (std::string const& p : orderBook.getKnownProducts()) {
            if (p == tokens[1])
            {
                productCheck = true;
            }
        }
        
        // couldn't find the product
        if(!productCheck) return false;
            
        // I found a the product now check if type is correct
        if (tokens[2] == "ask" || tokens[2] == "bid") {
            typeCheck = true;
        }
        
        if(typeCheck) return true;
    }
    
    // otherwise
    return false;
}
