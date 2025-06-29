//
// Created by Krish on 6/14/25.
//

#ifndef STRATEGYSIMULATOR_HPP
#define STRATEGYSIMULATOR_HPP

#include "OrderBook.hpp"
#include "TraderAgent.hpp"

class StrategySimulator {
public:
    void simulateTWAP(int qty, int intervals);
};

#endif //STRATEGYSIMULATOR_HPP
