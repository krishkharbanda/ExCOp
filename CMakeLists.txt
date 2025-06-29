cmake_minimum_required(VERSION 3.10)
project(ExCOp)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/project)
include_directories(${CMAKE_SOURCE_DIR}/include/nlohmann)
include_directories(${CMAKE_SOURCE_DIR}/include/IXWebSocket)

find_package(OpenSSL REQUIRED)
include_directories(/opt/homebrew/opt/openssl@3/include)
link_directories(/opt/homebrew/opt/openssl@3/lib)

add_executable(binance_exec
        src/main.cpp
        src/BinanceConnector.cpp
        src/LiquidityModel.cpp
        src/Order.cpp
        src/OrderBook.cpp
        src/TraderAgent.cpp
        src/Metrics.cpp
        src/StrategySimulator.cpp
)

if(APPLE)
    target_link_libraries(binance_exec
            ixwebsocket
            OpenSSL::SSL
            OpenSSL::Crypto
            "-framework CoreFoundation"
            "-framework Security"
            pthread
            z
    )
else()
    target_link_libraries(binance_exec
            ixwebsocket
            OpenSSL::SSL
            OpenSSL::Crypto
            pthread
            z
    )
endif()
