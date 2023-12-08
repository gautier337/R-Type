/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** SendingEntityServer
*/

#ifndef SENDINGENTITYSERVER_HPP_
	#define SENDINGENTITYSERVER_HPP_
	#include "ASystem.hpp"
	#include "Network/UDPServer.hpp"

namespace Ecs {

	class SendingEntityServer : public ASystem {
		public:
			FrameSendingSystem(
				std::list<std::shared_ptr<Entity>> &entities,
				UDPServer &server,
				boost::asio::ip::udp::endpoint	_endpoint);
			void launch() final;

		private:
			void drawThisEntity(std::shared_ptr<Entity> entity);
			boost::asio::ip::udp::endpoint	_endpoint;
			UDPServer &_server;
	};

}

#endif /* !SENDINGENTITYSERVER_HPP_ */
