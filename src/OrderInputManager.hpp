#ifndef OrderInputManager_HPP
#define OrderInputManager_HPP

#include <string>
#include <vector>
#include "LimitOrderMatcher.hpp"

class OrderInputManager
{
    private:
        LimitOrderMatcher m_matcher;
    public:
        void process(std::string& inputLine);
        void process(std::vector<std::string>& inputParts);
};

#endif