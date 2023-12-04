#pragma once

#include <asio.hpp>
#include <vector>
#include <memory>
#include <mutex>
#include "client.hpp"

class Server {
    public:
        Server(asio::io_context& io_context, int port);

        void broadcast_message(const std::string& message);

    private:
        void start_accept();
        void start_read(std::shared_ptr<Client> client);
        void handle_tick(const asio::error_code& error);

        std::vector<std::shared_ptr<Client>> clients_;
        std::mutex clients_mutex_;
        asio::ip::tcp::acceptor acceptor_;
        asio::steady_timer tick_timer_;
        int tick = 0;
};
