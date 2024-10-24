#include "Food/food.h"

int main() {
  std::array<std::vector<Ingredient>, categories.size()> ingredients;
  std::vector<Food> foods;

  loadIngredients(ingredients);
  loadFoods(foods);

  while (true) {
    switch (getOption()) {
      case 1:
        viewIngredients(ingredients);
        break;
      case 2:
        addIngredient(ingredients);
        break;
      case 3:
        deleteIngredient(ingredients);
        break;
      case 4:
        viewFoods(foods);
        break;
      case 5:
        addFood(foods, ingredients);
        break;
      case 6:
        deleteFood(foods);
        break;
      case 0:
        saveIngredients(ingredients);
        saveFoods(foods);
        return 0;
    }
  }
}