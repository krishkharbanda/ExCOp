//
// Created by Krish on 6/14/25.
//

#include "project/Metrics.hpp"

double Metrics::computeSlippage(double exec, double arrival) {
    return ((exec - arrival) / arrival) * 100.0;
}
