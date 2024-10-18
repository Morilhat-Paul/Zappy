/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** split_string
*/

#include "split_string.h"
#include "stdbool.h"

static bool is_separator(const char c, const char *separators)
{
    for (int i = 0; separators[i]; i++)
        if (c == separators[i])
            return true;
    return false;
}

static int nb_string(const char *str, char *sep)
{
    int nb_string = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_separator(str[i], sep) &&
            (is_separator(str[i + 1], sep) || str[i + 1] == '\0'))
            continue;
        if (is_separator(str[i], sep))
            nb_string++;
    }
    return nb_string + 1;
}

static char *malloc_string(const char *str, char *separator)
{
    int i = 0;
    char *new_str = NULL;

    while (str[i] != '\0' && !is_separator(str[i], separator))
        i++;
    new_str = malloc(sizeof(char) * (i + 1));
    return new_str;
}

static int copy_string(const char *src, char *dest, char *separator)
{
    int i = 0;

    while (src[i] != '\0' && !is_separator(src[i], separator)) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return i - 1;
}

char **split_string(const char *str, int *word_count)
{
    char **array = NULL;
    int nstr = 0;

    if (!str)
        return NULL;
    while (is_separator(str[0], " \n"))
        str++;
    if (!*str)
        return NULL;
    *word_count = nb_string(str, " \n");
    array = malloc(sizeof(char *) * (*word_count + 1));
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_separator(str[i], " \n"))
                continue;
        array[nstr] = malloc_string(str + i, " \n");
        i += copy_string(str + i, array[nstr], " \n");
        nstr++;
    }
    array[nstr] = NULL;
    return array;
}

void free_split_string(char **str_array)
{
    for (int i = 0; str_array[i] != NULL; i++)
        free(str_array[i]);
    free(str_array);
}
