/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "../include/Client.hpp"
#include <iostream>
#include <string>

////////////////////////////////////////////////////////////
//
// Create an instance of client class then init / run it
//
// @param argc the number of argument
// @param argv the content of argument
////////////////////////////////////////////////////////////
int main()
{
    Client client = Client("127.0.0.1", 8000);
    std::cout << "Client class initiated" << std::endl;

    client.init();
    client.run();
    return int(client.getStatus());
}
