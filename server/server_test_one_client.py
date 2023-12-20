import socket
import time
import random

def send_message_to_server(sock, server_address, server_port, message):
    sock.sendto(message.encode(), (server_address, server_port))
    data, server = sock.recvfrom(4096)
    return data.decode()

def parse_client_id(response):
    try:
        parts = response.split(',')
        client_id = int(parts[0].strip())
        return client_id
    except Exception as e:
        print(f"Erreur lors du parsing de l'ID: {e}, response={response}")
        exit(1)

def client_routine(server_address, server_port, client_id):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        response = send_message_to_server(sock, server_address, server_port, 'START')
        print(f"Client {client_id}: Reçu '{response}' du serveur")
        server_client_id = parse_client_id(response)
        if server_client_id is None:
            return

        print(f"Client {client_id}: Reçu ID '{server_client_id}' du serveur")
        
        # Envoi de la commande 'QUIT' au serveur
        # send_message_to_server(sock, server_address, server_port, 'QUIT')
        # print(f"Client {client_id}: Envoi de la commande 'QUIT'")
        while True:
            data, server = sock.recvfrom(4096)
            print(f"Client {client_id}: Reçu '{data.decode()}' du serveur")


if __name__ == "__main__":
    server_address = '127.0.0.1'
    server_port = 8000
    client_id = 1  # ID du client

    print(f"Client {client_id}: Connexion au serveur")
    client_routine(server_address, server_port, client_id)

    print("Test terminé.")
