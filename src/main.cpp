#include <cstdint>
#include <vector>
#include <iostream>
#include <matcha/order.hpp>
#include <matcha/price_level.hpp>
#include <matcha/order_book.hpp>

void takeOrder(Order &order) {
    std::cout << "Enter order id::";
    std::cin >> order.id;
    uint64_t order_type;
    std::cout << "Enter order type(0/1/2)::";
    std::cin >> order_type;
    order.order_type = (order_type == 0) ? OrderType::LIMIT : (order_type == 1 ? OrderType::MARKET : OrderType::CANCEL);
    if(order_type != 2) {
        std::cout << "Enter order side(0/1)::";
        uint64_t side;
        std::cin >> side;
        order.side = (side == 0) ? Side::BUY : Side::SELL;
        if(order_type != 1) {
            std::cout << "Enter order price::";
            std::cin >> order.price;
        }
        std::cout << "Enter order quantity::";
        std::cin >> order.qty;
    }
}

int main() {
    OrderBook book;
    std::cout << "Enter nummber of orders: ";
    int n;
    std::cin >> n;
    std::vector<Order> orders(n);
    for(size_t i = 0; i < n; i++) {
        takeOrder(orders[i]);
        book.insert_order(&orders[i]);
    }
    book.display_book();
    return 0;
}