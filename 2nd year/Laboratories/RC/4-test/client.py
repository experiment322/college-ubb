import sys
import time
import socket

#python client.py [SERVER_ADDR] [SERVER_PORT] [HOST_PORT]
if len(sys.argv) != 4:
    exit("Numar invalid de argumente.")

HOST = sys.argv[1]
PORT = int(sys.argv[2])
SOURCE = sys.argv[3]
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((SOURCE, 0))
    s.connect((HOST, PORT))
    number = input("Numar: ")
    text = input("Text: ")
    s.sendall(number.encode())
    time.sleep(1)
    s.sendall(text.encode())
    last_char = s.recv(1)
    time.sleep(1)
    last_addr = s.recv(16)
print('Raspuns:', last_char.decode(), last_addr.decode())
