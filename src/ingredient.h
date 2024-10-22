#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utils.h"

enum returns { FAILURE = -1, EXIT = 0, SUCCESS = 1 };

/*
    If you need to modify the categories, make sure to update the categories
    array, the getCategory function's arguments in utils.h/utils.cpp and clear
    the ingredients.bin file.
*/

const std::array<std::string, 7> categories = {
    "Dairy", "Grain", "Fruit", "Vegetable", "Meat", "Fat", "Snacks"};

class Ingredient {
 public:
  std::string name, brand;
  double cal, carb, fat, prot;
  bool isUnit;

  /* ------------------------ Methods ----------------------- */

  void view() const;

  void setName();

  void setMacros();

  bool isEqual(const std::string &name, const std::string &brand) const;
};

/* ------------------------ Functions ----------------------- */

void viewIngredients(
    const std::array<std::vector<Ingredient>, categories.size()> &ingredients);

void addIngredient(
    std::array<std::vector<Ingredient>, categories.size()> &ingredients);

void deleteIngredient(
    std::array<std::vector<Ingredient>, categories.size()> &ingredients);

void loadIngredients(
    std::array<std::vector<Ingredient>, categories.size()> &ingredients);

void saveIngredients(
    const std::array<std::vector<Ingredient>, categories.size()> &ingredients);

/* ------------------------- Helpers ------------------------ */

bool isIngredientsEmpty(
    const std::array<std::vector<Ingredient>, categories.size()> &ingredients);

int viewCategory(const std::vector<Ingredient> &ingredients, int category);

int findIngredient(const std::vector<Ingredient> &ingredients,
                   const std::string &name, const std::string &brand);

void insertIngredient(std::vector<Ingredient> &category,
                      const Ingredient &ingredient);

#endif