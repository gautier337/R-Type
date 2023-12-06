#pragma once

#include <asio.hpp>
#include <vector>
#include <memory>
#include <mutex>
#include <functional>
#include <asio.hpp>

namespace std
{
    template<>
    struct hash<asio::ip::udp::endpoint> {
        size_t operator()(const asio::ip::udp::endpoint& endpoint) const {
            return hash<string>()(endpoint.address().to_string()) ^ hash<unsigned short>()(endpoint.port());
        }
    };
}

class Server {
    public:
        Server(asio::io_context& io_context, int port);

    private:
        void start_receive();
        void handle_tick(const asio::error_code& error);
        void handle_send(const std::string& message, const asio::ip::udp::endpoint& endpoint);
        void handle_receive(const std::string& data, const asio::ip::udp::endpoint& endpoint);

        std::unordered_map<asio::ip::udp::endpoint, int> client_ids_;
        std::mutex clients_mutex_;
        asio::ip::udp::socket socket_;

        asio::steady_timer tick_timer_;
        int number_of_player_connected_ = 0;
        int tick = 0;
        int client_id_counter_ = 0;
};
