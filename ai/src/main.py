#!/usr/bin/python3

import argparse
from ai.src.bot.Bot import Bot
from ai.src.client.Client import Client

def parse_args():
    parser = argparse.ArgumentParser(
        prog="zappy_ai", description='Connect ai to zappy server.',
        usage='./%(prog)s [-p port] [-n name] [-h host] [port] [name] [host]',
        conflict_handler='resolve')

    parser.add_argument('-H', '--help', action='help', default=argparse.SUPPRESS, help='show this help message and exit')
    parser.add_argument('-p', '--port', type=int, help='port number (optional)', metavar='port')
    parser.add_argument('-n', '--name', type=str, help='name of the team (optional)', metavar='name')
    parser.add_argument('-h', '--host', type=str, help='name of the machine (optional)', default='localhost', metavar='host')

    parser.add_argument('pos_port', type=int, nargs='?', help=argparse.SUPPRESS, metavar='port')
    parser.add_argument('pos_name', type=str, nargs='?', help=argparse.SUPPRESS, metavar='name')
    parser.add_argument('pos_host', type=str, nargs='?', help=argparse.SUPPRESS, metavar='host', default='localhost')

    args = parser.parse_args()

    port = args.port if args.port is not None else args.pos_port
    name = args.name if args.name is not None else args.pos_name
    host = args.host if args.host != 'localhost' else args.pos_host

    if port is None or name is None or host is None:
        parser.print_usage()
        parser.exit(84, "zappy_ai: error: missing required arguments\n")

    if name == 'GRAPHIC':
        parser.exit(84, "The team name GRAPHIC is reserved for the GUI\n")

    return port, name, host

if __name__ == '__main__':
    port, team, host = parse_args()

    bot = Bot(team)
    client = Client(bot, host, port)
    client.start()
