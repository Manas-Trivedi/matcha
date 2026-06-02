#include <cstdint>
#include <stack>
#include <vector>
#include <iostream>
#include <matcha/order.hpp>
#include <matcha/price_level.hpp>

bool PriceLevel::empty() {
    return orderQueue.empty();
}

void PriceLevel::fillOrder(Order *order) {
    std::stack<size_t> filledOrders;
    for(size_t i = 0; i < orderQueue.size(); i++) {
        if(order->qty == 0) break;
        if(orderQueue[i]->qty == 0) continue;
        uint64_t filledQty = std::min(order->qty, orderQueue[i]->qty);
        order->qty -= filledQty;
        orderQueue[i]->qty -= filledQty;
        if(orderQueue[i]->qty == 0) filledOrders.push(i);
    }
    while(!filledOrders.empty()) {
        int idx = filledOrders.top();
        orderQueue.erase(orderQueue.begin() + idx);
        filledOrders.pop();
    }
}

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
        std::cout << "( " << orderQueue[i]->qty << ", " << orderQueue[i]->id << " )";
        if(i != orderQueue.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}
