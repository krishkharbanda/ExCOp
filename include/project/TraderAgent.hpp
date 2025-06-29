//
// Created by Krish on 6/14/25.
//

#ifndef TRADERAGENT_HPP
#define TRADERAGENT_HPP

#include "OrderBook.hpp"
#include "Metrics.hpp"
#include "LiquidityModel.hpp"
#include <string>
#include <vector>

enum class StrategyType {
    TWAP,
    VWAP,
    SMART_ORDER_ROUTING,
    ADVERSE_SELECTION_AVOIDANCE,
    PREDICTIVE_LIQUIDITY
};

class TraderAgent {
public:
    TraderAgent(OrderBook& book, StrategyType strategy, int totalShares, int durationSec);

    void run();
    std::vector<Trade> getExecutionLog() const;

private:
    void runTWAP();
    void runSOR();
    void runAdverseSelection();
    void runPredictiveLiquidity();

    OrderBook& orderBook;
    StrategyType strategy;
    int totalShares;
    int durationSec;
    std::vector<Trade> executionLog;
};

#endif //TRADERAGENT_HPP
