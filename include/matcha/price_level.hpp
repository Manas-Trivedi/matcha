#pragma once
#include <cstdint>
#include <vector>
#include <matcha/order.hpp>

class PriceLevel {
    uint64_t price;
    std::vector<Order*> order_queue;
    public:
    PriceLevel(uint64_t p) : price( p ) {}
    void add_order(Order*);
    bool remove_order(uint64_t);
    void fill_order(Order*);
    bool empty();
    void display_level();
};
