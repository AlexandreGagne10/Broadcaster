#pragma once
#include <vector>
#include <cstdint>

class Encoder {
public:
    virtual ~Encoder() = default;
    virtual std::vector<uint8_t> encode(const std::vector<uint8_t>& data) = 0;
};

class IdentityEncoder : public Encoder {
public:
    std::vector<uint8_t> encode(const std::vector<uint8_t>& data) override { return data; }
};
