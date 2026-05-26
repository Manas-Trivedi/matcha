#include <cstdint>
#include <map>
#include <iostream>
#include <matcha/order.hpp>
#include <matcha/price_level.hpp>
#include <matcha/order_book.hpp>

void OrderBook::insertOrder(Order *order) {
    if(!order) {
        return;
    }

    uint64_t price = order->price;
    if(order->side == Side::BUY) {
        if(bids.find(price) == bids.end()) {
            bids.insert({price, PriceLevel(price)});
        }
        bids.at(price).addOrder(order);
    } else {
        if(asks.find(price) == asks.end()) {
            asks.insert({price, PriceLevel(price)});
        }
        asks.at(price).addOrder(order);
    }
}

void OrderBook::displayBook() {
    std::cout << "BIDS::\n";
    for(auto &it: bids) {
        it.second.displayLevel();
    }
    std::cout << "ASKS::\n";
    for(auto &it: asks) {
        it.second.displayLevel();
    }
}