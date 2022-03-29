#include <iostream>
#include <string>

#include "bottom_up_parser.h"

// g++ -c src/*.cpp && g++ *.o -o main


int main(){
    std::string rules,input;

    std::cout<<"Enter the rules:"<<std::endl;
    getline(std::cin,rules);

    std::cout<<"Enter the input word"<<std::endl;
    getline(std::cin,input);

    BottomUpParser BUP(rules,input);
    BUP.print_rules();
    BUP.start_parshing();

    return 0;
}