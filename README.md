# Broadcaster

This project provides a minimal provider/receiver example using Boost.Asio.

## Building

```
g++ -std=c++17 src/provider.cpp src/signal_analysis.cpp src/hdmi.cpp -o provider -lboost_system
g++ -std=c++17 src/receiver.cpp src/signal_analysis.cpp src/hdmi.cpp -o receiver -lboost_system
```

## Running
1. Start the provider:
   ```
   ./provider
   ```
2. Run the receiver in another terminal:
   ```
   ./receiver
   ```

