/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "../include/Client.hpp"

////////////////////////////////////////////////////////////
//
// Create an instance of client class then init / run it
//
// @param argc the number of argument
// @param argv the content of argument
////////////////////////////////////////////////////////////
int main()
{
    // if (argc != 3)
    //     return 84;

    Client client = Client();
    client.init();
    client.run();
    return int(client.getStatus());
}