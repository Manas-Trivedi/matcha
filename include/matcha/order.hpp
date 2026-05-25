#pragma once
#include <cstdint>

enum class Side {
    BUY,
    SELL
};

enum class OrderType {
    LIMIT,
    MARKET,
    CANCEL
};

struct Order{
    uint64_t id;
    Side side;
    OrderType order_type;
    uint64_t price; // integer tics
    uint64_t qty; // current remaining qty
};