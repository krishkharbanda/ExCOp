//
// Created by Krish on 6/14/25.
//

#include "project/Order.hpp"

Order::Order(int id, OrderType t, OrderSide s, double p, int q, long ts)
    : id(id), type(t), side(s), price(p), quantity(q), timestamp(ts) {}
