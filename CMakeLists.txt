#CMakeLists.txt

cmake_minimum_required(VERSION 2.8)
project(OrderBook)
find_package(Boost COMPONENTS system unit_test_framework REQUIRED)

add_executable(order_book 
     src/main.cpp
     src/OrderInputManager.cpp
     src/LimitOrderMatcher.cpp
)

set(ORDER_TEST order_book_test)
add_executable(${ORDER_TEST} 
     test/OrderTester.cpp
     src/LimitOrderMatcher.cpp
     test/LimitOrderMatcherTester.cpp
     )                    
target_link_libraries(${ORDER_TEST}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      )
add_custom_command(
     TARGET ${ORDER_TEST}
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND ${ORDER_TEST}
)