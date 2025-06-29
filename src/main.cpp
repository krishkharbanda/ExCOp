//
// Created by Krish on 6/14/25.
//

#include "project/BinanceConnector.hpp"
#include "project/OrderBook.hpp"
#include "project/OrderBook.hpp"
#include "project/TraderAgent.hpp"
#include "project/BinanceConnector.hpp"
#include <iostream>
#include <string>

int main() {
    std::string strategyInput;
    std::cout << "Select strategy (TWAP, VWAP, SOR, ASA, PLIQ): ";
    std::cin >> strategyInput;

    StrategyType strategy;
    if (strategyInput == "TWAP") strategy = StrategyType::TWAP;
    else if (strategyInput == "VWAP") strategy = StrategyType::VWAP;
    else if (strategyInput == "SOR") strategy = StrategyType::SMART_ORDER_ROUTING;
    else if (strategyInput == "ASA") strategy = StrategyType::ADVERSE_SELECTION_AVOIDANCE;
    else if (strategyInput == "PLIQ") strategy = StrategyType::PREDICTIVE_LIQUIDITY;
    else {
        std::cerr << "Invalid strategy!" << std::endl;
        return 1;
    }

    int shares, duration;
    std::cout << "Enter number of shares to buy: ";
    std::cin >> shares;
    std::cout << "Enter duration (seconds): ";
    std::cin >> duration;

    OrderBook orderBook;
    BinanceConnector connector(orderBook);
    std::thread feedThread([&]() { connector.connect(); });

    std::this_thread::sleep_for(std::chrono::seconds(3));

    TraderAgent agent(orderBook, strategy, shares, duration);
    agent.run();

    connector.stop();
    if (feedThread.joinable()) feedThread.join();

    auto log = agent.getExecutionLog();
    double totalCost = 0;
    int filledShares = 0;

    for (const auto& trade : log) {
        std::cout << "Executed " << trade.quantity << " shares at $" << trade.price << std::endl;
        totalCost += trade.price * trade.quantity;
        filledShares += trade.quantity;
    }

    if (filledShares > 0) {
        double avgPrice = totalCost / filledShares;
        std::cout << "\nSummary:\n";
        std::cout << "Total shares filled: " << filledShares << "/" << shares << std::endl;
        std::cout << "Average execution price: $" << avgPrice << std::endl;
    } else {
        std::cout << "No trades were executed.\n";
    }

    return 0;
}
