#pragma once
#include <cstdint>
#include <vector>
#include <matcha/order.hpp>

class PriceLevel {
    uint64_t price;
    std::vector<Order*> orderQueue;
    public:
    PriceLevel(uint64_t p) : price( p ) {}
    void addOrder(Order*);
    bool removeOrder(uint64_t);
    void fillOrder(Order*);
    bool empty();
    void displayLevel();
};
