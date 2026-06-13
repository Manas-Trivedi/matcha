#include <cstdint>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <matcha/order.hpp>
#include <matcha/price_level.hpp>

bool PriceLevel::empty() {
    return order_queue.empty();
}

std::queue<uint64_t> PriceLevel::fill_order(Order *order) {
    std::stack<size_t> filled_orders;
    std::queue<uint64_t> matched_orders;
    for(size_t i = 0; i < order_queue.size(); i++) {
        if(order->qty == 0) break;
        uint64_t filledQty = std::min(order->qty, order_queue[i]->qty);
        order->qty -= filledQty;
        order_queue[i]->qty -= filledQty;
        if(order_queue[i]->qty == 0) {
            uint64_t order_id = order_queue[i]->id;
            matched_orders.push(order_id);
            filled_orders.push(i);
        }
    }
    while(!filled_orders.empty()) {
        size_t idx = filled_orders.top();
        order_queue.erase(order_queue.begin() + idx);
        filled_orders.pop();
    }
    return matched_orders;
}

void PriceLevel::add_order(Order *order) {
    if(order->price != price) {
        return;
    }
    order_queue.push_back(order);
}

bool PriceLevel::remove_order(uint64_t orderId) {
    for(size_t i = 0; i < order_queue.size(); i++) {
        if(order_queue[i]->id == orderId) {
            order_queue.erase(order_queue.begin() + i);
            return true;
        }
    }
    return false;
}

void PriceLevel::display_level() {
    std::cout << " [ " << price << " ]  -> ";
    for(size_t i = 0; i < order_queue.size(); i++) {
        std::cout << "( " << order_queue[i]->qty << ", " << order_queue[i]->id << " )";
        if(i != order_queue.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}
