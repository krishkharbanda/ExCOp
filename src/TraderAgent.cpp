//
// Created by Krish on 6/14/25.
//

#include "project/TraderAgent.hpp"
#include "project/Order.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

TraderAgent::TraderAgent(OrderBook& book, StrategyType strat, int shares, int dur)
    : orderBook(book), strategy(strat), totalShares(shares), durationSec(dur) {}

void TraderAgent::run() {
    switch (strategy) {
        case StrategyType::TWAP: runTWAP(); break;
        case StrategyType::VWAP: runVWAP(); break;
        case StrategyType::SMART_ORDER_ROUTING: runSOR(); break;
        case StrategyType::ADVERSE_SELECTION_AVOIDANCE: runAdverseSelection(); break;
        case StrategyType::PREDICTIVE_LIQUIDITY: runPredictiveLiquidity(); break;
        default: std::cerr << "Unknown strategy." << std::endl;
    }
}

void TraderAgent::runTWAP() {
    int interval = durationSec / 10;
    int sizePerSlice = totalShares / 10;

    for (int i = 0; i < 10; ++i) {
        auto trade = orderBook.executeMarketOrder("BUY", sizePerSlice);
        executionLog.push_back(trade);
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}

void TraderAgent::runVWAP() {
    int interval = durationSec / 10;
    int sizePerSlice = totalShares / 10;

    for (int i = 0; i < 10; ++i) {
        double avgPrice = orderBook.getVolumeWeightedPrice();
        if (orderBook.getBestAsk() <= avgPrice * 1.01) {
            auto trade = orderBook.executeMarketOrder("BUY", sizePerSlice);
            executionLog.push_back(trade);
        }
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}

void TraderAgent::runSOR() {
    int remaining = totalShares;
    while (remaining > 0) {
        auto spread = orderBook.getSpread();
        if (spread < 0.02) {
            auto trade = orderBook.executeMarketOrder("BUY", 100);
            remaining -= trade.quantity;
            executionLog.push_back(trade);
        } else {
            orderBook.placeLimitOrder("BUY", orderBook.getBestBid() + 0.01, 100);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void TraderAgent::runAdverseSelection() {
    std::string orderId = orderBook.placeLimitOrder("BUY", orderBook.getBestBid() + 0.01, 100);
    for (int i = 0; i < 30; ++i) {
        if (orderBook.detectAggressiveFlow()) {
            orderBook.cancelOrder(orderId);
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void TraderAgent::runPredictiveLiquidity() {
    LiquidityModel model;
    int batch = totalShares / 10;

    for (int i = 0; i < 10; ++i) {
        if (model.forecastFillProbability(orderBook) > 0.8) {
            auto trade = orderBook.executeMarketOrder("BUY", batch);
            executionLog.push_back(trade);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

std::vector<Trade> TraderAgent::getExecutionLog() const {
    return executionLog;
}