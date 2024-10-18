/*
** EPITECH PROJECT, 2024
** server
** File description:
** dequeue
*/

#include <criterion/criterion.h>
#include "../../../includes/struct_player.h"
#include "../../../includes/command.h"

Test(command, dequeue_commands) {
    player_t player = { .id = 0, .level = 0 };
    const command_t cmd1 = { "cmd1", NULL, NULL };
    const command_t cmd2 = { "cmd2", NULL, NULL };

    enqueue_command(&player, &cmd1);
    enqueue_command(&player, &cmd2);
    cr_assert_eq(player.commands[0], &cmd1);
    cr_assert_eq(player.commands[1], &cmd2);

    dequeue_command(&player, &cmd1);
    cr_assert_eq(player.commands[0], &cmd2);
    cr_assert_eq(player.commands[1], NULL);

    dequeue_command(&player, &cmd2);
    cr_assert_eq(player.commands[0], NULL);
    cr_assert_eq(player.commands[1], NULL);
}

Test(command, dequeue_max_commands) {
    player_t player = { .id = 0, .level = 0 };
    const command_t cmd = { "cmd", NULL, NULL };
    const command_t cmd_max = { "cmd_max", NULL, NULL };

    for (int i = 0; i < MAX_COMMAND - 1; i++)
        enqueue_command(&player, &cmd);
    enqueue_command(&player, &cmd_max);

    cr_assert_eq(player.commands[MAX_COMMAND - 2], &cmd);
    cr_assert_eq(player.commands[MAX_COMMAND - 1], &cmd_max);
    cr_assert_null(player.commands[MAX_COMMAND]);

    dequeue_command(&player, &cmd_max);

    cr_assert_eq(player.commands[MAX_COMMAND - 2], &cmd);
    cr_assert_null(player.commands[MAX_COMMAND - 1]);
    cr_assert_null(player.commands[MAX_COMMAND]);
}

Test(command, dequeue_command_not_in_queue) {
    player_t player = { .id = 0, .level = 0 };
    const command_t cmd = { "cmd", NULL, NULL };
    const command_t cmd_max = { "cmd_max", NULL, NULL };

    for (int i = 0; i < MAX_COMMAND; i++)
        enqueue_command(&player, &cmd);

    cr_assert_eq(player.commands[MAX_COMMAND - 1], &cmd);
    cr_assert_null(player.commands[MAX_COMMAND]);

    dequeue_command(&player, &cmd_max);

    cr_assert_eq(player.commands[MAX_COMMAND - 1], &cmd);
    cr_assert_null(player.commands[MAX_COMMAND]);
}
