#include <string>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <iostream>

#ifndef BOTTOM_UP_PARSER
#define BOTTOM_UP_PARSER

class BottomUpParser{

    enum StateofAnalysis{
        Q, // normal
        T, // acceptable
        B  // backtrack
    };

    struct ParsingState{
        StateofAnalysis state;
        unsigned int i; // pointer in the input word
        std::string alpha;
        std::string beta;

        
    };

    BottomUpParser::ParsingState parsing_state;
    void print_state();

    std::string input_word;
    unsigned int input_word_length;

    std::vector<char> capitals={'Q','W','E','R','T','Y','U','I','O','P',
                                'A','S','D','F','G','H','J','K','L','Z','X','C',
                                'V','B','N','M'};

    bool is_capital(char letter);
    std::vector<std::string> extract_rule_symbols();

    struct Rule
    {
        char symbol;
        std::string rule;
    };
    std::vector<Rule> rules;
    void read_rules(const std::string raw_rules);
    void shift();
    bool reduce();


public:
    BottomUpParser();
    BottomUpParser(const std::string raw_rules, std::string input);

    void print_rules();

    void start_parshing();


};

#endif