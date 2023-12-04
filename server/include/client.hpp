#pragma once

#include <asio.hpp>
#include <memory>
#include <string>
#include <utility>

class Client
{
    public:
        explicit Client(std::shared_ptr<asio::ip::tcp::socket> socket)
            : socket_(std::move(socket)) {}

        void setLife(int life) { life_ = life; }
        int getLife() const { return life_; }

        void setPosition(float x, float y) { position_ = {x, y}; }
        std::pair<float, float> getPosition() const { return position_; }

        void sendMessage(const std::string& message) {
            asio::async_write(*socket_, asio::buffer(message),
                [](const asio::error_code& error, std::size_t) {
                    if (error) {
                        // Gérer l'erreur d'envoi
                    }
                }
            );
        }

        std::shared_ptr<asio::ip::tcp::socket> getSocket() const {
            return socket_;
        }

    private:
        std::shared_ptr<asio::ip::tcp::socket> socket_;
        int life_;
        std::pair<float, float> position_;
};
