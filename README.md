# Matcha

Matcha is a single-instrument order matching engine written in C++23. It implements a simple price-time priority book and includes a small interactive CLI for experimenting with order flow.

## Features

- buy and sell orders [LIMIT / MARKET]
- Price priority across levels
- FIFO priority within each price level
- Partial fills
- Multi-level matching
- Resting limit orders for any unfilled remainder

## Current Status

Supported today:

- Limit and market order matching
- Basic in-memory bid/ask book
- Displaying the current book state after input is processed

Not yet implemented:

- True cancel-order handling
- Order lookup by id
- Persistence or recovery
- Network or wire protocol support
- Benchmarking and latency tooling

## Build

```bash
mkdir build
cd build
cmake ..
make
```

## Run

The current executable is interactive and asks for orders on stdin.

```bash
./build/matcha
```

Input format for each order:

1. Order id
2. Order type: `0 = LIMIT`, `1 = MARKET`, `2 = CANCEL`
3. Order side: `0 = BUY`, `1 = SELL` if the order is not a cancel
4. Price: required for limit orders
5. Quantity

## Matching Rules

- Incoming buy orders match against the lowest available ask prices first.
- Incoming sell orders match against the highest available bid prices first.
- Orders at the same price level are matched in FIFO order.
- A market order consumes available liquidity and never rests in the book.
- A limit order rests in the book only if it is not fully filled.

## Project Layout

- `include/matcha/order.hpp` defines the order model and enums.
- `include/matcha/price_level.hpp` defines a price level and its FIFO queue.
- `include/matcha/order_book.hpp` defines the bid/ask book interface.
- `src/price_level.cpp` implements price-level matching and display logic.
- `src/order_book.cpp` implements cross-level matching and resting order insertion.
- `src/main.cpp` provides the interactive CLI demo.

## Architecture

OrderBook
├── bids : std::map<uint64_t, PriceLevel>
├── asks : std::map<uint64_t, PriceLevel>

PriceLevel
├── price
└── vector<Order*>

Order
├── id
├── side
├── order_type
├── price
└── qty

## Planned Improvements

- Cancel-order support
- Order lookup by id
- Arena allocator
- Intrusive FIFO linked lists
- Intrusive RB-tree
- Binary wire protocol
- TCP server
- Benchmarking