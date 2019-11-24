#ifndef QueryResult_HPP
#define QueryResult_HPP

#include "Side.hpp"

class QueryResult
{
    private:
        unsigned long int     m_quantity;
        unsigned long int     m_price;
        unsigned int          m_level;
        Side                  m_side;
    public:
        QueryResult(unsigned long int qty, unsigned long int price, int level, const Side side)
            : m_quantity(qty),
            m_price(price),
            m_level(level),
            m_side(side)
        {}

        QueryResult(const QueryResult& other)
        {
            m_quantity = other.m_quantity;
            m_price = other.m_price;
            m_level = other.m_level;
            m_side = other.m_side;

        }

        QueryResult& operator=(const QueryResult& other)
        {
            if (this != &other) 
            {
                m_quantity = other.m_quantity;
                m_price = other.m_price;
                m_level = other.m_level;
                m_side = other.m_side;
            }

            return *this;
        }

        QueryResult& operator=(QueryResult&& other) noexcept
        {
            if (this != &other) 
            {
                m_quantity = other.m_quantity;
                m_price = other.m_price;
                m_level = other.m_level;
                m_side = other.m_side;
            }
            return *this;
        }

        Side getSide()
        {
            return m_side;
        }  

        unsigned long int getQuantity()
        {
            return m_quantity;
        }  

        unsigned long int getPrice()
        {
            return m_price;
        }

        unsigned int getLevel()
        {
            return m_level;
        }
};

#endif