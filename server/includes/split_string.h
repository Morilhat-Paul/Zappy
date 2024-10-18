/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** split_string.h
*/

#ifndef SPLIT_STRING_H_
    #define SPLIT_STRING_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

int count_words(const char *str);
char **split_string(const char *str, int *word_count);
void free_split_string(char **str_array);

#endif /* !SPLIT_STRING_H_ */
