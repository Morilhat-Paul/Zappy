/*
** EPITECH PROJECT, 2024
** server
** File description:
** clear
*/

#include <criterion/criterion.h>
#include "../../../includes/struct_player.h"
#include "../../../includes/command.h"

Test(command, clear_commands) {
    player_t player = { .id = 0, .level = 0 };
    const command_t cmd1 = { "cmd1", NULL, NULL };
    const command_t cmd2 = { "cmd2", NULL, NULL };

    enqueue_command(&player, &cmd1);
    enqueue_command(&player, &cmd2);
    cr_assert_eq(player.commands[0], &cmd1);
    cr_assert_eq(player.commands[1], &cmd2);

    clear_commands(&player);
    cr_assert_eq(player.commands[0], NULL);
    cr_assert_eq(player.commands[1], NULL);
}
