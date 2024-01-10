#include "server.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include "../../ECS/include/SystemManager/Entity.hpp"
#include "../../ECS/include/SystemManager/EntityManager.hpp"
#include "../../ECS/include/SystemManager/HitboxSystem.hpp"
#include "../../ECS/include/components/Health.hpp"
#include "../../ECS/include/components/Position.hpp"
#include "../../ECS/include/components/Damages.hpp"
#include "../../ECS/include/components/HitBox.hpp"
#include <iostream>
#include <chrono>
#include <fstream>

// Server::Server(asio::io_context& io_context, int port)
//     : socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)),
//         tick_timer_(io_context, std::chrono::milliseconds(16)) {
//     start_receive();
//     handle_tick({});
// }

Server::Server(asio::io_context& io_context, int port)
    : socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)),
      tick_timer_(io_context, std::chrono::milliseconds(16)),
      entitySystem(entities_), // Utilisation de entities_ sans std::move
      missileSystem(entities_),
      monsterSystem(entities_, entitySystem),
      playerSystem(entities_)
{
    start_receive();
    handle_tick({});
}

void Server::start_receive() {
    auto buffer = std::make_shared<std::array<char, 1024>>();
    auto endpoint = std::make_shared<asio::ip::udp::endpoint>();

    socket_.async_receive_from(
        asio::buffer(*buffer), *endpoint,
        [this, buffer, endpoint](const asio::error_code& error, std::size_t bytes_recvd) {
            if (!error && bytes_recvd > 0) {
                std::string message(buffer->begin(), buffer->begin() + bytes_recvd);
                handle_receive(message, *endpoint);
                start_receive();
            } else {
                std::cerr << "Receive error: " << error.message() << std::endl;
                start_receive();
            }
        }
    );
}

void Server::handle_receive(const std::string& data, const asio::ip::udp::endpoint& endpoint) {
    std::cout << "Received message: " << data << " from " << endpoint << std::endl;
    // std::cout << "handle_receive called from thread: " << std::this_thread::get_id() << std::endl;

    bool isNewClient = false;
    int clientId;
    {
        std::lock_guard<std::mutex> lock(clients_mutex_);
        if (client_ids_.find(endpoint) == client_ids_.end() || data == "START") {
            number_of_player_connected_++;
            clientId = playerSystem.createPlayer();
            if (clientId == 0) {
                std::string welcomeMessage = "The room is full !";
                handle_send(welcomeMessage, endpoint);
                return;
            }
            client_ids_[endpoint] = clientId;
            isNewClient = true;
            std::cout << "New client added with ID: " << clientId << std::endl;
        } else {
            clientId = client_ids_[endpoint];
        }
    }

    if (isNewClient) {
        std::string welcomeMessage = std::to_string(clientId) + ", Bienvenue !";
        handle_send(welcomeMessage, endpoint);
        return;
    }

    if (data == "QUIT") {
        std::lock_guard<std::mutex> lock(clients_mutex_);
        client_ids_.erase(endpoint);
        handle_send("Goodbye", endpoint);
        number_of_player_connected_--;
        std::cout << "Client " << clientId << " disconnected, clients left: " << number_of_player_connected_ << std::endl;
    } else if (data == "LEFT") {
        playerSystem.handlePlayerInput(clientId, 3);
    } else if (data == "RIGHT") {
        playerSystem.handlePlayerInput(clientId, 4);
    } else if (data == "UP") {
        playerSystem.handlePlayerInput(clientId, 1);
    } else if (data == "DOWN") {
        playerSystem.handlePlayerInput(clientId, 2);
    } else if (data == "SHOOT") {
        playerSystem.handlePlayerInput(clientId, 5);
    } else {
        handle_send("Unknow Command received: " + data, endpoint);   
    }
}

struct Message {
    char data[1024]; // Adaptez la taille selon vos besoins
};

void Server::handle_send(const std::string& message, const asio::ip::udp::endpoint& endpoint)
{
    // Création de l'objet Message
    Message message_obj;
    memset(&message_obj, 0, sizeof(message_obj)); // Initialisation à zéro
    strncpy(message_obj.data, message.c_str(), sizeof(message_obj.data) - 1); // Copie de la chaîne

    auto message_data = std::make_shared<Message>(message_obj);

    socket_.async_send_to(
        asio::buffer(static_cast<const char*>(static_cast<const void*>(message_data.get())), sizeof(Message)), endpoint,
        [this, message_data](const asio::error_code& error, std::size_t /*bytes_sent*/) {
            if (error) {
                std::cerr << "Send error: " << error.message() << std::endl;
            }
        }
    );
}


void Server::handle_tick(const asio::error_code& error)
{
    try {
        if (!error) {
            tick++;
            // manager.updateMissiles();
            // manager.checkEntitiesState();
            // manager.updateMonsters();
            // manager.updateWave();
            missileSystem.launch();
            entitySystem.launch();
            monsterSystem.launch();
            hitbox.launch(entitySystem.getEntsByComps<Ecs::Hitbox, Ecs::Position, Ecs::Damages, Ecs::Health>());

            std::stringstream ss;
            if (entitySystem.interWave) {
                ss << "Wave " << entitySystem.wave << "\n";
            }
            for (auto& entity : entitySystem.getEntsByComp<Ecs::Position>()) {
                ss << "Entity " << entity->getEntityId() << " position: ("
                << entity->getComponent<Ecs::Position>()->getPosition().first << ", "
                << entity->getComponent<Ecs::Position>()->getPosition().second << ")";

                if (entity->hasComponent<Ecs::Health>()) {
                    ss << " HP: " << entity->getComponent<Ecs::Health>()->getHp();
                }
                ss << "\n";
            }

            ss << "Score : " << entitySystem.score << "\n";

            std::string message = ss.str();
            std::lock_guard<std::mutex> lock(clients_mutex_);
            for (auto& client : client_ids_) {
                if (!monsterSystem.isIdTaken(client.second)) {
                    std::string dead_message = "DEAD";
                    handle_send(dead_message, client.first);
                }
                handle_send(message, client.first);
            }

            tick_timer_.expires_at(tick_timer_.expiry() + std::chrono::milliseconds(16));
            tick_timer_.async_wait(std::bind(&Server::handle_tick, this, std::placeholders::_1));
        } else {
            std::cerr << "Tick timer error: " << error.message() << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";

        std::ofstream logFile("log.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << "Exception in thread: " << e.what() << "\n";
            logFile.close();
        } else {
            std::cerr << "Unable to open log file.\n";
        }
    }
}
