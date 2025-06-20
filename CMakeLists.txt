cmake_minimum_required(VERSION 3.10)
project(ExCOp)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

include_directories(
        include
        /usr/local/include
        ${OPENSSL_INCLUDE_DIR}
)

link_directories(
        /usr/local/lib
        ${OPENSSL_LIBRARIES}
)

add_executable(binance_exec
        src/main.cpp
        src/BinanceConnector.cpp
)

if(APPLE)
    target_link_libraries(binance_exec
            ixwebsocket
            "-framework CoreFoundation"
            "-framework Security"
            pthread
            z
    )
else()
    target_link_libraries(binance_exec
            ixwebsocket
            ${OPENSSL_LIBRARIES}
            pthread
            z
    )
endif()

