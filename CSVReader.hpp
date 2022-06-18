//
//  CSVReader.hpp
//  Advisorbot
//
//  This class copied from Merklerex
//

#ifndef CSVReader_hpp
#define CSVReader_hpp

#include <stdio.h>

#include "OrderBookEntry.hpp"

#include <vector>

#include <string>


class CSVReader {
    public:
        CSVReader();

    static std::vector < OrderBookEntry > readCSV(std::string csvFile);
    static std::vector < std::string > tokenise(std::string csvLine, char separator);

    static OrderBookEntry stringsToOBE(std::string price,
        std::string amount,
        std::string timestamp,
        std::string product,
        OrderBookType OrderBookType);

    private:
        static OrderBookEntry stringsToOBE(std::vector < std::string > strings);

};
#endif /* CSVReader_hpp */
