//
// Created by Krish on 6/28/25.
//

#include "project/LiquidityModel.hpp"
#include <cmath>

double LiquidityModel::forecastFillProbability(const OrderBook& ob) const {
    double bid = ob.getBestBid();
    double ask = ob.getBestAsk();

    if (bid == 0 || ask == 0) return 0.0;

    double spread = ask - bid;
    double mid = (ask + bid) / 2.0;

    double spreadRatio = spread / mid;

    double prob = std::exp(-spreadRatio * 50.0);

    if (ob.detectAggressiveFlow()) {
        prob += 0.1;
    }

    return std::min(1.0, std::max(0.0, prob));
}
