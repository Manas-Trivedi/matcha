#include <cstdint>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <matcha/order.hpp>
#include <matcha/price_level.hpp>

bool PriceLevel::empty_dll() {
    return head == nullptr;
}

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

std::queue<uint64_t> PriceLevel::fill_order_dll(Order *order) {
    std::queue<uint64_t> matched_orders;
    Order *tmp = head;
    while(tmp && order->qty > 0) {
        uint64_t filledQty = std::min(order->qty, tmp->qty);
        order->qty -= filledQty;
        tmp->qty -= filledQty;
        if(tmp->qty == 0) {
            Order *delOrder = tmp;
            tmp = tmp->next;
            matched_orders.push(delOrder->id);
            remove_order_dll(delOrder);
            continue;
        }
        tmp = tmp->next;
    }
    return matched_orders;
}

void PriceLevel::add_order(Order *order) {
    if(order->price != price) {
        return;
    }
    order_queue.push_back(order);
}

void PriceLevel::add_order_dll(Order *order) {
    order->prev = nullptr;
    order->next = nullptr;
    if(head == nullptr) {
        head = order;
        tail = order;
    } else {
        order->prev = tail;
        tail->next = order;
        tail = order;
    }
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

void PriceLevel::remove_order_dll(Order *order) {
    if(order == head && order == tail) {
        head = nullptr;
        tail = nullptr;
    } else if(head == order) {
        head = order->next;
        head->prev = nullptr;
    } else if(tail == order) {
        tail = order->prev;
        tail->next = nullptr;
    } else {
        order->prev->next = order->next;
        order->next->prev = order->prev;
    }
    order->next = nullptr;
    order->prev = nullptr;
}

void PriceLevel::display_level() {
    std::cout << " [ " << price << " ]  -> ";
    for(size_t i = 0; i < order_queue.size(); i++) {
        std::cout << "( " << order_queue[i]->qty << ", " << order_queue[i]->id << " )";
        if(i != order_queue.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}

void PriceLevel::display_level_dll() {
    std::cout << " [ " << price << " ]  -> ";
    Order *tmp = head;
    while(tmp) {
        std::cout << "( " << tmp->qty << ", " << tmp->id << " )";
        if(tmp->next) std::cout << ", ";
        tmp = tmp->next;
    }
    std::cout << "\n";
}
