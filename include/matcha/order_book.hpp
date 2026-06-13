#pragma once
#include <cstdint>
#include <map>
#include <unordered_map>
#include <matcha/order.hpp>
#include <matcha/price_level.hpp>

class OrderBook {
    std::map<uint64_t, PriceLevel> bids;
    std::map<uint64_t, PriceLevel> asks;
    std::unordered_map<uint64_t, Order*> order_lookup;
    void match_order(Order *order);
    public:
    void insert_order(Order *order);
    void cancel_order(uint64_t order_id);
    void display_book();
};
