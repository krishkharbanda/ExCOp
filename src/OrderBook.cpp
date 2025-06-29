//
// Created by Krish on 6/14/25.
//

#include "project/OrderBook.hpp"
#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void OrderBook::applySnapshot(const std::vector<std::pair<double, double>>& bidSnap,
                              const std::vector<std::pair<double, double>>& askSnap) {
    std::lock_guard<std::mutex> lock(bookMutex);
    bids.clear();
    asks.clear();
    for (const auto& [price, qty] : bidSnap) bids[price] = qty;
    for (const auto& [price, qty] : askSnap) asks[price] = qty;
}

void OrderBook::applyUpdate(const std::vector<std::pair<double, double>>& bidUpdates,
                            const std::vector<std::pair<double, double>>& askUpdates) {
    std::lock_guard<std::mutex> lock(bookMutex);

    for (const auto& [price, qty] : bidUpdates) {
        if (qty == 0) bids.erase(price);
        else bids[price] = qty;
    }

    for (const auto& [price, qty] : askUpdates) {
        if (qty == 0) asks.erase(price);
        else asks[price] = qty;
    }
}

void OrderBook::updateFromBinanceJson(const std::string& jsonStr) {
    std::lock_guard<std::mutex> lock(bookMutex);

    auto j = json::parse(jsonStr);

    auto parseSide = [](const json& sideJson) {
        std::map<double, double, std::greater<>> side;
        for (const auto& level : sideJson) {
            double price = std::stod(level[0].get<std::string>());
            double qty   = std::stod(level[1].get<std::string>());
            if (qty > 0)
                side[price] = qty;
        }
        return side;
    };

    bids = parseSide(j["b"]);
    asks = parseSide(j["a"]);
}

double OrderBook::getBestBid() const {
    std::lock_guard<std::mutex> lock(bookMutex);
    return bids.empty() ? 0.0 : bids.begin()->first;
}

double OrderBook::getBestAsk() const {
    std::lock_guard<std::mutex> lock(bookMutex);
    return asks.empty() ? 0.0 : asks.begin()->first;
}

double OrderBook::getVolumeWeightedPrice() const {
    std::lock_guard<std::mutex> lock(bookMutex);
    if (bids.empty() || asks.empty()) return 0.0;
    return (getBestBid() + getBestAsk()) / 2.0;
}

Trade OrderBook::executeMarketOrder(const std::string& side, int quantity) {
    std::lock_guard<std::mutex> lock(bookMutex);
    double price = (side == "BUY") ? getBestAsk() : getBestBid();
    return { side, price, quantity };
}

std::string OrderBook::placeLimitOrder(const std::string& side, double price, int quantity) {
    std::lock_guard<std::mutex> lock(bookMutex);
    if (side == "BUY") bids[price] += quantity;
    else asks[price] += quantity;
    return "order_" + std::to_string(rand());
}

bool OrderBook::cancelOrder(const std::string&) {
    return true;
}

bool OrderBook::detectAggressiveFlow() const {
    return rand() % 10 < 2;
}
