#pragma once
#include <cstdint>
#include <map>
#include <matcha/order.hpp>
#include <matcha/price_level.hpp>

class OrderBook {
    std::map<uint64_t, PriceLevel> bids;
    std::map<uint64_t, PriceLevel> asks;

    public:
    void insertOrder(Order *order);
    void displayBook();
};
