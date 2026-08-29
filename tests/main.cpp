#include <gtest/gtest.h>
#include <matcha/order_book.hpp>

TEST(OrderBookTest, LimitOrderRests) {
    OrderBook book(10);

    Order order;
    order.id = 1;
    order.side = Side::BUY;
    order.order_type = OrderType::LIMIT;
    order.price = 100;
    order.qty = 5;

    book.insert_order(order);
    EXPECT_TRUE(book.contains_order(1));
}