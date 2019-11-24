#include <iostream>
#include <string>
#include "OrderInputManager.hpp"


int main(){
    OrderInputManager orderInputManager;
    for (std::string line; std::getline(std::cin, line);)
    {
        orderInputManager.process(line);
    }
    return 0;
}