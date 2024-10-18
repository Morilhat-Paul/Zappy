#!/usr/bin/python3

import os
import subprocess
import sys
import socket
import threading

from ai.src.action.Action import Action

fork_triggered = False

class Client:
    def __init__(self, bot, host, port):
        self.last_cmd = None
        self.bot = bot
        self.host = host
        self.port = port
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def start(self):
        try:
            self.client_socket.connect((self.host, self.port))
            listener_thread = threading.Thread(target=self.client_listener, args=(self.client_socket,))
            listener_thread.start()
            listener_thread.join()
        except socket.error as e:
            print(f"Socket error: {e}")
        finally:
            self.client_socket.close()

    def send_cmd(self, client, cmd):
        self.last_cmd = cmd
        self.send(client, cmd)
        print(f"{cmd}")

    def send(self, client, msg):
        client.sendall((msg + '\n').encode())

    def handle_response(self, client, msg):
        print(f"({os.getpid()}) {self.last_cmd}: {msg}")
        if "Elevation underway" in msg:
            self.bot.reset_state()
            if self.last_cmd and self.last_cmd == 'Incantation':
                self.last_cmd = None
        elif "Current level:" in msg:
            i = msg.index(':') + 1
            s = msg[i:]
            self.bot.level = int(s)
            self.bot.reset_state()
            if self.last_cmd and self.last_cmd == 'Incantation':
                self.last_cmd = None
        elif "Eject" in msg:
            self.bot.reset_state()
        else:
            cmd_name = self.last_cmd.split(' ')[0]
            if cmd_name == "Look":
                Action.look(self.bot, msg)
            elif cmd_name == "Inventory":
                Action.inventory(self.bot, msg)
            elif cmd_name == "Take":
                Action.take(self.bot, msg)
            elif cmd_name == "Incantation":
                Action.incantation(self.bot, msg)
            elif cmd_name == "Connect_nbr":
                self.connect_nbr(msg)
            self.last_cmd = None

    def process_msg(self, client, msg):
        global handshake
        if msg == "WELCOME":
            self.welcome(client)
        elif msg == "dead":
            self.die()
        else:
            try:
                if handshake == 1:
                    if self.connect_nbr(msg):
                        handshake = 2
                elif handshake == 2:
                    if self.world_size(msg):
                        handshake = 3
                        if not self.bot.dead:
                            self.send_cmd(client, self.bot.live())
                elif handshake >= 3:
                    if msg.startswith("message"):
                        self.handle_message(msg)
                    else:
                        self.handle_response(client, msg)
                        if not self.last_cmd and not self.bot.dead:
                            self.send_cmd(client, self.bot.live())
            except ValueError as e:
                self.print_help_message()

    def welcome(self, client):
        global handshake
        handshake = 1
        self.send(client, self.bot.team)

    def die(self):
        print('dead')
        self.bot.dead = True

    def connect_nbr(self, msg):
        global fork_triggered
        n = int(msg)
        if not fork_triggered and n == 0:
            fork_triggered = True
            self.fork_player()
        elif fork_triggered and n > 0:
            self.fork_player()
        return True

    def world_size(self, msg):
        params = msg.split(' ')
        if len(params) != 2:
            return False
        self.bot.world_x, self.bot.world_y = int(params[0]), int(params[1])
        return True

    def fork_player(self):
        args = ['./zappy_ai', '-n', self.bot.team, '-p', str(self.port)]
        if self.host != 'localhost':
            args.extend(['-h', self.host])
        subprocess.Popen(args)

    def handle_message(self, msg):
        print(msg)
        i = msg.index(' ') + 1
        s = msg[i:]
        args = s.split(',')
        if not args or len(args) != 2:
            return
        self.bot.recv_message(int(args[0]), args[1])

    def client_listener(self, client):
        while True:
            data = client.recv(4096)
            if not data:
                break
            messages = data.decode().split('\n')
            for msg in messages:
                if msg:
                    self.process_msg(client, msg)

    def print_help_message(self):
        print("usage: ./zappy_ai [-p port] [-n name] [-h host] [port] [name] [host]\n")
        print("Connect ai to zappy server.\n")
        exit(84)
