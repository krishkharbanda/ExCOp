//
// Created by Krish on 6/14/25.
//

#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include <map>
#include <string>
#include <vector>
#include <mutex>

struct Trade {
    std::string side;
    double price;
    int quantity;
};

class OrderBook {
public:
    void applySnapshot(const std::vector<std::pair<double, double>>& bids,
                       const std::vector<std::pair<double, double>>& asks);

    void applyUpdate(const std::vector<std::pair<double, double>>& bidUpdates,
                     const std::vector<std::pair<double, double>>& askUpdates);
	void updateFromBinanceJson(const std::string& jsonStr);

    double getBestBid() const;
    double getBestAsk() const;
    double getVolumeWeightedPrice() const;

    Trade executeMarketOrder(const std::string& side, int quantity);
    std::string placeLimitOrder(const std::string& side, double price, int quantity);
    bool cancelOrder(const std::string& orderId);
    bool detectAggressiveFlow() const;

private:
    std::map<double, double, std::greater<>> bids;
    std::map<double, double> asks;
    mutable std::mutex bookMutex;
};

#endif // ORDERBOOK_HPP



#endif //ORDERBOOK_HPP
