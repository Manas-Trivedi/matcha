#pragma once

#include <vector>
#include <cstdint>
#include <matcha/order.hpp>

class Arena {
private:
    std::vector<Order> storage;
    size_t next_free;
public:
    Arena(size_t);
    Order* allocate();
    bool full() const;
};