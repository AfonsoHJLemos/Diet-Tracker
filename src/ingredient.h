#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utils.h"

const int numCategories = 7;
const std::array<std::string, numCategories> categories = {
    "Dairy", "Grains", "Fruits", "Meat", "Vegetables", "Beverages", "Snacks"};

class Ingredient {
 public:
  std::string name, brand;
  double cal, carb, fat, prot;

  /* ------------------------ Methods ----------------------- */

  Ingredient(const std::string &name, const std::string &brand, double cal,
             double carb, double fat, double prot);

  void view() const;

  bool isEqual(const std::string &name, const std::string &brand) const;
};

/* ------------------------ Functions ----------------------- */

void viewIngredients(
    const std::array<std::vector<Ingredient>, numCategories> &ingredients);

void addIngredient(
    std::array<std::vector<Ingredient>, numCategories> &ingredients);

void deleteIngredient(
    std::array<std::vector<Ingredient>, numCategories> &ingredients);

void loadIngredients(
    std::array<std::vector<Ingredient>, numCategories> &ingredients);

void saveIngredients(
    const std::array<std::vector<Ingredient>, numCategories> &ingredients);

/* ------------------------- Others ------------------------- */

void getIngredient(std::string &name, std::string &brand);

void getMacros(double &cal, double &carb, double &fat, double &prot);

std::size_t findIngredient(const std::vector<Ingredient> &ingredients,
                           const std::string &name, const std::string &brand);

int viewCategory(const std::vector<Ingredient> &ingredients, int &category);

bool isIngredientsEmpty(
    const std::array<std::vector<Ingredient>, numCategories> &ingredients);

#endif