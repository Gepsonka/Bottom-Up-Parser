#include <string>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>

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
        std::stack<std::string> alpha;
        std::string beta;

        // divide the operations into levels to make backtrack easier
        unsigned int level;

        // helping in the backtrack keeping track of which alternative are we using
        // currently
        // in case of backtrack we only increase this number to try
        // the next alternative of the sybol
        unsigned int symbol_alternative;

        ParsingState();
        ParsingState(const ParsingState* ps); // copy constructor
        static ParsingState* new_parsing_state();
        static ParsingState* copy(const ParsingState* ps);
        void print_instance_to_std_err();
        // TODO: print out the tree in the end
    };

    std::vector<char> capitals={'Q','W','E','R','T','Y','U','I','O','P',
                                'A','S','D','F','G','H','J','K','L','Z','X','C',
                                'V','B','N','M'};

    void is_capital(char letter);



    struct Rule
    {
        char symbol;
        std::string rule;
    };
    

    BottomUpParser();
    BottomUpParser(const std::string raw_rules, const std::string input_word);

    std::vector<Rule> rules;


    void read_rules(const std::string raw_rules);
}



#endif