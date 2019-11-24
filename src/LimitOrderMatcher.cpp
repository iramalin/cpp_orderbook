#include "LimitOrderMatcher.hpp"

std::shared_ptr<Order> LimitOrderMatcher::getOrder(long int id)
{
    OrderCache::iterator it = m_orderCache.find(id);
    if(it != m_orderCache.end())
    {
        return it->second;
    }
    std::shared_ptr<Order> order(new Order(0, Side::Bid, 0, 0));
    return order;
}

void LimitOrderMatcher::add(std::shared_ptr<Order>& order)
{
    auto pair = m_orderCache.emplace(order->getId(), order);
    if(pair.second)
    {
        if(order->getSide() == Side::Bid){
            m_bidOrderList[order->getPrice()].insert(order);
        }
        else
        {
            m_askOrderList[order->getPrice()].insert(order);
        }
        tryMatching();
    }
}

void LimitOrderMatcher::cancel(std::shared_ptr<Order>& order)
{
    if(order->getSide() == Side::Bid)
    {
        cancel(order, m_bidOrderList);
    }
    else
    {
        cancel(order, m_askOrderList);
    }  
}

void LimitOrderMatcher::amend(std::shared_ptr<Order>& order)
{
    if(!order->getQuantity() || !order->getPrice())
    {
        cancel(order);
    }

    OrderCache::iterator it = m_orderCache.find(order->getId());
    if(it != m_orderCache.end())
    {
        std::shared_ptr<Order> oldOrder = it->second;
        if(oldOrder->getPrice() != order->getPrice())
        {
            cancelAndAdd(oldOrder, order);
        }
        else if(oldOrder->getQuantity() != order->getQuantity())
        {
            if(oldOrder->getQuantity() < order->getQuantity())
            {
                cancelAndAdd(oldOrder, order);
            }
            else
            {
                amendDownOrderQty(oldOrder, order);
            }            
        }
    }
}

void LimitOrderMatcher::amendDownOrderQty(std::shared_ptr<Order>& oldOrder, std::shared_ptr<Order>& order)
{
    if(order->getSide() == Side::Bid)
    {
        amendDownOrderQty(oldOrder, order, m_bidOrderList);
    }
    else
    {
        amendDownOrderQty(oldOrder, order, m_askOrderList);
    }     
}

void LimitOrderMatcher::cancelAndAdd(std::shared_ptr<Order>& oldOrder, std::shared_ptr<Order>& order)
{
    cancel(oldOrder);
    add(order);
}

void LimitOrderMatcher::tryMatching()
{
    BidOrderListByPrice::iterator bPriceIter = m_bidOrderList.begin();
    AskOrderListByPrice::iterator aPriceIter = m_askOrderList.begin();

    while(bPriceIter != m_bidOrderList.end() && aPriceIter != m_askOrderList.end())
    {
        if(bPriceIter->first >= aPriceIter->first)
        {
            OrderList& bidOrderList = bPriceIter->second;
            OrderList& askOrderList = aPriceIter->second;

            OrderList::iterator boIter = bidOrderList.begin();
            OrderList::iterator aoIter = askOrderList.begin();
            while(boIter != bidOrderList.end() && aoIter != askOrderList.end())
            {
                if((*boIter)->getQuantity() == (*aoIter)->getQuantity())
                {
                    bidOrderList.erase(boIter);
                    askOrderList.erase(aoIter);
                }
                else if((*boIter)->getQuantity() > (*aoIter)->getQuantity())
                {
                    (*boIter)->setQuantity((*boIter)->getQuantity() - (*aoIter)->getQuantity());
                    askOrderList.erase(aoIter);
                }
                else if((*boIter)->getQuantity() < (*aoIter)->getQuantity())
                {                    
                    (*aoIter)->setQuantity((*aoIter)->getQuantity() - (*boIter)->getQuantity());
                    bidOrderList.erase(boIter);
                }
                boIter = bidOrderList.begin();
                aoIter = askOrderList.begin();
            }
            if(bidOrderList.empty())
            {
                m_bidOrderList.erase(bPriceIter);
            }
            if(askOrderList.empty())
            {
                m_askOrderList.erase(aPriceIter);
            }
        }
        else
        {
            break;
        }
        bPriceIter = m_bidOrderList.begin();
        aPriceIter = m_askOrderList.begin();
    }
}

QueryResult LimitOrderMatcher::query(int level, Side side)
{
    if(side == Side::Bid)
    {
        return query(level, side, m_bidOrderList);
    }
    return query(level, side, m_askOrderList);
}

QueryResult LimitOrderMatcher::query(long int id)
{
    OrderCache::iterator it = m_orderCache.find(id);
    if(it != m_orderCache.end())
    {
        std::shared_ptr<Order> order = it->second;
        if(order->getSide() == Side::Bid)
        {
            return query(order, m_bidOrderList);
        }
        return query(order, m_askOrderList);
    }
    return QueryResult(0,0.0,0,Side::Bid);
}
