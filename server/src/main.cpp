#include <iostream>
#include <memory>
#include <asio.hpp>

const int serverPort = 8000;

void start_read(std::shared_ptr<asio::ip::tcp::socket> socket) {
    auto buffer = std::make_shared<std::vector<char>>(1024);
    socket->async_read_some(asio::buffer(*buffer), [socket, buffer](const asio::error_code& error, std::size_t length) {
        if (!error) {
            std::string message(buffer->begin(), buffer->begin() + length);
            std::cout << "Received: " << message << std::endl;

            // Continue reading from the client
            start_read(socket);
        } else {
            // Handle disconnection or errors
        }
    });
}

void start_accept(asio::ip::tcp::acceptor& acceptor, asio::io_context& io_context) {
    auto socket = std::make_shared<asio::ip::tcp::socket>(io_context);
    acceptor.async_accept(*socket, [&acceptor, &io_context, socket](const asio::error_code& error) {
        if (!error) {
            std::cout << "New client connected" << std::endl;

            // Commencer la lecture des données du client
            start_read(socket);

            // Continuer à accepter de nouvelles connexions
            start_accept(acceptor, io_context);
        } else {
            // Gérer l'erreur
        }
    });
}

int main() {
    try {
        std::cout << "R-Type Server Starting..." << std::endl;

        asio::io_context io_context;
        asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), serverPort);
        asio::ip::tcp::acceptor acceptor(io_context, endpoint);

        start_accept(acceptor, io_context);

        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
