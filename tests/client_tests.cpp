/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** R-TYPE Tests
*/

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <iostream>
#include <stdlib.h>

Test(main, TestOutput) {
    cr_assert_eq(1, 1, "Expected: %d, Got: %d", 1, 1);
}