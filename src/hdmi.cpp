#include "hdmi.h"

bool HDMIOutput::connect() {
    std::cout << "HDMI output connected." << std::endl;
    return true;
}

void HDMIOutput::sendFrame(const std::vector<uint8_t>& frame) {
    std::cout << "Sending HDMI frame of size " << frame.size() << std::endl;
}

bool HDMIInput::connect() {
    std::cout << "HDMI input connected." << std::endl;
    return true;
}

std::vector<uint8_t> HDMIInput::receiveFrame() {
    std::vector<uint8_t> dummy(1920 * 1080 * 3, 0);
    std::cout << "Receiving HDMI frame of size " << dummy.size() << std::endl;
    return dummy;
}
