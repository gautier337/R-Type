import socket
import time
import random

client_ids = set()

def send_message_to_server(sock, server_address, server_port, message):
    sock.sendto(message.encode(), (server_address, server_port))
    data, server = sock.recvfrom(4096)
    return data.decode()

def parse_client_id(response):
    try:
        # Divise la chaîne de caractères au niveau de la virgule
        parts = response.split(',')
        # Récupère la première partie et la convertit en entier
        client_id = int(parts[0].strip())  # 'strip' est utilisé pour enlever les espaces blancs
        return client_id
    except Exception as e:
        print(f"Erreur lors du parsing de l'ID: {e}, response={response}")
        exit(1)

def client_routine(server_address, server_port, client_id, is_reconnect=False):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        response = send_message_to_server(sock, server_address, server_port, 'START')
        print(f"Client {client_id}: Reçu '{response}' du serveur")
        server_client_id = parse_client_id(response)
        if server_client_id is None:
            return

        assert server_client_id not in client_ids, f"ID {server_client_id} is duplicated"
        client_ids.add(server_client_id)

        print(f"Client {client_id} ({'Reconnect' if is_reconnect else 'Connect'}): Reçu ID '{server_client_id}' du serveur")
        
        # time.sleep(5)
        # send_message_to_server(sock, server_address, server_port, 'QUIT')
        if random.randint(1, 10) == 1:
            print(f"Client {client_id}: Envoi de la commande 'QUIT'")
            send_message_to_server(sock, server_address, server_port, 'QUIT')

if __name__ == "__main__":
    server_address = '127.0.0.1'
    server_port = 8000

    num_clients = 20000

    # Première phase: Connexion des clients
    for i in range(num_clients):
        print(f"Client {i}: Connexion au serveur")
        client_routine(server_address, server_port, i)

    # Vider l'ensemble des IDs pour la seconde phase
    client_ids.clear()

    # Seconde phase: Reconnexion des clients
    for i in range(num_clients, num_clients * 2):
        client_routine(server_address, server_port, i, True)

    print("Test terminé. Aucun ID dupliqué détecté.")
