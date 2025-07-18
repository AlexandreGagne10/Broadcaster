#pragma once
#include <vector>
#include <cstdint>

class SignalAnalyzer {
public:
    virtual ~SignalAnalyzer() = default;
    virtual void analyze(const std::vector<uint8_t>& data) = 0;
};

class SimpleLogger : public SignalAnalyzer {
public:
    void analyze(const std::vector<uint8_t>& data) override;
};
