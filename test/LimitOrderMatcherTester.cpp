#include <boost/test/unit_test.hpp>
#include <memory>
#include "../src/LimitOrderMatcher.hpp"

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Basic_Query_Test ) {
    LimitOrderMatcher matcher;

    QueryResult bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 0);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 0);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    QueryResult bidQuery1 = matcher.query(1, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery1.getQuantity(), 0);
    BOOST_CHECK_EQUAL(bidQuery1.getPrice(), 0);
    BOOST_CHECK_EQUAL(bidQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(bidQuery1.getSide()), int(Side::Bid));

    QueryResult askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 0);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 0);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));

    QueryResult askQuery1 = matcher.query(1, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery1.getQuantity(), 0);
    BOOST_CHECK_EQUAL(askQuery1.getPrice(), 0);
    BOOST_CHECK_EQUAL(askQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(askQuery1.getSide()), int(Side::Ask));

}

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Basic_BidOrder_Test ) {
    LimitOrderMatcher matcher;
    std::shared_ptr<Order> bidOrder1(new Order(1001, Side::Bid, 100, 1230));
    matcher.add(bidOrder1);
    std::shared_ptr<Order> invalidAskOrder1(new Order(1001, Side::Ask, 100, 1230));
    matcher.add(invalidAskOrder1);

    QueryResult bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 100);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 1230);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    QueryResult askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 0);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 0);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));
}

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Basic_AskOrder_Test ) {
    LimitOrderMatcher matcher;
    std::shared_ptr<Order> askOrder1(new Order(1001, Side::Ask, 100, 1230));
    matcher.add(askOrder1);
    std::shared_ptr<Order> invalidBidOrder1(new Order(1001, Side::Bid, 100, 1230));
    matcher.add(invalidBidOrder1);

    QueryResult askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 100);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 1230);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));

    QueryResult bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 0);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 0);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));
}

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Basic_Bid_And_Ask_Order_Test ) {
    LimitOrderMatcher matcher;
    std::shared_ptr<Order> bidOrder1(new Order(1001, Side::Bid, 100, 1230));
    matcher.add(bidOrder1);
    std::shared_ptr<Order> askOrder1(new Order(1002, Side::Ask, 100, 1240));
    matcher.add(askOrder1);

    QueryResult buyQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(buyQuery0.getQuantity(), 100);
    BOOST_CHECK_EQUAL(buyQuery0.getPrice(), 1230);
    BOOST_CHECK_EQUAL(buyQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(buyQuery0.getSide()), int(Side::Bid));

    QueryResult sellQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(sellQuery0.getQuantity(), 100);
    BOOST_CHECK_EQUAL(sellQuery0.getPrice(), 1240);
    BOOST_CHECK_EQUAL(sellQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(sellQuery0.getSide()), int(Side::Ask));
}

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Multiple_Bid_And_Ask_Order_Test ) {
    LimitOrderMatcher matcher;
    std::shared_ptr<Order> bidOrder1(new Order(1001, Side::Bid, 100, 1230));
    matcher.add(bidOrder1);
    std::shared_ptr<Order> bidOrder2(new Order(1002, Side::Bid, 200, 1230));
    matcher.add(bidOrder2);

    std::shared_ptr<Order> askOrder1(new Order(1003, Side::Ask, 300, 1240));
    matcher.add(askOrder1);
    std::shared_ptr<Order> askOrder2(new Order(1004, Side::Ask, 400, 1240));
    matcher.add(askOrder2);

    QueryResult buyQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(buyQuery0.getQuantity(), 300);
    BOOST_CHECK_EQUAL(buyQuery0.getPrice(), 1230);
    BOOST_CHECK_EQUAL(buyQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(buyQuery0.getSide()), int(Side::Bid));

    QueryResult sellQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(sellQuery0.getQuantity(), 700);
    BOOST_CHECK_EQUAL(sellQuery0.getPrice(), 1240);
    BOOST_CHECK_EQUAL(sellQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(sellQuery0.getSide()), int(Side::Ask));
}

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Multi_Level_Bid_And_Ask_Order_Test ) {
    LimitOrderMatcher matcher;
    std::shared_ptr<Order> bidOrder11(new Order(10011, Side::Bid, 100, 1230));
    matcher.add(bidOrder11);
    std::shared_ptr<Order> bidOrder12(new Order(10012, Side::Bid, 100, 1230));
    matcher.add(bidOrder12);
    std::shared_ptr<Order> bidOrder21(new Order(10021, Side::Bid, 200, 1240));
    matcher.add(bidOrder21);
    std::shared_ptr<Order> bidOrder22(new Order(10022, Side::Bid, 200, 1240));
    matcher.add(bidOrder22);

    std::shared_ptr<Order> askOrder31(new Order(10031, Side::Ask, 300, 1250));
    matcher.add(askOrder31);
    std::shared_ptr<Order> askOrder32(new Order(10032, Side::Ask, 300, 1250));
    matcher.add(askOrder32);    
    std::shared_ptr<Order> askOrder41(new Order(10041, Side::Ask, 400, 1260));
    matcher.add(askOrder41);
    std::shared_ptr<Order> askOrder42(new Order(10042, Side::Ask, 400, 1260));
    matcher.add(askOrder42);

    QueryResult buyQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(buyQuery0.getQuantity(), 400);
    BOOST_CHECK_EQUAL(buyQuery0.getPrice(), 1240);
    BOOST_CHECK_EQUAL(buyQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(buyQuery0.getSide()), int(Side::Bid));

    QueryResult buyQuery1 = matcher.query(1, Side::Bid);
    BOOST_CHECK_EQUAL(buyQuery1.getQuantity(), 200);
    BOOST_CHECK_EQUAL(buyQuery1.getPrice(), 1230);
    BOOST_CHECK_EQUAL(buyQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(buyQuery1.getSide()), int(Side::Bid));

    QueryResult sellQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(sellQuery0.getQuantity(), 600);
    BOOST_CHECK_EQUAL(sellQuery0.getPrice(), 1250);
    BOOST_CHECK_EQUAL(sellQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(sellQuery0.getSide()), int(Side::Ask));

    QueryResult sellQuery1 = matcher.query(1, Side::Ask);
    BOOST_CHECK_EQUAL(sellQuery1.getQuantity(), 800);
    BOOST_CHECK_EQUAL(sellQuery1.getPrice(), 1260);
    BOOST_CHECK_EQUAL(sellQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(sellQuery1.getSide()), int(Side::Ask));
}

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Basic_Amend_Down_Qty_Bid_Test ) {
    LimitOrderMatcher matcher;
    std::shared_ptr<Order> bidOrder1(new Order(1001, Side::Bid, 100, 1210));
    matcher.add(bidOrder1);
    std::shared_ptr<Order> bidOrder2(new Order(1002, Side::Bid, 2000, 1220));
    matcher.add(bidOrder2);
    std::shared_ptr<Order> bidOrder3(new Order(1003, Side::Bid, 300, 1230));
    matcher.add(bidOrder3);

    QueryResult bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 300);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 1230);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    QueryResult bidQuery1 = matcher.query(1, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery1.getQuantity(), 2000);
    BOOST_CHECK_EQUAL(bidQuery1.getPrice(), 1220);
    BOOST_CHECK_EQUAL(bidQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(bidQuery1.getSide()), int(Side::Bid));

    QueryResult bidQuery2 = matcher.query(2, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery2.getQuantity(), 100);
    BOOST_CHECK_EQUAL(bidQuery2.getPrice(), 1210);
    BOOST_CHECK_EQUAL(bidQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(bidQuery2.getSide()), int(Side::Bid));

    std::shared_ptr<Order> amendBidOrder2(new Order(1002, Side::Bid, 1000, 1220));
    matcher.amend(amendBidOrder2);

    bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 300);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 1230);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    bidQuery1 = matcher.query(1, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery1.getQuantity(), 1000);
    BOOST_CHECK_EQUAL(bidQuery1.getPrice(), 1220);
    BOOST_CHECK_EQUAL(bidQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(bidQuery1.getSide()), int(Side::Bid));

    bidQuery2 = matcher.query(2, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery2.getQuantity(), 100);
    BOOST_CHECK_EQUAL(bidQuery2.getPrice(), 1210);
    BOOST_CHECK_EQUAL(bidQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(bidQuery2.getSide()), int(Side::Bid));

}

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Basic_Amend_Down_Qty_Ask_Test ) {
    LimitOrderMatcher matcher;
    std::shared_ptr<Order> askOrder1(new Order(1001, Side::Ask, 100, 1210));
    matcher.add(askOrder1);
    std::shared_ptr<Order> askOrder2(new Order(1002, Side::Ask, 2000, 1220));
    matcher.add(askOrder2);
    std::shared_ptr<Order> askOrder3(new Order(1003, Side::Ask, 300, 1230));
    matcher.add(askOrder3);

    QueryResult askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 100);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 1210);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));

    QueryResult askQuery1 = matcher.query(1, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery1.getQuantity(), 2000);
    BOOST_CHECK_EQUAL(askQuery1.getPrice(), 1220);
    BOOST_CHECK_EQUAL(askQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(askQuery1.getSide()), int(Side::Ask));

    QueryResult askQuery2 = matcher.query(2, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery2.getQuantity(), 300);
    BOOST_CHECK_EQUAL(askQuery2.getPrice(), 1230);
    BOOST_CHECK_EQUAL(askQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(askQuery2.getSide()), int(Side::Ask));

    std::shared_ptr<Order> amendAskOrder2(new Order(1002, Side::Ask, 1000, 1220));
    matcher.amend(amendAskOrder2);

    askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 100);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 1210);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));

    askQuery1 = matcher.query(1, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery1.getQuantity(), 1000);
    BOOST_CHECK_EQUAL(askQuery1.getPrice(), 1220);
    BOOST_CHECK_EQUAL(askQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(askQuery1.getSide()), int(Side::Ask));

    askQuery2 = matcher.query(2, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery2.getQuantity(), 300);
    BOOST_CHECK_EQUAL(askQuery2.getPrice(), 1230);
    BOOST_CHECK_EQUAL(askQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(askQuery2.getSide()), int(Side::Ask));
}

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Basic_Amend_Qty_Up_Bid_Test ) {
    LimitOrderMatcher matcher;
    std::shared_ptr<Order> bidOrder1(new Order(1001, Side::Bid, 100, 1210));
    matcher.add(bidOrder1);
    std::shared_ptr<Order> bidOrder2(new Order(1002, Side::Bid, 2000, 1220));
    matcher.add(bidOrder2);
    std::shared_ptr<Order> bidOrder3(new Order(1003, Side::Bid, 300, 1230));
    matcher.add(bidOrder3);

    QueryResult bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 300);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 1230);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    QueryResult bidQuery1 = matcher.query(1, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery1.getQuantity(), 2000);
    BOOST_CHECK_EQUAL(bidQuery1.getPrice(), 1220);
    BOOST_CHECK_EQUAL(bidQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(bidQuery1.getSide()), int(Side::Bid));

    QueryResult bidQuery2 = matcher.query(2, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery2.getQuantity(), 100);
    BOOST_CHECK_EQUAL(bidQuery2.getPrice(), 1210);
    BOOST_CHECK_EQUAL(bidQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(bidQuery2.getSide()), int(Side::Bid));

    std::shared_ptr<Order> amendBidOrder2(new Order(1002, Side::Bid, 20000, 1220));
    matcher.amend(amendBidOrder2);

    bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 300);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 1230);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    bidQuery1 = matcher.query(1, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery1.getQuantity(), 20000);
    BOOST_CHECK_EQUAL(bidQuery1.getPrice(), 1220);
    BOOST_CHECK_EQUAL(bidQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(bidQuery1.getSide()), int(Side::Bid));

    bidQuery2 = matcher.query(2, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery2.getQuantity(), 100);
    BOOST_CHECK_EQUAL(bidQuery2.getPrice(), 1210);
    BOOST_CHECK_EQUAL(bidQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(bidQuery2.getSide()), int(Side::Bid));

}

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Basic_Amend_Qty_Up_Ask_Test ) {
    LimitOrderMatcher matcher;
    std::shared_ptr<Order> askOrder1(new Order(1001, Side::Ask, 100, 1210));
    matcher.add(askOrder1);
    std::shared_ptr<Order> askOrder2(new Order(1002, Side::Ask, 2000, 1220));
    matcher.add(askOrder2);
    std::shared_ptr<Order> askOrder3(new Order(1003, Side::Ask, 300, 1230));
    matcher.add(askOrder3);

    QueryResult askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 100);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 1210);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));

    QueryResult askQuery1 = matcher.query(1, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery1.getQuantity(), 2000);
    BOOST_CHECK_EQUAL(askQuery1.getPrice(), 1220);
    BOOST_CHECK_EQUAL(askQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(askQuery1.getSide()), int(Side::Ask));

    QueryResult askQuery2 = matcher.query(2, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery2.getQuantity(), 300);
    BOOST_CHECK_EQUAL(askQuery2.getPrice(), 1230);
    BOOST_CHECK_EQUAL(askQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(askQuery2.getSide()), int(Side::Ask));

    std::shared_ptr<Order> amendAskOrder2(new Order(1002, Side::Ask, 20000, 1220));
    matcher.amend(amendAskOrder2);

    askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 100);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 1210);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));

    askQuery1 = matcher.query(1, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery1.getQuantity(), 20000);
    BOOST_CHECK_EQUAL(askQuery1.getPrice(), 1220);
    BOOST_CHECK_EQUAL(askQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(askQuery1.getSide()), int(Side::Ask));

    askQuery2 = matcher.query(2, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery2.getQuantity(), 300);
    BOOST_CHECK_EQUAL(askQuery2.getPrice(), 1230);
    BOOST_CHECK_EQUAL(askQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(askQuery2.getSide()), int(Side::Ask));
}

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Basic_Amend_Price_Bid_Test ) {
    LimitOrderMatcher matcher;
    std::shared_ptr<Order> bidOrder1(new Order(1001, Side::Bid, 100, 1210));
    matcher.add(bidOrder1);
    std::shared_ptr<Order> bidOrder2(new Order(1002, Side::Bid, 2000, 1220));
    matcher.add(bidOrder2);
    std::shared_ptr<Order> bidOrder3(new Order(1003, Side::Bid, 300, 1230));
    matcher.add(bidOrder3);

    QueryResult bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 300);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 1230);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    QueryResult bidQuery1 = matcher.query(1, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery1.getQuantity(), 2000);
    BOOST_CHECK_EQUAL(bidQuery1.getPrice(), 1220);
    BOOST_CHECK_EQUAL(bidQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(bidQuery1.getSide()), int(Side::Bid));

    QueryResult bidQuery2 = matcher.query(2, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery2.getQuantity(), 100);
    BOOST_CHECK_EQUAL(bidQuery2.getPrice(), 1210);
    BOOST_CHECK_EQUAL(bidQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(bidQuery2.getSide()), int(Side::Bid));

    std::shared_ptr<Order> amendDownBidOrder2(new Order(1002, Side::Bid, 2000, 1200));
    matcher.amend(amendDownBidOrder2);

    bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 300);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 1230);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    bidQuery1 = matcher.query(1, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery1.getQuantity(), 100);
    BOOST_CHECK_EQUAL(bidQuery1.getPrice(), 1210);
    BOOST_CHECK_EQUAL(bidQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(bidQuery1.getSide()), int(Side::Bid));

    bidQuery2 = matcher.query(2, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery2.getQuantity(), 2000);
    BOOST_CHECK_EQUAL(bidQuery2.getPrice(), 1200);
    BOOST_CHECK_EQUAL(bidQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(bidQuery2.getSide()), int(Side::Bid));

    std::shared_ptr<Order> amendUpBidOrder2(new Order(1002, Side::Bid, 2000, 1240));
    matcher.amend(amendUpBidOrder2);

    bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 2000);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 1240);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    bidQuery1 = matcher.query(1, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery1.getQuantity(), 300);
    BOOST_CHECK_EQUAL(bidQuery1.getPrice(), 1230);
    BOOST_CHECK_EQUAL(bidQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(bidQuery1.getSide()), int(Side::Bid));

    bidQuery2 = matcher.query(2, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery2.getQuantity(), 100);
    BOOST_CHECK_EQUAL(bidQuery2.getPrice(), 1210);
    BOOST_CHECK_EQUAL(bidQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(bidQuery2.getSide()), int(Side::Bid));

}

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Basic_Amend_Price_Ask_Test ) {
    LimitOrderMatcher matcher;
    std::shared_ptr<Order> askOrder1(new Order(1001, Side::Ask, 100, 1210));
    matcher.add(askOrder1);
    std::shared_ptr<Order> askOrder2(new Order(1002, Side::Ask, 2000, 1220));
    matcher.add(askOrder2);
    std::shared_ptr<Order> askOrder3(new Order(1003, Side::Ask, 300, 1230));
    matcher.add(askOrder3);

    QueryResult askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 100);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 1210);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));

    QueryResult askQuery1 = matcher.query(1, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery1.getQuantity(), 2000);
    BOOST_CHECK_EQUAL(askQuery1.getPrice(), 1220);
    BOOST_CHECK_EQUAL(askQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(askQuery1.getSide()), int(Side::Ask));

    QueryResult askQuery2 = matcher.query(2, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery2.getQuantity(), 300);
    BOOST_CHECK_EQUAL(askQuery2.getPrice(), 1230);
    BOOST_CHECK_EQUAL(askQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(askQuery2.getSide()), int(Side::Ask));

    std::shared_ptr<Order> amendDownAskOrder2(new Order(1002, Side::Ask, 2000, 1200));
    matcher.amend(amendDownAskOrder2);

    askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 2000);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 1200);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));

    askQuery1 = matcher.query(1, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery1.getQuantity(), 100);
    BOOST_CHECK_EQUAL(askQuery1.getPrice(), 1210);
    BOOST_CHECK_EQUAL(askQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(askQuery1.getSide()), int(Side::Ask));

    askQuery2 = matcher.query(2, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery2.getQuantity(), 300);
    BOOST_CHECK_EQUAL(askQuery2.getPrice(), 1230);
    BOOST_CHECK_EQUAL(askQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(askQuery2.getSide()), int(Side::Ask));

    std::shared_ptr<Order> amendUpAskOrder2(new Order(1002, Side::Ask, 2000, 1240));
    matcher.amend(amendUpAskOrder2);

    askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 100);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 1210);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));

    askQuery1 = matcher.query(1, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery1.getQuantity(), 300);
    BOOST_CHECK_EQUAL(askQuery1.getPrice(), 1230);
    BOOST_CHECK_EQUAL(askQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(askQuery1.getSide()), int(Side::Ask));

    askQuery2 = matcher.query(2, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery2.getQuantity(), 2000);
    BOOST_CHECK_EQUAL(askQuery2.getPrice(), 1240);
    BOOST_CHECK_EQUAL(askQuery2.getLevel(), 2);
    BOOST_CHECK_EQUAL(int(askQuery2.getSide()), int(Side::Ask));
}

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Basic_Matching_Test ) {
    LimitOrderMatcher matcher;
    std::shared_ptr<Order> bidOrder1(new Order(1001, Side::Bid, 100, 1230));
    matcher.add(bidOrder1);
    std::shared_ptr<Order> askOrder1(new Order(1002, Side::Ask, 100, 1230));
    matcher.add(askOrder1);

    QueryResult bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 0);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 0);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    QueryResult askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 0);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 0);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));
}

