import os
import socket

HOST = ''
PORT = 7333

def new_game_board():
    return b'---------'

def print_game_board(game_board):
    for i in range(0,9,3):
        print(game_board[i:i+3].decode())

def put_on_board(game_board, pos, c):
    if pos > 0 and pos < len(game_board):
        return game_board[:pos] + c + game_board[pos + 1:]
    return game_board

def handle_connection(conn, addr):
    with conn:
        game_board = new_game_board()
        while True:
            print(addr)
            print_game_board(game_board)
            x_pos = int(input('pos = '))
            game_board = put_on_board(game_board, x_pos, b'x')
            print_game_board(game_board)
            conn.sendall(game_board)
            o_pos = int(conn.recv(1024).decode())
            game_board = put_on_board(game_board, o_pos, b'o')
            conn.sendall(game_board)
            print()


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen(1)
    while True:
        conn, addr = s.accept()
        if os.fork() == 0:
            handle_connection(conn, addr)
