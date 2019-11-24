#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include "OrderInputManager.hpp"

void OrderInputManager::process(std::string& inputLine)
{
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep{" \""};
    tokenizer tokens{inputLine, sep};
    std::vector<std::string> inputParts;
    for (auto& token : tokens)
    {
        std::string part = token;
        boost::algorithm::to_lower(part);
        inputParts.push_back(part);
    }
    process(inputParts);
}

void OrderInputManager::process(std::vector<std::string>& inputParts)
{
    if(inputParts.size() >= 5 && inputParts[0] == "order")
    {
        const unsigned long int id = std::stol(inputParts[1]);
        const Side side = inputParts[2] == "buy" ? Side::Bid : Side::Ask;
        const unsigned long int qty = std::stol(inputParts[3]);
        const unsigned long int px = std::stof(inputParts[4]) * 100;        
        std::shared_ptr<Order> order(new Order(id, side, qty, px));
        m_matcher.add(order);
    }
    else if(inputParts.size() >= 2 && inputParts[0] == "cancel")
    {
        const unsigned long int id = std::stol(inputParts[1]);
        std::shared_ptr<Order> origOrder = m_matcher.getOrder(id);
        if(origOrder->getId() > 0)
        {
            m_matcher.cancel(origOrder);
        }
    }
    else if(inputParts.size() >= 3 && inputParts[0] == "amend")
    {
        const unsigned long int id = std::stol(inputParts[1]);
        const unsigned long int qty = std::stol(inputParts[2]);
        std::shared_ptr<Order> origOrder = m_matcher.getOrder(id);
        if(origOrder->getId() > 0)
        {
            std::shared_ptr<Order> order(new Order(id,origOrder->getSide(), qty, origOrder->getPrice()));
            m_matcher.amend(order);
        }        
    }
    else if( inputParts.size() >= 4 && inputParts[0] == "q" && inputParts[1] == "level")
    {
        const Side side = inputParts[2] == "bid" ? Side::Bid : Side::Ask;
        int level = std::stoi(inputParts[3]);
        QueryResult result = m_matcher.query(level, side);
        std::cout << (side == Side::Bid ? "bid" : "ask")
            << "," << level
            << "," << result.getPrice()/100.0
            << "," << result.getQuantity()
            << std::endl;
    }
    else if( inputParts.size() >= 3 && inputParts[0] == "q" && inputParts[1] == "order")
    {
        const unsigned long int id = std::stol(inputParts[2]);
        QueryResult result = m_matcher.query(id);
        std::cout << (result.getSide() == Side::Bid ? "bid" : "ask")
            << "," << result.getLevel()
            << "," << result.getPrice()/100.0
            << "," << result.getQuantity()
            << std::endl;
    }
}