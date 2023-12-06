How to build and run the server:

Dependences:
sudo apt install cmake
sudo apt install libasio-dev

go to /build and run:

cmake .. && make && ./RTypeServer

pour envoyer un message au serveur avec netcat par exemple:

echo "1 Z" | nc -u -q 0 127.0.0.1 8000
