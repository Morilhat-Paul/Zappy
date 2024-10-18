/*
** EPITECH PROJECT, 2024
** server
** File description:
** enqueue
*/

#include <criterion/criterion.h>
#include "../../../includes/struct_player.h"
#include "../../../includes/command.h"

Test(command, enqueue_commands) {
    player_t player = { .id = 0, .level = 0 };
    const command_t cmd1 = { "cmd1", NULL, NULL };
    const command_t cmd2 = { "cmd2", NULL, NULL };

    enqueue_command(&player, &cmd1);
    enqueue_command(&player, &cmd2);

    cr_assert_eq(player.commands[0], &cmd1);
    cr_assert_eq(player.commands[1], &cmd2);
}

Test(command, enqueue_max_commands) {
    player_t player = { .id = 0, .level = 0 };
    const command_t cmd = { "cmd", NULL, NULL };
    const command_t cmd_max = { "cmd_max", NULL, NULL };

    for (int i = 0; i < MAX_COMMAND - 1; i++)
        enqueue_command(&player, &cmd);
    enqueue_command(&player, &cmd_max);

    cr_assert_eq(player.commands[MAX_COMMAND - 2], &cmd);
    cr_assert_eq(player.commands[MAX_COMMAND - 1], &cmd_max);
    cr_assert_null(player.commands[MAX_COMMAND]);
}

Test(command, enqueue_full_commands) {
    player_t player = { .id = 0, .level = 0 };
    const command_t cmd = { "cmd", NULL, NULL };
    const command_t cmd_max = { "cmd_max", NULL, NULL };

    for (int i = 0; i < MAX_COMMAND; i++)
        enqueue_command(&player, &cmd);

    cr_assert_eq(player.commands[MAX_COMMAND - 1], &cmd);
    cr_assert_null(player.commands[MAX_COMMAND]);

    enqueue_command(&player, &cmd_max);

    cr_assert_eq(player.commands[MAX_COMMAND - 1], &cmd);
    cr_assert_null(player.commands[MAX_COMMAND]);
}
