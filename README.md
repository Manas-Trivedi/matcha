# Matcha

A single-instrument limit order matching engine written in C++.

## Current implementation:

- Limit buy orders
- Limit sell orders
- FIFO within each price level
- Price priority across levels
- Partial fills
- Multi-level matching

## Architecture:

OrderBook
├── bids : std::map<uint64_t, PriceLevel>
├── asks : std::map<uint64_t, PriceLevel>

PriceLevel
├── price
└── vector<Order*>

Order
├── id
├── side
├── type
├── price
└── qty

## Matching Rules

- Incoming BUY orders match against the lowest available ASK prices.
- Incoming SELL orders match against the highest available BID prices.
- Within the same price level, orders are matched in FIFO order.
- Any unfilled quantity from a LIMIT order rests in the book.

## Planned Improvements

- Market orders
- Cancel orders
- Arena allocator
- Intrusive FIFO linked lists
- Intrusive RB-tree / dense price ladder exploration
- Binary wire protocol
- TCP server
- Benchmarking