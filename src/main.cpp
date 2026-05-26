#include <cstdint>
#include <vector>
#include <iostream>
#include <matcha/order.hpp>
#include <matcha/price_level.hpp>
#include <matcha/order_book.hpp>

void takeOrder(Order &order) {
    std::cout << "Enter order id::";
    std::cin >> order.id;
    std::cout << "Enter order side(0/1)::";
    int side, order_type;
    std::cin >> side;
    order.side = (side == 0) ? Side::BUY : Side::SELL;
    std::cout << "Enter order type(0/1/2)::";
    std::cin >> order_type;
    order.order_type = (order_type == 0) ? OrderType::LIMIT : (order_type == 1 ? OrderType::MARKET : OrderType::CANCEL);
    std::cout << "Enter order price::";
    std::cin >> order.price;
    std::cout << "Enter order quantity::";
    std::cin >> order.qty;
}

int main() {
    OrderBook book;
    std::cout << "Enter nummber of orders: ";
    int n;
    std::cin >> n;
    std::vector<Order> orders(n);
    for(size_t i = 0; i < n; i++) {
        takeOrder(orders[i]);
        book.insertOrder(&orders[i]);
    }
    book.displayBook();
    return 0;
}