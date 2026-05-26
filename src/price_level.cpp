#include <cstdint>
#include <vector>
#include <iostream>
#include <matcha/order.hpp>
#include <matcha/price_level.hpp>

void PriceLevel::addOrder(Order *order) {
    if(order->price != price) {
        return;
    }
    orderQueue.push_back(order);
}

bool PriceLevel::removeOrder(uint64_t orderId) {
    for(size_t i = 0; i < orderQueue.size(); i++) {
        if(orderQueue[i]->id == orderId) {
            orderQueue.erase(orderQueue.begin() + i);
            return true;
        }
    }
    return false;
}

void PriceLevel::displayLevel() {
    std::cout << " [ " << price << " ]  -> ";
    for(size_t i = 0; i < orderQueue.size(); i++) {
        std::cout << "( " << orderQueue[i]->id << ", " << orderQueue[i]->qty << " )";
        if(i != orderQueue.size() - 1) std::cout << ", ";
        else std::cout << "\n";
    }
}
