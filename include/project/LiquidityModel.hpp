//
// Created by Krish on 6/28/25.
//

#ifndef LIQUIDITYMODEL_HPP
#define LIQUIDITYMODEL_HPP

#include "OrderBook.hpp"

class LiquidityModel {
public:
    double forecastFillProbability(const OrderBook& ob) const;
};

#endif //LIQUIDITYMODEL_HPP
