//
// Created by Krish on 6/14/25.
//

#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>

class Order {
public:
    std::string side;
    double price;
    double quantity;

    Order(const std::string& s, double p, double q)
        : side(s), price(p), quantity(q) {}
};

#endif

