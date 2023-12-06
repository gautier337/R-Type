import socket
import time
import threading

def send_message_to_server(sock, server_address, server_port, message):
    # Envoi du message
    sock.sendto(message.encode(), (server_address, server_port))

    # Attente de la réponse
    data, server = sock.recvfrom(4096)
    print(f"Réponse reçue : '{data.decode()}'")

def client_routine(server_address, server_port, client_id):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        test_commands = [f'{client_id}-START', f'{client_id}-test1', f'{client_id}-test2']

        for command in test_commands:
            print(f"Client {client_id}: Envoi de la commande '{command}'")
            send_message_to_server(sock, server_address, server_port, command)
            time.sleep(1)

        time.sleep(5)
        print(f"Client {client_id}: Envoi de la commande 'QUIT'")
        send_message_to_server(sock, server_address, server_port, 'QUIT')

if __name__ == "__main__":
    server_address = '127.0.0.1'
    server_port = 40000

    num_clients = 500 # Nombre de clients à simuler

    threads = []
    for i in range(num_clients):
        thread = threading.Thread(target=client_routine, args=(server_address, server_port, i))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()
