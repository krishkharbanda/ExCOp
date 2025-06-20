//
// Created by Krish on 6/14/25.
//

#include "project/BinanceConnector.hpp"
#include <IXWebSocket/ixwebsocket/IXWebSocket.h>
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

void BinanceConnector::connect()
{
    ix::WebSocket ws;
    std::string endpoint = "wss://stream.binance.com:9443/ws/btcusdt@depth5";

    ix::WebSocketHttpHeaders headers;
    headers["User-Agent"] = "Mozilla/5.0";
    headers["Origin"] = "https://stream.binance.com";
    ws.setExtraHeaders(headers);

    ws.setUrl(endpoint);

    std::cout << "Connecting to Binance stream: " << endpoint << std::endl;

    std::atomic<int> messageCount{0};
    const int maxMessages = 10;
    std::atomic<bool> done{false};

    ws.setOnMessageCallback([&](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Message) {
            std::cout << "Message " << messageCount + 1 << ":\n" << msg->str << std::endl;
            if (++messageCount >= maxMessages) {
                done = true;
                ws.stop();
            }
        } else if (msg->type == ix::WebSocketMessageType::Error) {
            std::cerr << "Error: " << msg->errorInfo.reason << std::endl;
            done = true;
            ws.stop();
        }
    });

    try {
        ws.start();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        done = true;
    }

    while (!done) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Connection closed." << std::endl;
}
