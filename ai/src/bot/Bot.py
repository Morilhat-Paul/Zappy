#!/usr/bin/python3

import random

class Bot:
    def __init__(self, team):
        self.team = team
        self.level = 1
        self.inventory = {}
        self.around = []
        self.path = []
        self.elevation = []
        self.elevation_failed = False
        self.connect_watcher = 0
        self.locked = False
        self.dead = False

    def needed_res(self):
        resources = {
            1: {'nb_players': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
            2: {'nb_players': 2, 'linemate': 1, 'deraumere': 1, 'sibur': 1, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
            3: {'nb_players': 2, 'linemate': 2, 'deraumere': 0, 'sibur': 1, 'mendiane': 0, 'phiras': 2, 'thystame': 0},
            4: {'nb_players': 4, 'linemate': 1, 'deraumere': 1, 'sibur': 2, 'mendiane': 0, 'phiras': 1, 'thystame': 0},
            5: {'nb_players': 4, 'linemate': 1, 'deraumere': 2, 'sibur': 1, 'mendiane': 3, 'phiras': 0, 'thystame': 0},
            6: {'nb_players': 6, 'linemate': 1, 'deraumere': 2, 'sibur': 3, 'mendiane': 0, 'phiras': 1, 'thystame': 0},
            7: {'nb_players': 6, 'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 2, 'phiras': 2, 'thystame': 1},
        }
        return resources.get(self.level, {})

    def seek_place(self):
        needed = self.needed_res()
        for i, sq in enumerate(self.around):
            for element in sq:
                if element == 'food':
                    self.to_take = 'food'
                    return i
                if self.level != 8 and self.inventory.get(element, 0) < needed.get(element, 0):
                    self.to_take = element
                    return i
        return -1

    def get_players_around(self):
        return sum(1 for element in self.around[0] if element == 'player')

    def can_elevate(self):
        needed = self.needed_res()
        for key, val in needed.items():
            if key != 'nb_players' and self.inventory.get(key, 0) < val:
                return -1
        if self.get_players_around() < needed['nb_players']:
            return 0
        return 1

    def prepare_elevation(self):
        self.elevation = []
        needed = self.needed_res()
        for key, val in needed.items():
            if key != 'nb_players' and val > 0:
                self.elevation.extend([f"Set {key}"] * val)
        self.elevation.append('Incantation')

    def get_vision(self):
        vision = []
        first, last = 1, 3
        for _ in range(self.level):
            line = list(range(first, last + 1))
            vision.append(line)
            first, last = last + 1, first + len(line) + 1
        return vision

    def init_path(self, index):
        self.path = ['Forward']
        cur_index = 2
        cur_line = 0
        turned = False
        vision = self.get_vision()
        while cur_index != index:
            if index not in vision[cur_line]:
                self.path.append('Forward')
                cur_line += 1
                if cur_line >= len(vision):
                    break
                cur_index = vision[cur_line][len(vision[cur_line]) // 2]
            else:
                if index < cur_index:
                    if not turned:
                        self.path.append('Left')
                    cur_index -= 1
                else:
                    if not turned:
                        self.path.append('Right')
                    cur_index += 1
                turned = True
                self.path.append('Forward')

    def next_move(self):
        if len(self.path) == 1:
            self.around = []
        return self.path.pop(0)

    def next_action(self):
        if len(self.elevation) == 1:
            self.inventory = {}
        return self.elevation.pop(0)

    def will_try_to_fork(self):
        return random.randint(0, 6) == 1

    def recv_message(self, k, text):
        if self.locked:
            return
        if self.path and k != 0:
            return
        required_level = int(text)
        if required_level != self.level:
            return
        moves = [
            [],
            ['Forward'],
            ['Forward', 'Left', 'Forward'],
            ['Left', 'Forward'],
            ['Left', 'Forward', 'Left', 'Forward'],
            ['Left', 'Left', 'Forward'],
            ['Right', 'Forward', 'Right', 'Forward'],
            ['Right', 'Forward'],
            ['Forward', 'Right', 'Forward'],
        ]
        self.path = moves[k]
        if k == 0:
            self.locked = True

    def get_random_move(self):
        moves = ['Left', 'Right', 'Forward', 'Forward', 'Forward']
        return random.choice(moves)

    def elevation_did_fail(self):
        self.elevation_failed = False
        self.elevation = ['Incantation']
        return f"Broadcast {self.level}"

    def reset_state(self):
        self.around = []
        self.inventory = {}
        self.locked = False

    def live(self):
        if not self.inventory:
            return 'Inventory'
        if self.inventory.get('food', 0) < 5:
            self.locked = False
        if self.connect_watcher % 10 == 0 or self.locked:
            self.connect_watcher += 1
            self.inventory = {}
            return 'Connect_nbr'
        if self.path:
            return self.next_move()
        if self.elevation:
            return self.next_action()
        if not self.around:
            return 'Look'
        if self.level != 8 and self.inventory.get('food', 0) >= 5:
            if self.elevation_failed:
                return self.elevation_did_fail()
            if self.can_elevate() == 0:
                self.around = []
                self.inventory = {}
                if self.will_try_to_fork():
                    return 'Fork'
                return f"Broadcast {self.level}"
            if self.can_elevate() == 1:
                self.prepare_elevation()
                return self.next_action()
        index = self.seek_place()
        if index != -1:
            if index == 0:
                return f"Take {self.to_take}"
            self.init_path(index)
            return self.next_move()
        self.around = []
        return self.get_random_move()
