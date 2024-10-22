#ifndef FOOD_H
#define FOOD_H

#include "ingredient.h"

class Food {
 public:
  std::string name;
  double cal, carb, fat, prot;
  std::vector<Ingredient> ingredients;

  /* ------------------------ Methods ----------------------- */

  void view() const;

  void setName();

  void setMacros();

  void resetMacros();

  bool isEqual(const std::string &name) const;

  void addIngredient(const Ingredient &ingredient);
};

/* ------------------------ Functions ----------------------- */

void viewFoods(const std::vector<Food> &foods);

void addFood(
    std::vector<Food> &foods,
    const std::array<std::vector<Ingredient>, categories.size()> &ingredients);

void deleteFood(std::vector<Food> &foods);

void loadFoods(std::vector<Food> &foods);

void saveFoods(const std::vector<Food> &foods);

/* ------------------------- Helpers ------------------------ */

int findFood(const std::vector<Food> &foods, const std::string &name);

#endif