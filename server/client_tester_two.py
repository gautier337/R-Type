import socket
import time

def send_message_to_server(sock, server_address, server_port, message):
    # Envoi du message
    sock.sendto(message.encode(), (server_address, server_port))

    # Attente de la réponse
    data, server = sock.recvfrom(4096)
    print(f"Réponse reçue : '{data.decode()}'")

def send_test_commands(server_address, server_port):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        test_commands = ['START', 'test1', 'test2']  # Remplacez par vos commandes de test

        for command in test_commands:
            print(f"Envoi de la commande '{command}'")
            send_message_to_server(sock, server_address, server_port, command)
            time.sleep(1)  # Attendre 1 seconde entre chaque commande

        # Attente de 10 secondes avant d'envoyer QUIT
        time.sleep(5)
        print("Envoi de la commande 'QUIT'")
        send_message_to_server(sock, server_address, server_port, 'QUIT')

if __name__ == "__main__":
    # Adresse et port du serveur
    server_address = '127.0.0.1'  # L'adresse IP de votre serveur
    server_port = 8000  # Le port sur lequel votre serveur écoute

    send_test_commands(server_address, server_port)
