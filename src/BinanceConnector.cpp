//
// Created by Krish on 6/14/25.
//
#include "project/BinanceConnector.hpp"
#include "project/OrderBook.hpp"
#include <IXWebSocket/IXWebSocket.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

using json = nlohmann::json;

BinanceConnector::BinanceConnector(OrderBook* ob) : orderBook(ob) {}

void BinanceConnector::connect() {
    ix::WebSocket ws;
    std::string endpoint = "wss://stream.binance.com:9443/ws/btcusdt@depth5";

    ws.setUrl(endpoint);
    std::cout << "Connecting to Binance stream: " << endpoint << std::endl;

    std::atomic<bool> done{false};

    ws.setOnMessageCallback([&](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Message) {
            try {
                orderBook->updateFromBinanceJson(msg->str);

                double vwap = orderBook->getVolumeWeightedPrice();
                std::cout << "[VWAP]: $" << vwap << std::endl;

                if (orderBook->detectAggressiveFlow()) {
                    std::cout << "Aggressive flow detected. Executing mock market order." << std::endl;
                    Trade trade = orderBook->executeMarketOrder("BUY", 10);
                    std::cout << "Executed: " << trade.side << " " << trade.quantity << " @ $" << trade.price << "\n";
                }

            } catch (const std::exception& e) {
                std::cerr << "JSON parse error: " << e.what() << std::endl;
            }

        } else if (msg->type == ix::WebSocketMessageType::Error) {
            std::cerr << "WebSocket error: " << msg->errorInfo.reason << std::endl;
            done = true;
            ws.stop();
        }
    });

    ws.start();

    while (!done) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Connection closed.\n";
}

