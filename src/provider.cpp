#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include "signal_analysis.h"
#include "encoding.h"

using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_context& io, unsigned short port, Encoder* encoder, SignalAnalyzer* analyzer)
        : acceptor_(io, tcp::endpoint(tcp::v4(), port)), encoder_(encoder), analyzer_(analyzer) {
        accept();
    }

private:
    void accept() {
        socket_.emplace(acceptor_.get_executor());
        acceptor_.async_accept(*socket_, [this](boost::system::error_code ec) {
            if (!ec) {
                std::cout << "Client connected" << std::endl;
                send_data();
            }
        });
    }

    void send_data() {
        std::vector<uint8_t> raw{ 'H', 'e', 'l', 'l', 'o' };
        if (encoder_) raw = encoder_->encode(raw);
        if (analyzer_) analyzer_->analyze(raw);
        uint32_t len = static_cast<uint32_t>(raw.size());
        std::vector<uint8_t> buffer(4 + raw.size());
        buffer[0] = (len >> 24) & 0xFF;
        buffer[1] = (len >> 16) & 0xFF;
        buffer[2] = (len >> 8) & 0xFF;
        buffer[3] = len & 0xFF;
        std::copy(raw.begin(), raw.end(), buffer.begin() + 4);
        boost::asio::async_write(*socket_, boost::asio::buffer(buffer),
            [this](boost::system::error_code ec, std::size_t) {
                if (!ec) {
                    std::cout << "Data sent" << std::endl;
                }
            });
    }

    tcp::acceptor acceptor_;
    std::optional<tcp::socket> socket_;
    Encoder* encoder_;
    SignalAnalyzer* analyzer_;
};

int main() {
    boost::asio::io_context io;
    Encoder* encoder = nullptr; // hook for custom encoding
    SignalAnalyzer* analyzer = nullptr; // hook for signal analysis
    Server srv(io, 12345, encoder, analyzer);
    io.run();
    return 0;
}
