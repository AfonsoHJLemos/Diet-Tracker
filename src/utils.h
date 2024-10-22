#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <iostream>
#include <string>

void clear(const std::string &msg);

void pressExit();

int getOption();

int getCategory(const std::string &operation,
                const std::array<std::string, 7> &categories);

#endif