BOOST_AUTO_TEST_CASE( LimitOrderMatcher_Basic_Matching_Test2 ) {
    LimitOrderMatcher matcher;
    std::shared_ptr<Order> bidOrder1(new Order(1001, Side::Bid, 500, 1230));
    matcher.add(bidOrder1);
    std::shared_ptr<Order> bidOrder2(new Order(1002, Side::Bid, 100, 1220));
    matcher.add(bidOrder2);

    QueryResult bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 500);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 1230);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    QueryResult bidQuery1 = matcher.query(1, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery1.getQuantity(), 100);
    BOOST_CHECK_EQUAL(bidQuery1.getPrice(), 1220);
    BOOST_CHECK_EQUAL(bidQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(bidQuery1.getSide()), int(Side::Bid));


    QueryResult askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 0);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 0);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));

    std::shared_ptr<Order> askOrder1(new Order(1003, Side::Ask, 100, 1220));
    matcher.add(askOrder1);

    bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 400);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 1230);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    bidQuery1 = matcher.query(1, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery1.getQuantity(), 100);
    BOOST_CHECK_EQUAL(bidQuery1.getPrice(), 1220);
    BOOST_CHECK_EQUAL(bidQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(bidQuery1.getSide()), int(Side::Bid));

    askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 0);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 0);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));

    std::shared_ptr<Order> askOrder2(new Order(1004, Side::Ask, 1000, 1220));
    matcher.add(askOrder2);

    bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 0);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 0);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    bidQuery1 = matcher.query(1, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery1.getQuantity(), 0);
    BOOST_CHECK_EQUAL(bidQuery1.getPrice(), 0);
    BOOST_CHECK_EQUAL(bidQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(bidQuery1.getSide()), int(Side::Bid));

    askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 500);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 1220);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));

    std::shared_ptr<Order> bidOrder3(new Order(1005, Side::Bid, 500, 1210));
    matcher.add(bidOrder3);
    std::shared_ptr<Order> bidOrder4(new Order(1006, Side::Bid, 500, 1220));
    matcher.add(bidOrder4);

    bidQuery0 = matcher.query(0, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery0.getQuantity(), 500);
    BOOST_CHECK_EQUAL(bidQuery0.getPrice(), 1210);
    BOOST_CHECK_EQUAL(bidQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(bidQuery0.getSide()), int(Side::Bid));

    bidQuery1 = matcher.query(1, Side::Bid);
    BOOST_CHECK_EQUAL(bidQuery1.getQuantity(), 0);
    BOOST_CHECK_EQUAL(bidQuery1.getPrice(), 0);
    BOOST_CHECK_EQUAL(bidQuery1.getLevel(), 1);
    BOOST_CHECK_EQUAL(int(bidQuery1.getSide()), int(Side::Bid));

    askQuery0 = matcher.query(0, Side::Ask);
    BOOST_CHECK_EQUAL(askQuery0.getQuantity(), 0);
    BOOST_CHECK_EQUAL(askQuery0.getPrice(), 0);
    BOOST_CHECK_EQUAL(askQuery0.getLevel(), 0);
    BOOST_CHECK_EQUAL(int(askQuery0.getSide()), int(Side::Ask));

}