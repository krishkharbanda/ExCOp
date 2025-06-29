//
// Created by Krish on 6/14/25.
//

#include "project/StrategySimulator.hpp"
#include "project/BinanceConnector.hpp"

void StrategySimulator::simulateTWAP(int qty, int intervals) {
    OrderBook book;
    TraderAgent agent;

    BinanceConnector connector;
    connector.connect([&](const std::string& msg) {
        std::cout << "Market data: " << msg << std::endl;
    });

    agent.runTWAP(book, qty, intervals);
}
