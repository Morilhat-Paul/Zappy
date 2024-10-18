/*
** EPITECH PROJECT, 2024
** server
** File description:
** execute
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../../../includes/struct_player.h"
#include "../../../includes/command.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

void test_function(player_t *__attribute_maybe_unused__, const char **args)
{
    for (int i = 0; args[i]; i++)
        printf("%s\n", args[i]);
}

Test(command, execute_commands, .init = redirect_all_stdout) {
    player_t player = { .id = 0, .level = 0 };
    const char *args1[] = { "arg1", "arg2", "arg3", NULL };
    const char *args2[] = { "ARG1", "ARG2", "ARG3", NULL };
    const command_t cmd1 = { "cmd1", &args1[0], &test_function };
    const command_t cmd2 = { "cmd2", &args2[0], &test_function };

    enqueue_command(&player, &cmd1);
    enqueue_command(&player, &cmd2);
    cr_assert_eq(player.commands[0], &cmd1);
    cr_assert_eq(player.commands[1], &cmd2);

    execute_commands(&player);

    clear_commands(&player);
    cr_assert_eq(player.commands[0], NULL);
    cr_assert_eq(player.commands[1], NULL);

    fflush(stdout);
    fflush(stderr);
    cr_assert_stdout_eq_str("arg1\narg2\narg3\nARG1\nARG2\nARG3\n");
}
