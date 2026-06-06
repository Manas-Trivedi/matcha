#include <cstdint>
#include <stack>
#include <map>
#include <iostream>
#include <matcha/order.hpp>
#include <matcha/price_level.hpp>
#include <matcha/order_book.hpp>

void OrderBook::matchOrder(Order *order) {
    std::stack<uint64_t> emptyLevels;
    uint64_t price;
    if(order->order_type == OrderType::LIMIT) {
        price = order->price;
    }
    else if(order->order_type == OrderType::MARKET){
        if(order->side == Side::BUY) price = UINT64_MAX;
        else price = 0;
    }
    if(order->side == Side::BUY) {
        auto it = asks.begin();
        while(it != asks.end() && it->first <= price && order->qty > 0) {
            it->second.fillOrder(order);
            if(it->second.empty()) emptyLevels.push(it->first);
            it++;
        }
        while(!emptyLevels.empty()) {
            uint64_t key = emptyLevels.top();
            asks.erase(key);
            emptyLevels.pop();
        }
    } else {
        auto it = bids.rbegin();
        while(it != bids.rend() && it->first >= price && order->qty > 0) {
            it->second.fillOrder(order);
            if(it->second.empty()) emptyLevels.push(it->first);
            it++;
        }
        while(!emptyLevels.empty()) {
            uint64_t key = emptyLevels.top();
            bids.erase(key);
            emptyLevels.pop();
        }
    }
}

void OrderBook::insertOrder(Order *order) {
    if(!order) {
        return;
    }

    if(order->order_type != OrderType::CANCEL)matchOrder(order);
    if(order->qty == 0 || order->order_type == OrderType::MARKET) return;
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
     std::cout << " [ price ]  -> ";
        std::cout << "( qty, id )";
    std::cout << "\n";
    std::cout << "BIDS::\n";
    for(auto &it: bids) {
        it.second.displayLevel();
    }
    std::cout << "ASKS::\n";
    for(auto &it: asks) {
        it.second.displayLevel();
    }
}