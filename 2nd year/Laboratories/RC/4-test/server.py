import sys
import time
import socket
#-----se importa modulul pentru threaduri
#import threading

#python server.py [PORT]
if len(sys.argv) != 2:
    exit("Numar invalid de argumente.")

HOST = ''
PORT = int(sys.argv[1])
last_addr = ''
last_char = ''

#-----se copiaza codul din serverul iterativ intr-o functie
#-----si se foloseste un lock pentru a modifica variabilele globale
#lock = threading.Lock()
#def conn_handler(conn, addr):
#    global last_addr
#    global last_char
#    with conn:
#        print('Client conectat:', addr[0])
#        number = int(conn.recv(16).decode())
#        time.sleep(1)
#        text = conn.recv(256).decode()
#        time.sleep(1)
#        conn.sendall(last_char.encode())
#        conn.sendall(last_addr.encode())
#        with lock:
#            last_addr = addr[0]
#            last_char = text[number]

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen(1)
    while True:
        conn, addr = s.accept()
#-----se creeaza threadul si se apeleaza functia de mai sus
#        t = threading.Thread(target=conn_handler, args=(conn, addr))
#        t.start()
#-----se vor comenta liniile urmatoare
        with conn:
            print('Client conectat:', addr[0])
            number = int(conn.recv(16).decode())
            time.sleep(1)
            text = conn.recv(256).decode()
            time.sleep(1)
            conn.sendall(last_char.encode())
            conn.sendall(last_addr.encode())
            last_addr = addr[0]
            last_char = text[number]

