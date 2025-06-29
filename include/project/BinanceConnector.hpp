//
// Created by Krish on 6/14/25.
//

#ifndef BINANCE_CONNECTOR_HPP
#define BINANCE_CONNECTOR_HPP

#include "OrderBook.hpp"
#include <string>

class BinanceConnector {
public:
    explicit BinanceConnector(OrderBook* ob);
    void connect();

private:
    OrderBook* orderBook;
};

#endif //BINANCE_CONNECTOR_HPP
