#include "Parser.h"
#include "Command.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using std::string;

Parser::Parser() { }

Command Parser::getCommand() {
    std::cout << "> "; 

    string inputWord1;
    string delimiter = " ";

    string input;
    string words;
    std::cin >> input;

    std::vector<string> result;
    if (input.empty()) 
        return *new Command("");
 
    size_t pos = 0;
    size_t lpos = 0;
    auto dlen = delimiter.length();
    
    while ((pos = input.find(delimiter, lpos)) != string::npos) {
        result.push_back(input.substr(lpos, pos - lpos));
        lpos = pos + dlen;
    }

    result.push_back(input.substr(lpos, input.length()));
    return *new Command(result[0]);
}
