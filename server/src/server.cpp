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
#include <chrono>
#include <fstream>

Server::Server(asio::io_context& io_context, int port, int wave, bool solo)
    : socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)),
      tick_timer_(io_context, std::chrono::milliseconds(16)),
      entitySystem(entities_),
      missileSystem(entities_),
      monsterSystem(entities_, entitySystem, solo),
      playerSystem(entities_)
{
    entitySystem.wave = wave;
    if (entitySystem.wave == 2)
        entitySystem.killedMonstersCount = 10;
    if (entitySystem.wave == 3)
        entitySystem.killedMonstersCount = 30;
    if (entitySystem.wave == 4)
        entitySystem.killedMonstersCount = 31;
    if (entitySystem.wave == 5)
        entitySystem.killedMonstersCount = 45;
    if (entitySystem.wave == 6)
        entitySystem.killedMonstersCount = 75;
    if (entitySystem.wave == 7)
        entitySystem.killedMonstersCount = 76;
    if (entitySystem.wave == 8)
        entitySystem.killedMonstersCount = 100;
    if (entitySystem.wave == 9)
        entitySystem.killedMonstersCount = 130;
    if (entitySystem.wave == 10)
        entitySystem.killedMonstersCount = 138;
    start_receive();
    solo_ = solo;
    std::cout << "Server started on port " << port << std::endl;
    std::cout << "Wave: " << wave << std::endl;
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

void Server::handle_receive(const std::string& data, const asio::ip::udp::endpoint& endpoint)
{
    std::cout << "Received message: " << data << " from " << endpoint << std::endl;
    // std::cout << "handle_receive called from thread: " << std::this_thread::get_id() << std::endl;
    // std::cout << "Trying to lock clients_mutex_ from thread: " << std::this_thread::get_id() << std::endl;
    auto it = client_ids_.find(endpoint);
    {
        std::lock_guard<std::mutex> lock(clients_mutex_);
        // std::cout << "clients_mutex_ locked by thread: " << std::this_thread::get_id() << std::endl;
        // Vérifier si le client existe et traiter les nouveaux clients
        if (it == client_ids_.end()) {
            // le client n'a jamais été enrégistré, il n'existe pas dans la liste client_ids_
            if (data == "START") {
                if (accepting_connections_ == false) {
                    handle_send("The game has already started and it's in solo mode", endpoint);
                    return;
                }
                int clientId = playerSystem.createPlayer();
                if (clientId == 0) {
                    handle_send("The room is full!", endpoint);
                    std::cout << "clients_mutex_ unlocked by thread: " << std::this_thread::get_id() << std::endl;
                    return;
                }
                client_ids_[endpoint] = clientId;
                std::string welcomeMessage = std::to_string(clientId) + ", Bienvenue !";
                handle_send(welcomeMessage, endpoint);
                number_of_player_connected_++;
                std::cout << "New client added with ID: " << clientId << std::endl;
                if (solo_) {
                    accepting_connections_ = false;
                }
            } else {
                handle_send("You are not in our list, please say START", endpoint);
                std::cout << "A client tried to send a message but he is not in our list and he didn't say START" << std::endl;
            }
            // std::cout << "clients_mutex_ unlocked by thread: " << std::this_thread::get_id() << std::endl;
            return;
        }
        if (data == "QUIT") {
            client_ids_.erase(endpoint);
            handle_send("Goodbye", endpoint);
            number_of_player_connected_--;
            std::cout << "Client " << it->second << " disconnected, clients left: " << number_of_player_connected_ << std::endl;
            // std::cout << "clients_mutex_ unlocked by thread: " << std::this_thread::get_id() << std::endl;
            return;
        }
    }

    // std::cout << "clients_mutex_ unlocked by thread: " << std::this_thread::get_id() << std::endl;
    int clientId = it->second;

    if (data == "LEFT") {
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
        handle_send("Unknown Command received: " + data, endpoint);
    }
}

struct Message {
    char data[1024];
};

void Server::handle_send(const std::string& message, const asio::ip::udp::endpoint& endpoint)
{
    // Création de l'objet Message
    Message message_obj;
    memset(&message_obj, 0, sizeof(message_obj));
    strncpy(message_obj.data, message.c_str(), sizeof(message_obj.data) - 1);

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
            missileSystem.launch();
            entitySystem.launch();
            playerSystem.launch();
            monsterSystem.launch();
            hitbox.launch(entitySystem.getEntsByComps<Ecs::Hitbox, Ecs::Position, Ecs::Damages, Ecs::Health>());

            std::stringstream ss;
            ss << "Wave " << entitySystem.wave << "\n";
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
