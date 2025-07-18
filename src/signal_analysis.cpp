#include "signal_analysis.h"
#include <iostream>

void SimpleLogger::analyze(const std::vector<uint8_t>& data) {
    std::cout << "Analyzing data of size " << data.size() << std::endl;
}
