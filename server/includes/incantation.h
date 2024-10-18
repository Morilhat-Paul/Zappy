/*
** EPITECH PROJECT, 2024
** DEV
** File description:
** incantation
*/

#ifndef INCANTATION_H_
    #define INCANTATION_H_

    #include "resources.h"

typedef unsigned int resource_level_t[NB_RESOURCE];

static const resource_level_t resources_level[] = {
    { 1, 1, 0, 0, 0, 0, 0 },   // Resource needed for incantation level 2
    { 2, 1, 1, 1, 0, 0, 0 },   // Resource needed for incantation level 3
    { 2, 2, 0, 1, 0, 2, 0 },   // Resource needed for incantation level 4
    { 4, 1, 1, 2, 0, 1, 0 },   // Resource needed for incantation level 5
    { 4, 1, 2, 1, 3, 0, 0 },   // Resource needed for incantation level 6
    { 6, 1, 2, 3, 0, 1, 0 },   // Resource needed for incantation level 7
    { 6, 2, 2, 2, 2, 2, 1 },   // Resource needed for incantation level 8
};

#endif /* !INCANTATION_H_ */
