#include "bottom_up_parser.h"

BottomUpParser::BottomUpParser(const std::string raw_rules, std::string input){
    read_rules(raw_rules);
    input_word=input;
    input_word_length=input_word.length();
    parsing_state.i=0;
    parsing_state.state=BottomUpParser::StateofAnalysis::Q;
    parsing_state.alpha="";
    parsing_state.beta="";
}


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
        else if (raw_rules[i]=='-'){
            continue;
        }
        else if (raw_rules[i]==' '){
            Rule new_rule;
            new_rule.symbol=curr_symbol[0];
            new_rule.rule=curr_rule;
            rules.push_back(new_rule);
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
        Rule new_rule;
        new_rule.symbol=curr_symbol[0];
        new_rule.rule=curr_rule;
        rules.push_back(new_rule);
        curr_rule=curr_symbol="";
        after_arrow=false;
    }

    std::vector<std::string> symbols=extract_rule_symbols();
    if(std::find(symbols.begin(), symbols.end(),"S")==symbols.end()){
        std::cerr<<"Starting symbol is required! (S)"<<std::endl;
        exit(-1);
    }

    for (const auto rule : rules)
    {
        for (const auto rule_char : rule.rule)
        {
            if (is_capital(rule_char))
            {
                if (std::find(extract_rule_symbols().begin(), extract_rule_symbols().end(), std::string(1, rule_char)) == extract_rule_symbols().end())
                {
                    std::cerr << rule_char << " has no member." << std::endl;
                    exit(-1);
                }
            }
        }
    }
}

// for debug purposes
void BottomUpParser::print_rules(){
    std::cerr<<"The rules are the following:"<<std::endl;
    for (auto x: rules){
        std::cerr<<x.symbol<<"->"<<x.rule<<std::endl;
    }
}

// for debug purposes
void BottomUpParser::print_state(){
    std::string soa;
    switch(parsing_state.state){
        case BottomUpParser::StateofAnalysis::Q:
            soa="Q";
            break;
        case BottomUpParser::StateofAnalysis::T:
            soa="T";
            break;
        case BottomUpParser::StateofAnalysis::B:
            soa="B";
            break;
    }


    std::cerr<<"state: "<<soa<<std::endl;
    std::cerr<<"pointer in word: "<<parsing_state.i<<std::endl;
    std::cerr<<"alpha stack: "<<parsing_state.alpha<<std::endl;
    std::cerr<<"beta stack: "<<parsing_state.beta<<std::endl;
    std::cerr<<"input word:"<<input_word<<std::endl;

}


std::vector<std::string> BottomUpParser::extract_rule_symbols(){
    std::vector<std::string> symbols_vec;
    for (auto x: rules){
        symbols_vec.push_back(std::string(1,x.symbol));
    }

    return symbols_vec;
}

void BottomUpParser::shift(){
    std::cout<<std::endl;
    print_state();
    std::cerr<<"shifting..."<<std::endl;
    parsing_state.alpha+=input_word[0];
    input_word=input_word.substr(1);
    parsing_state.beta="s"+parsing_state.beta;
    parsing_state.i++;

}

bool BottomUpParser::reduce(){
    std::cout<<std::endl;
    print_state();
    std::cerr<<"reducing..."<<std::endl;
    for (int i=parsing_state.alpha.length();i>=1;i--)
    {
        std::string front_substr=parsing_state.alpha.substr(0,parsing_state.alpha.length()-i);
        std::string observed_substr=parsing_state.alpha.substr(parsing_state.alpha.length()-i);
        for (int j=0; j<rules.size(); j++){
            if (observed_substr==rules[j].rule){
                parsing_state.alpha=front_substr+rules[j].symbol;
                parsing_state.beta=std::to_string(j+1)+parsing_state.beta;
                return true;
            }
        }

    }
    // std::string a = "kacsahal";
    // for (int i = 1; i <= a.length(); i++)
    // {
    //     std::cout << a.substr(i, a.length() - 1) << std::endl;
    // }
    // i am gonna need this

    // int i=0;
    // for (auto x : rules){
    //     if (x.rule==parsing_state.alpha){
    //         parsing_state.alpha=x.symbol;
    //         parsing_state.beta=std::to_string(i)+parsing_state.beta;
    //         return true;
    //     }
    //     i++;
    // }

    return false;
}


void BottomUpParser::start_parshing(){
    shift();
    while (true){
        if (input_word_length==parsing_state.i && parsing_state.alpha=="S"){
            std::cout<<std::endl;
            print_state();
            std::cout<<std::endl;
            std::cout<<"Parsing was successful"<<std::endl;
            std::cout<<"The word is an element of the language"<<std::endl;
            std::cout<<"beta stack: "<<parsing_state.beta<<std::endl;
            std::cout<<"Program exitting..."<<std::endl;
            return;
        }

        if (input_word_length<parsing_state.i){
            std::cout<<std::endl;
            print_state();
            std::cout<<"Parsing was unsuccessful"<<std::endl;
            std::cout<<"The word is not an element of the language"<<std::endl;
            std::cout<<"Program exitting..."<<std::endl;
            return;
        }

        bool reduce_result=reduce();
        if (!reduce_result){
            shift();
        }

    }
}