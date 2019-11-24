#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../src/Order.hpp"

BOOST_AUTO_TEST_CASE( Order_Constructor_Test ) {
    std::unique_ptr<Order> order(new Order(1,Side::Bid,100,5000));
    BOOST_CHECK_EQUAL(order->getId(), 1);
    BOOST_CHECK_EQUAL(int(order->getSide()), int(Side::Bid));
    BOOST_CHECK_EQUAL(order->getQuantity(), 100);
    BOOST_CHECK_EQUAL(order->getPrice(), 5000); 
}

BOOST_AUTO_TEST_CASE( Order_Copy_Constructor_Test ) {
    std::unique_ptr<Order> order1Ptr(new Order(1,Side::Bid,100,5000));
    std::unique_ptr<Order> order(new Order(*order1Ptr));
    BOOST_CHECK_EQUAL(order->getId(), 1);
    BOOST_CHECK_EQUAL(int(order->getSide()), int(Side::Bid));
    BOOST_CHECK_EQUAL(order->getQuantity(), 100);
    BOOST_CHECK_EQUAL(order->getPrice(), 5000); 
}