#ifndef ORDER_HPP
#define ORDER_HPP

#include <chrono>
#include "Side.hpp"

class Order
{
    private:
        long int                    m_receivedTime;
        const unsigned long int     m_id;
        unsigned long int           m_quantity;
        const unsigned long int     m_price;
        const Side                  m_side;

    public:
        Order(unsigned long int id, Side side, unsigned long int qty, unsigned long int price)
            : m_id(id), m_side(side), m_quantity(qty), m_price(price)
        {
            m_receivedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        }

        Order(const Order& order)
            : m_id(order.m_id), 
            m_side(order.m_side), 
            m_quantity(order.m_quantity), 
            m_price(order.m_price)
        {
            m_receivedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        }

        long int getReceiveTime()
        {
            return m_receivedTime;
        }

        unsigned long int getId()
        {
            return m_id;
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

        // only used for amend down case
        void setQuantity(unsigned long int qty)
        {
            if(qty < m_quantity){
                m_quantity = qty;
            }
        }  

};

#endif