#include <cstdint>
#include <cassert>
#include <vector>
#include <matcha/order.hpp>
#include <matcha/arena.hpp>

Arena::Arena(size_t capacity)
    :   storage(capacity),
        next_free(0)
{
    assert(capacity > 0);
}

Order* Arena::allocate() {
    assert(!full());
    return &storage[next_free++];
}

bool Arena::full() const {
    return next_free >= storage.size();
}