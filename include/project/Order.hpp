//
// Created by Krish on 6/14/25.
//

#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>

enum class OrderType { MARKET, LIMIT };
enum class OrderSide { BUY, SELL };

struct Order {
    int id;
    OrderType type;
    OrderSide side;
    double price;
    int quantity;
    long timestamp;

    Order(int id, OrderType t, OrderSide s, double p, int q, long ts);
};

#endif //ORDER_HPP

