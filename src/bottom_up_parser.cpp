#include "bottom_up_parser.h"




bool BottomUpParser::is_capital(char letter){
    if (std::find(capitals.begin(),capitals.end(),letter)==capitals.end()){
        return false;
    }

    return true;
}


void BottomUpParser::read_rules(const std::string raw_rules){
    std::string curr_symbol;
    std::string curr_rule;
    bool after_arrow=false; // check if we are after the '>' in the rule declaration

    for (int i=0;i<raw_rules.length();++i){
        if (raw_rules[i]=='>'){
            after_arrow=true;
        } 
        else if (raw_rules[i]==' '){
            rules[curr_symbol].push_back(curr_rule);
            curr_rule=curr_symbol="";
            after_arrow=false;
        }

        else if (after_arrow){
            curr_rule+=raw_rules[i];
                
        } 
        else {
            if (is_capital(raw_rules[i])){
                if (curr_symbol==""){
                    curr_symbol=raw_rules[i];
                }
                else {
                    std::cerr<<"Cannot give more than 1 symbols in one rule (S>adeSxa is valid, Sk>fnmekSlsS or SL>kjdfSlsK is not)"<<std::endl;
                    exit(-1);
                }
            }
            else {
                std::cerr<<"Symbol cannot be a terminal (lower case character): "<<raw_rules[i]<<std::endl;
                exit(-1);
            }

        }
    }

    if (curr_rule!="" && curr_symbol!=""){
        rules[curr_symbol].push_back(curr_rule);
        curr_rule=curr_symbol="";
        after_arrow=false;
    }

    std::vector<std::string> symbols=extract_rule_symbols();
    if(std::find(symbols.begin(), symbols.end(),"S")==symbols.end()){
        std::cerr<<"Starting symbol is required! (S)"<<std::endl;
        exit(-1);
    }

    for (const auto symb: extract_rule_symbols()){
        for (const auto rule:rules[symb]){
            for (const auto rule_char:rule){
                if (is_capital(rule_char)){
                    if (std::find(extract_rule_symbols().begin(),extract_rule_symbols().end(),std::string(1,rule_char))==extract_rule_symbols().end()){
                        std::cerr<<rule_char<<" has no member."<<std::endl;
                        exit(-1);
                    }
                }
            }
        }
    }
}
