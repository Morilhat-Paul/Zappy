/*
** EPITECH PROJECT, 2024
** server
** File description:
** split_messasge
*/

#include <criterion/criterion.h>
#include "../../../includes/message.h"

Test(split_message, basic) {
    const char *message = "cmd arg1 arg2\n";
    char *args_array[] = { "cmd", "arg1", "arg2", NULL };
    char **args = NULL;
    int nb_args = 0;

    args = split_message(message, &nb_args);

    cr_assert_eq(nb_args, 2);
    cr_assert_str_eq(args[0], args_array[0]);
    cr_assert_str_eq(args[1], args_array[1]);
    cr_assert_str_eq(args[2], args_array[2]);
    cr_assert_null(args[3]);
}

// Test(split_message, basic) {
//     const char *message = "cmd arg1 arg2";
//     char *args_array[] = { "cmd", "arg1", "arg2", NULL };
//     char **args = NULL;
//     int nb_args = 0;

//     args = split_message(message, &nb_args);

//     cr_assert_eq(nb_args, 2);
//     // cr_assert_arr_eq(args, args_array, sizeof(args_array), "args size: %li != args_array size: %li", sizeof(args), sizeof(args_array));
//     cr_assert_str_eq(args[0], args_array[0]);
//     cr_assert_str_eq(args[1], args_array[1]);
//     cr_assert_str_eq(args[2], args_array[2]);
//     cr_assert_null(args[3]);
// }
