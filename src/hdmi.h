#pragma once
#include <vector>
#include <cstdint>
#include <iostream>

class HDMIOutput {
public:
    bool connect();
    void sendFrame(const std::vector<uint8_t>& frame);
};

class HDMIInput {
public:
    bool connect();
    std::vector<uint8_t> receiveFrame();
};
