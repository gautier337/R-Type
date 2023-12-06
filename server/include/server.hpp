#pragma once

#include <asio.hpp>
#include <vector>
#include <memory>
#include <mutex>

class Server {
    public:
        Server(asio::io_context& io_context, int port);

    private:
        void start_receive();
        void handle_tick(const asio::error_code& error);
        void handle_send(const std::string& /*message*/, const std::shared_ptr<std::string> /*message_data*/);
        void handle_receive(const std::string& data, const asio::ip::udp::endpoint& endpoint);

        std::vector<asio::ip::udp::endpoint> clients_;
        asio::ip::udp::socket socket_;

        asio::steady_timer tick_timer_;
        int tick = 0;
};
