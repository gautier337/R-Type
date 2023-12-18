/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "../include/Client.hpp"

////////////////////////////////////////////////////////////
//
// Gets the file and store it in the m_content vector
//
// @param argc the number of argument
// @param argv the content of argument
////////////////////////////////////////////////////////////
int main()
{
    // if (argc != 3)
    //     return 84;

    Client client = Client();
    client.run();
    return int(client.getStatus());
}