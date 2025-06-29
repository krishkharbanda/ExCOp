
# 🚀 Execution Cost Optimizer (ExCOp)

**Execution Cost Optimizer** is a high-performance C++ simulation framework designed to model and evaluate algorithmic order execution strategies in real-time markets. It includes a custom order book, strategy engine, and live Binance integration using `IXWebSocket`.

---

## 📁 Project Structure

```

ExCOp/
├── include/
│   └── project/
│       ├── BinanceConnector.hpp
│       ├── LiquidityModel.hpp
│       ├── Metrics.hpp
│       ├── Order.hpp
│       ├── OrderBook.hpp
│       ├── StrategySimulator.hpp
│       └── TraderAgent.hpp
│   └── IXWebSocket/     # IXWebSocket headers
│   └── nlohmann/        # nlohmann/json headers
├── src/
│   ├── BinanceConnector.cpp
│   ├── LiquidityModel.cpp
│   ├── main.cpp
│   ├── Metrics.cpp
│   ├── Order.cpp
│   ├── OrderBook.cpp
│   ├── StrategySimulator.cpp
│   └── TraderAgent.cpp
├── tests/
├── .gitignore
├── CMakeLists.txt
├── LICENSE
└── README.md

````

---

## ⚙️ Features

- ✅ **Order Book Simulation** — full bid/ask book with live updates
- 📡 **Live Binance Integration** — real-time market data via WebSocket
- 🧠 **Execution Strategies**:
  - TWAP (Time-Weighted Average Price)
  - VWAP (Volume-Weighted Average Price)
  - Smart Order Routing (SOR)
  - Adverse Selection Avoidance
  - Predictive Liquidity Modeling
- 📊 **Metrics Engine** — calculates slippage, fill rate, and more
- 🔧 **Modular Design** — plug-and-play components for extensibility

---

## 🔌 Dependencies

- C++17
- [IXWebSocket](https://github.com/machinezone/IXWebSocket)
- OpenSSL (required for WebSocket TLS)
- CMake ≥ 3.10
- `nlohmann/json` (for optional structured logging)

---

## 🧪 Build Instructions

```bash
# Clone
git clone https://github.com/krishkharbanda/ExCOp.git
cd ExCOp

# Create build directory
mkdir build && cd build

# Configure
cmake ..

# Build
make -j

# Run
./binance_exec
````

---

## 📈 Example Run

```bash
./binance_exec

Connecting to Binance stream: wss://stream.binance.com:9443/ws/btcusdt@depth5
[1/10] Executed market buy @ $61,254.3 for 100 shares
...
[10/10] Strategy complete.
[✔] Slippage: 0.12%
[✔] Fill rate: 100%
```

---

## 🧠 Strategy Descriptions

| Strategy                     | Description                                                               |
| ---------------------------- | ------------------------------------------------------------------------- |
| **TWAP**                     | Executes slices evenly over a time horizon                                |
| **VWAP**                     | Executes when price is favorable relative to recent volume-weighted price |
| **Smart Order Routing**      | Places limit or market orders based on spread conditions                  |
| **Adverse Selection Avoid.** | Cancels if flow appears aggressive                                        |
| **Predictive Liquidity**     | Uses a custom model to predict fill success                               |

---

## 📊 Metrics Tracked

* **Slippage** = Relative difference from arrival price
* **Fill Rate** = Filled shares / total requested
* **Avg Exec Price** = Weighted average across all trades
* **Spread Analysis** = Used in SOR and Predictive Liquidity

---

## 🧱 Modules Overview

| File                        | Purpose                                      |
| --------------------------- | -------------------------------------------- |
| `OrderBook.hpp/cpp`         | Simulates a limit order book                 |
| `TraderAgent.hpp/cpp`       | Implements execution logic for each strategy |
| `BinanceConnector.hpp/cpp`  | Streams live data from Binance WebSocket     |
| `LiquidityModel.hpp/cpp`    | Predicts fill probability                    |
| `Metrics.hpp/cpp`           | Tracks performance metrics                   |
| `StrategySimulator.hpp/cpp` | Runs strategy and aggregates results         |
| `main.cpp`                  | CLI driver to launch simulation              |

---

## 📌 TODOs / Extensions

* [ ] Logging with timestamps and JSON format
* [ ] Support for multiple tickers
* [ ] UI Dashboard for real-time analytics (e.g. Qt or Python backend)
* [ ] Order Book visualization
* [ ] Reinforcement learning strategy wrapper

---

## 📄 License

MIT License © 2025 Krish Kharbanda

---

## 💬 Contact

For questions or collaboration inquiries, reach out to:

**Krish Kharbanda**

- 📧 [kharbandakrish23@gmail.com](mailto:kharbandakrish23@gmail.com)

- in [https://www.linkedin.com/in/krishkharbanda](https://www.linkedin.com/in/krishkharbanda)

---