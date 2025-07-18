#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include "signal_analysis.h"
#include "encoding.h"

using boost::asio::ip::tcp;

class Client {
public:
    Client(boost::asio::io_context& io, const std::string& host, unsigned short port,
           Encoder* encoder, SignalAnalyzer* analyzer)
        : socket_(io), encoder_(encoder), analyzer_(analyzer) {
        tcp::resolver resolver(io);
        auto endpoints = resolver.resolve(host, std::to_string(port));
        boost::asio::async_connect(socket_, endpoints,
            [this](boost::system::error_code ec, tcp::endpoint) {
                if (!ec) {
                    receive();
                }
            });
    }

private:
    void receive() {
        boost::asio::async_read(socket_, boost::asio::buffer(len_buf_),
            [this](boost::system::error_code ec, std::size_t) {
                if (!ec) {
                    uint32_t len = (static_cast<uint32_t>(len_buf_[0]) << 24) |
                                    (static_cast<uint32_t>(len_buf_[1]) << 16) |
                                    (static_cast<uint32_t>(len_buf_[2]) << 8) |
                                    static_cast<uint32_t>(len_buf_[3]);
                    data_buf_.resize(len);
                    read_body(len);
                }
            });
    }

    void read_body(std::size_t len) {
        boost::asio::async_read(socket_, boost::asio::buffer(data_buf_),
            [this](boost::system::error_code ec, std::size_t) {
                if (!ec) {
                    if (analyzer_) analyzer_->analyze(data_buf_);
                    if (encoder_) data_buf_ = encoder_->encode(data_buf_); // decode if symmetric
                    std::string text(data_buf_.begin(), data_buf_.end());
                    std::cout << "Received: " << text << std::endl;
                }
            });
    }

    tcp::socket socket_;
    std::array<uint8_t,4> len_buf_{};
    std::vector<uint8_t> data_buf_;
    Encoder* encoder_;
    SignalAnalyzer* analyzer_;
};

int main() {
    boost::asio::io_context io;
    Encoder* encoder = nullptr;
    SignalAnalyzer* analyzer = nullptr;
    Client cl(io, "127.0.0.1", 12345, encoder, analyzer);
    io.run();
    return 0;
}
