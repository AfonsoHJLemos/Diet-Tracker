#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

#include "ingredient.h"

const int menuSize = 23;

void exit(const std::string &msg);

void pressExit();

std::size_t getOption();

std::size_t getCategory(const std::string &operation);

void showCategories();

#endif