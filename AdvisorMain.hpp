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
    /** Lists all available commands. */
    void printMenu();
    /** Perform a basic check on user input and return it */
    std::string getUserOption();
    /** Figurout the user input related to which command. */
    void processUserOption(std::string userOption);
    /** Print more info about each of the available commands and how to use them. */
    void printHelpCmd(const std::vector<std::string>& tokens);
    /** Print all available products */
    void printProd();
    /** Find minimum bid or ask for product in current time step*/
    void printMin(const std::vector<std::string>& tokens);
    /** Find maximum bid or ask for product in current time step*/
    void printMax(const std::vector<std::string>& tokens);
    /** Compute average ask or bid for the sent product from the last N time steps*/
    void printAvg(const std::vector<std::string>& tokens);
    /** Predict max or min ask or bid for the sent product for the next time step */
    void predict(const std::vector<std::string>& tokens);
    /** Move to next time step */
    void step(const std::vector<std::string>& tokens);
    /** print current time step  index*/
    void printCurrentTimeStep();
    /** Check if given product name is on the last of known products and return true if we find it otherwise return false  */
    bool productNameIsValid(std::string productName, const std::vector<std::string>& knownProducts);
    /** Check if given product type is on the last of known type and return true if we find it otherwise return false */
    bool productTypeIsValid(std::string productType);
    /** Check if given command name is on the last of known commands and return true if we find it otherwise return false */
    bool commanNameIsValid(std::string commandName, const std::vector<std::string>& knownCommands);
    /** Return the price sum of the given products */
    double totalProductPrices(const std::vector<OrderBookEntry> orders);
    /** Return a predicted min price for a product in the next time step */
    double getPredictMin(std::string productName, int timestampIndex, std::string productType);
    /** Return a predicted max price for a product in the next time step   */
    double getPredictMax(std::string productName, int timestampIndex, std::string productType);

    OrderBook orderBook{"20200601.csv"};
    std::string currentTime;
    int currentTimeStep;
    std::vector<std::string> avaliableCommands{"help", "prod", "min", "max", "avg", "predict", "time", "step"};

};

#endif /* AdvisorMain_hpp */
