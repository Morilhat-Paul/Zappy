#!/usr/bin/python3

class Action:
    def look(bot, msg):
        bot.around = []
        squares = msg[1:-1].split(',')
        for sq in squares:
            bot.around.append(sq.strip().split(' '))

    def inventory(bot, msg):
        bot.inventory = {}
        items = msg[1:-1].split(',')
        for it in items:
            sp = it.strip().split(' ')
            if len(sp) == 2 and sp[1].isdigit():
                bot.inventory[sp[0]] = int(sp[1])
            else:
                print(f"Unexpected inventory format: {it}")

    def take(bot, msg):
        bot.inventory = {}
        bot.around = []

    def incantation(bot, msg):
        if msg == 'ko':
            bot.elevation_failed = True
        bot.reset_state()
