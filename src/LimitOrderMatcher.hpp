#ifndef LimitOrderMatcher_HPP
#define LimitOrderMatcher_HPP

#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <memory>
#include <functional>
#include "Order.hpp"
#include "QueryResult.hpp"

class LimitOrderMatcher
{
    private:
        struct timeCompare
        { 
            bool operator()(const std::shared_ptr<Order>& lhs, const std::shared_ptr<Order>& rhs)
            {
                return lhs->getReceiveTime() < rhs->getReceiveTime(); 
            }
        };
        typedef std::set<std::shared_ptr<Order>, timeCompare> OrderList;
        typedef std::map<long int,OrderList, std::greater<long int>> BidOrderListByPrice;
        typedef std::map<long int,OrderList> AskOrderListByPrice;

        BidOrderListByPrice m_bidOrderList;
        AskOrderListByPrice m_askOrderList;

        typedef std::unordered_map<long int, std::shared_ptr<Order>> OrderCache;
        OrderCache m_orderCache;
    public:
        std::shared_ptr<Order> getOrder(long int id);
        void add(std::shared_ptr<Order>& order);
        void cancel(std::shared_ptr<Order>& order);
        void amend(std::shared_ptr<Order>& order);
        QueryResult query(int level, Side side);
        QueryResult query(long int id);
    private:
        void tryMatching();
        void cancelAndAdd(std::shared_ptr<Order>& origOrder, std::shared_ptr<Order>& order);
        void amendDownOrderQty(std::shared_ptr<Order>& origOrder, std::shared_ptr<Order>& order);

        template <typename T>
        void cancel(std::shared_ptr<Order>& order, T& orderList)
        {
            typename T::iterator it = orderList.find(order->getPrice());
            if(it != orderList.end())
            {
                it->second.erase(order);
                if(it->second.empty())
                {
                    orderList.erase(it);
                }
            }    
            m_orderCache.erase(order->getId());
        }

        template <typename T>
        void amendDownOrderQty(std::shared_ptr<Order> origOrder, std::shared_ptr<Order>& order, T& orderListByPricer)
        {            
            typename T::iterator priceIter = orderListByPricer.find(origOrder->getPrice());
            if(priceIter != orderListByPricer.end())
            {
                OrderList& orderList = priceIter->second;
                OrderList::iterator olIter = orderList.find(origOrder);
                if(olIter != orderList.end())
                {
                    (*olIter)->setQuantity(order->getQuantity());
                }               
            }                
        }

        template <typename T>
        QueryResult query(int level, Side side, T& orderListByPrice)
        {
            unsigned long int quantity{};
            unsigned long int price{};
    
            int levelIndex = 0;
            typename T::iterator priceIter = orderListByPrice.begin();
            while(level != levelIndex && priceIter != orderListByPrice.end())
            {
                ++priceIter;
                ++levelIndex;
            }
            if(level == levelIndex && priceIter != orderListByPrice.end())
            {
                price = priceIter->first;
                for(auto order : priceIter->second)
                {
                    quantity += order->getQuantity();
                }
            }
            return QueryResult(quantity, price, level, side);
        }

        template <typename T>
        QueryResult query(std::shared_ptr<Order> order, T& orderListByPrice)
        {
            int levelIndex{};
            typename T::iterator priceIter = orderListByPrice.begin();
            while(priceIter->first != order->getPrice() && priceIter != orderListByPrice.end())
            {
                ++levelIndex;
                ++priceIter;
            }
            return QueryResult(order->getQuantity(), order->getPrice(), levelIndex, order->getSide());
        }
};

#endif